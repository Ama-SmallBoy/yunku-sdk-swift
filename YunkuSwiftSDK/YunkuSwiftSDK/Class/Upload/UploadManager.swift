//
//  Uploader.swift
//  YunkuSwiftSDK
//
//  Created by Brandon on 15/7/6.
//  Copyright (c) 2015年 goukuai. All rights reserved.
//

import Foundation
public class UploadManager: SignAbility{
    let urlUploadInit = "/upload_init"
    let urlUploadPart = "/upload_part"
    let urlUploadAbort = "/upload_abort"
    let urlUploadFinish = "/upload_finish"
    let rangeSize = 65536
    // 上传分块大小-64K
    
    var _server = ""
    var _session = ""
    var _apiUrl = ""
    
    //    var _data:NSData?
    var _fullPath = ""
    var _orgClientId = ""
    var _dateline = 0
    var _opName = ""
    var _opId = 0
    
    var _data:NSData?
    
    var _localPath = ""
    
    var _overWrite = false
    
    var delegate : UploadCallBack?
    
    
    init(apiUrl: String, localPath: String, fullPath: String, opName: String, opId: Int, orgClientId: String, dateline: Int, clientSecret: String, overWirte: Bool) {
        super.init()
        _apiUrl = apiUrl
        _localPath = localPath
        _fullPath = fullPath
        _opName = opName
        _opId = opId
        _dateline = dateline
        _orgClientId = orgClientId
        _clientSecret = clientSecret
        _overWrite = overWirte
    }
    
    func doUpload() {
        
        var checkValidation = NSFileManager.defaultManager()
        if checkValidation.fileExistsAtPath(_localPath){
            startUpload()
        }else{
            if delegate != nil{
                delegate?.onFail("\(_localPath)  file is not exist")
            }
            
        }
    }
    
    
    //MARK:开始上传
    private func startUpload() -> Bool {
        
        var handler = NSFileHandle(forReadingAtPath: _localPath)
        var filesize = handler?.seekToEndOfFile()
        handler?.seekToFileOffset(0)
        
        var fullPath = _fullPath
        
        var filehash = Utils.getFileSha1(_localPath)
        var fileName = _fullPath.lastPathComponent
        
        var returnResult = ReturnResult.create(addFile(filesize!, fileHash: filehash, fullPath: fullPath))
        var data = FileOperationData.create(returnResult.result!, code: returnResult.code)
        
        if data.code == HTTPStatusCode.OK.rawValue{
            
            if data.state != FileOperationData.stateNoupload {
                _server = data.server
                
                uploadInit(data.uuidHash, fileName: fileName, fullPath: fullPath, fileHash: filehash, fileSize: filesize!)
                
                var rangeIndex = 0
                var rangeEnd:UInt64 = 0
                var rangeStart:UInt64 = 0
                var rangEnd:UInt64 = 0
                var range = ""
                
                while handler?.offsetInFile < filesize && !self.isStop{
                    var bufferData = handler?.readDataOfLength(rangeSize)
                    
                    //获取crc校验值
                    var crc32 = CRC().crc32Value(bufferData!)
                    
                    
                    //获取偏移量range值
                    rangeStart = UInt64(rangeIndex * rangeSize)
                    rangeEnd = rangeStart + UInt64((bufferData?.length)! - 1)
                    range = "\(rangeStart)-\(rangeEnd)"
                    
                    if delegate != nil{
                        delegate?.onProgress( Float(rangeStart) / Float(filesize!))
                    }
                    
                    var returnResult = uploadPart(range, data: bufferData!, dataLength: bufferData!.length, crc32: crc32)
                    
                    if returnResult.code == HTTPStatusCode.OK.rawValue{
                        
                        rangeStart += UInt64(rangeSize)
                        
                    } else if returnResult.code == HTTPStatusCode.Accepted.rawValue{
                        
                        break
                        
                    } else if returnResult.code == HTTPStatusCode.InternalServerError.rawValue{
                        
                        reGetUploadServer(filesize!, fileHash: filehash, fullPath: fullPath)
                        
                    } else if returnResult.code == HTTPStatusCode.Unauthorized.rawValue {
                        //认证失败
                        
                        var success =  uploadInit(data.uuidHash, fileName: fileName, fullPath: fullPath, fileHash: filehash, fileSize: filesize!)
                        
                        if !success{
                            return false
                        }
                        
                    } else if returnResult.code == HTTPStatusCode.Conflict.rawValue {
                        
                        var dic = returnResult.result
                        var partRangeStart = dic?["expect"] as! UInt64
                        rangeStart = partRangeStart
                        
                    } else {
                        return false
                    }
                    
                    rangeIndex++
                }
                
                var success = uploadCheck()
                
                if !success{
                    return false
                }
                
                if delegate != nil{
                    delegate?.onProgress(1)
                    delegate?.onSuccess(filehash)
                }
                
                return true
                
            } else {
                
                if delegate != nil{
                    delegate?.onSuccess(filehash)
                }
                
                return true
            }
            
        }else {
            LogPrint.error("upload error:\(data.errorCode):\(data.errorMsg)")
            return false
        }
        
    }
    
    //MARK:上传初始化
    private func uploadInit(hash: String, fileName: String, fullPath: String, fileHash: String,fileSize:UInt64) ->Bool {
        let url = _server + urlUploadInit + "?org_client_id=\(_orgClientId)"
        var params = Dictionary<String, String>()
        params["x-gk-upload-pathhash"] = hash
        params["x-gk-upload-filename"] = fileName.urlEncode
        params["x-gk-upload-filehash"] = fileHash
        params["x-gk-upload-filesize"] = String(fileSize)
        var resultDic = NetConnection.sendRequest(url, method: "POST", params: nil, headParams: params)
        var retrunResult = ReturnResult.create(resultDic)
        var returnResultDic = retrunResult.result
        if retrunResult.code == HTTPStatusCode.OK.rawValue {
            _session = returnResultDic?["session"] as! String
        }else if retrunResult.code >= HTTPStatusCode.InternalServerError.rawValue {
            reGetUploadServer(fileSize, fileHash: fileHash, fullPath: fullPath)
            return uploadInit(hash, fileName: fileName, fullPath: fullPath, fileHash: fileHash, fileSize: fileSize)
            
        }else {
            return false
        }
        return true
    }
    
    //MARK:分块传输
    private func uploadPart(range:String,data:NSData,dataLength:Int,crc32:UInt32) -> ReturnResult {
        var returnResult = ReturnResult()
        
        var url: NSURL = NSURL(string: _server + urlUploadPart)!
        var request = NSMutableURLRequest(URL: url)
        
        request.addValue(Config.userAgent, forHTTPHeaderField: "User-Agent")
        request.timeoutInterval = Config.connectTimeOut
        request.HTTPMethod = "PUT"
        request.addValue( "Keep-Alive", forHTTPHeaderField:  "Connection")
        request.addValue( _session, forHTTPHeaderField: "x-gk-upload-session")
        request.addValue( range, forHTTPHeaderField: "x-gk-upload-range")
        request.addValue( String(crc32), forHTTPHeaderField: "x-gk-upload-crc")
        request.HTTPBody = data
        
        var response: NSURLResponse?
        
        var dataVal: NSData = NSURLConnection.sendSynchronousRequest(request, returningResponse: &response, error: nil)!
        
        //输出返回
        LogPrint.info(NSString(data: dataVal, encoding: NSUTF8StringEncoding))
        var error: NSError?
        var jsonResult = NSJSONSerialization.JSONObjectWithData(dataVal, options: NSJSONReadingOptions.MutableContainers, error: &error) as? Dictionary<String, AnyObject>
        
        var httpcode: Int = 0
        if let httpResponse = response as? NSHTTPURLResponse {
            httpcode = httpResponse.statusCode
        }
        
        return ReturnResult( code: httpcode, result: jsonResult)
    }
    
    //MARK:分块传输
    private func uploadCheck() -> Bool {
        var result = ReturnResult.create(uploadFinish())
        return result.code == HTTPStatusCode.OK.rawValue
    }
    
    //MARK:分块传输
    private func uploadFinish() -> Dictionary<String, AnyObject> {
        let url = _server + urlUploadFinish
        var params = Dictionary<String, String>()
        params["x-gk-upload-session"] = _session
        return NetConnection.sendRequest(url, method: "POST", params: nil, headParams: params)
    }
    
    //MARK:分块传输
    private func reGetUploadServer(fileSize: UInt64, fileHash: String, fullPath: String) {
        var returnResult = ReturnResult.create(addFile(fileSize, fileHash: fileHash, fullPath: fullPath))
        var data = FileOperationData.create(returnResult.result!, code: returnResult.code)
        _server = data.server
    }
    
    //MARK:分块传输
    private func uploadAbort() {
        let url = _server + urlUploadAbort
        var params = Dictionary<String, String>()
        params["x-gk-upload-session"] = _session
        NetConnection.sendRequest(url, method: "POST", params: nil, headParams: params)
    }
    
    //MARK:添加文件
    private func addFile(fileSize: UInt64, fileHash: String, fullPath: String) -> Dictionary<String, AnyObject> {
        
        let method = "POST"
        let url = _apiUrl
        var params = Dictionary<String, String?>()
        params["org_client_id"] = _orgClientId
        params["dateline"] = String(_dateline)
        params["fullpath"] = fullPath
        
        if _opId > 0 {
            params["op_id"] = String(_opId)
        } else if (!_opName.isEmpty) {
            params["op_name"] = _opName
        }
        params["overwrite"] = String(_overWrite ? 1 : 0)
        params["op_name"] = _opName
        params["sign"] = self.generateSign(params)
        
        params["filesize"] = String(fileSize)
        params["filehash"] = fileHash
        
        return NetConnection.sendRequest(url, method: method, params: params, headParams: nil)
    }
    
    var isStop: Bool = false
    
    public func stop() {
        isStop = true
    }
    
    
}