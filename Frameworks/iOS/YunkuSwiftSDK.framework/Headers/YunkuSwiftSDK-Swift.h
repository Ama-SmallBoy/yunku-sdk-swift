// Generated by Apple Swift version 2.2 (swiftlang-703.0.18.8 clang-703.0.31)
#pragma clang diagnostic push

#if defined(__has_include) && __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wauto-import"
#include <objc/NSObject.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if !defined(SWIFT_TYPEDEFS)
# define SWIFT_TYPEDEFS 1
# if defined(__has_include) && __has_include(<uchar.h>)
#  include <uchar.h>
# elif !defined(__cplusplus) || __cplusplus < 201103L
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
# endif
typedef float swift_float2  __attribute__((__ext_vector_type__(2)));
typedef float swift_float3  __attribute__((__ext_vector_type__(3)));
typedef float swift_float4  __attribute__((__ext_vector_type__(4)));
typedef double swift_double2  __attribute__((__ext_vector_type__(2)));
typedef double swift_double3  __attribute__((__ext_vector_type__(3)));
typedef double swift_double4  __attribute__((__ext_vector_type__(4)));
typedef int swift_int2  __attribute__((__ext_vector_type__(2)));
typedef int swift_int3  __attribute__((__ext_vector_type__(3)));
typedef int swift_int4  __attribute__((__ext_vector_type__(4)));
#endif

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif

#if defined(__has_attribute) && __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if defined(__has_attribute) && __has_attribute(swift_name)
# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))
#else
# define SWIFT_COMPILE_NAME(X)
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if defined(__has_attribute) && __has_attribute(objc_subclassing_restricted)
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if defined(__has_attribute) && __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name) enum _name : _type _name; enum SWIFT_ENUM_EXTRA _name : _type
# if defined(__has_feature) && __has_feature(generalized_swift_name)
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME) enum _name : _type _name SWIFT_COMPILE_NAME(SWIFT_NAME); enum SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_ENUM_EXTRA _name : _type
# else
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME) SWIFT_ENUM(_type, _name)
# endif
#endif
#if defined(__has_feature) && __has_feature(modules)
@import ObjectiveC;
@import Foundation;
#endif

#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
typedef SWIFT_ENUM(NSInteger, AuthType) {
  AuthTypeDefault = 0,
  AuthTypePreview = 1,
  AuthTypeDownload = 2,
  AuthTypeUpload = 3,
};

enum LogLevel : NSInteger;

SWIFT_CLASS("_TtC13YunkuSwiftSDK6Config")
@interface Config : NSObject
+ (BOOL)logPrint;
+ (void)setLogPrint:(BOOL)value;
+ (enum LogLevel)logLevel;
+ (void)setLogLevel:(enum LogLevel)value;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC13YunkuSwiftSDK11SignAbility")
@interface SignAbility : NSObject
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end

enum NetType : NSInteger;
@protocol UploadCallBack;
@class UploadManager;
@class NSData;

SWIFT_CLASS("_TtC13YunkuSwiftSDK14EntFileManager")
@interface EntFileManager : SignAbility
- (nonnull instancetype)initWithOrgClientId:(NSString * _Nonnull)orgClientId orgClientSecret:(NSString * _Nonnull)orgClientSecret OBJC_DESIGNATED_INITIALIZER;
- (NSDictionary<NSString *, id> * _Nonnull)getFileList:(NSInteger)start fullPath:(NSString * _Nonnull)fullPath;
- (NSDictionary<NSString *, id> * _Nonnull)getUpdateList:(BOOL)isCompare fetchDateline:(NSInteger)fetchDateline;
- (NSDictionary<NSString *, id> * _Nonnull)getFileInfo:(NSString * _Nonnull)fullPath type:(enum NetType)type;
- (NSDictionary<NSString *, id> * _Nonnull)createFolder:(NSString * _Nonnull)fullPath opName:(NSString * _Nonnull)opName;
- (UploadManager * _Nonnull)uploadByBlock:(NSString * _Nonnull)localPath fullPath:(NSString * _Nonnull)fullPath opName:(NSString * _Nonnull)opName opId:(NSInteger)opId overwrite:(BOOL)overwrite delegate:(id <UploadCallBack> _Nonnull)delegate;
- (NSDictionary<NSString *, id> * _Nonnull)createFile:(NSString * _Nonnull)fullPath opName:(NSString * _Nonnull)opName data:(NSData * _Nonnull)data;
- (NSDictionary<NSString *, id> * _Nonnull)del:(NSString * _Nonnull)fullPaths opName:(NSString * _Nonnull)opName;
- (NSDictionary<NSString *, id> * _Nonnull)move:(NSString * _Nonnull)fullPath destFullPath:(NSString * _Nonnull)destFullPath opName:(NSString * _Nonnull)opName;
- (NSDictionary<NSString *, id> * _Nonnull)link:(NSString * _Nonnull)fullPath deadline:(NSInteger)deadline authType:(enum AuthType)authType password:(NSString * _Nullable)password;
- (NSDictionary<NSString *, id> * _Nonnull)sendmsg:(NSString * _Nonnull)title text:(NSString * _Nonnull)text image:(NSString * _Nullable)image linkUrl:(NSString * _Nullable)linkUrl opName:(NSString * _Nonnull)opName;
- (NSDictionary<NSString *, id> * _Nonnull)links:(BOOL)fileOnly;
- (NSDictionary<NSString *, id> * _Nonnull)getUpdateCounts:(NSInteger)beginDateline endDateline:(NSInteger)endDateline showDelete:(BOOL)showDelete;
- (NSDictionary<NSString *, id> * _Nonnull)createFileByUrl:(NSString * _Nonnull)fullPath opId:(NSInteger)opId opName:(NSString * _Null_unspecified)opName overwrite:(BOOL)overwrite fileUrl:(NSString * _Nonnull)fileUrl;
- (NSDictionary<NSString *, id> * _Nonnull)getUploadServers;
- (NSDictionary<NSString *, id> * _Nonnull)getServerSite:(NSString * _Nonnull)type;
- (EntFileManager * _Nonnull)clone;
@end


SWIFT_CLASS("_TtC13YunkuSwiftSDK12ParentEngine")
@interface ParentEngine : SignAbility
- (NSDictionary<NSString *, id> * _Nonnull)accessToken:(NSString * _Nonnull)username password:(NSString * _Nonnull)password;
@end

enum MemberType : NSInteger;

SWIFT_CLASS("_TtC13YunkuSwiftSDK13EntLibManager")
@interface EntLibManager : ParentEngine
- (nonnull instancetype)initWithClientId:(NSString * _Nonnull)clientId clientSecret:(NSString * _Nonnull)clientSecret isEnt:(BOOL)isEnt OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithClientId:(NSString * _Nonnull)clientId clientSecret:(NSString * _Nonnull)clientSecret isEnt:(BOOL)isEnt token:(NSString * _Nonnull)token OBJC_DESIGNATED_INITIALIZER;
- (NSDictionary<NSString *, id> * _Nonnull)create:(NSString * _Nonnull)orgName orgCapacity:(NSString * _Nullable)orgCapacity storagePointName:(NSString * _Nullable)storagePointName orgDesc:(NSString * _Nullable)orgDesc orgLogo:(NSString * _Nullable)orgLogo;
- (NSDictionary<NSString *, id> * _Nonnull)getLibList;
- (NSDictionary<NSString *, id> * _Nonnull)bindLib:(NSInteger)orgId title:(NSString * _Nullable)title linkUrl:(NSString * _Nullable)linkUrl;
- (NSDictionary<NSString *, id> * _Nonnull)unbindLib:(NSString * _Nonnull)orgClientId;
- (NSDictionary<NSString *, id> * _Nonnull)getMembers:(NSInteger)start size:(NSInteger)size orgId:(NSInteger)orgId;
- (NSDictionary<NSString *, id> * _Nonnull)addMembers:(NSInteger)orgId roleId:(NSInteger)roleId memberIds:(NSArray<NSString *> * _Nonnull)memberIds;
- (NSDictionary<NSString *, id> * _Nonnull)setMemberRole:(NSInteger)orgId roleId:(NSInteger)roleId memberIds:(NSArray<NSString *> * _Nonnull)memberIds;
- (NSDictionary<NSString *, id> * _Nonnull)delMember:(NSInteger)orgId memberIds:(NSArray<NSString *> * _Nonnull)memberIds;
- (NSDictionary<NSString *, id> * _Nonnull)getGroups:(NSInteger)orgId;
- (NSDictionary<NSString *, id> * _Nonnull)addGroup:(NSInteger)orgId groupId:(NSInteger)groupId roleId:(NSInteger)roleId;
- (NSDictionary<NSString *, id> * _Nonnull)delGroup:(NSInteger)orgId groupId:(NSInteger)groupId;
- (NSDictionary<NSString *, id> * _Nonnull)setGroupRole:(NSInteger)orgId groupId:(NSInteger)groupId roleId:(NSInteger)roleId;
- (NSDictionary<NSString *, id> * _Nonnull)destroy:(NSString * _Nonnull)orgClientId;
- (NSDictionary<NSString *, id> * _Nonnull)set:(NSInteger)orgId orgName:(NSString * _Nullable)orgName orgCapacity:(NSString * _Nullable)orgCapacity orgDes:(NSString * _Nullable)orgDes orgLogo:(NSString * _Nullable)orgLogo;
- (NSDictionary<NSString *, id> * _Nonnull)getMember:(NSInteger)orgId type:(enum MemberType)type ids:(NSArray<NSString *> * _Nonnull)ids;
- (NSDictionary<NSString *, id> * _Nonnull)getInfo:(NSInteger)orgId;
- (EntLibManager * _Nonnull)clone;
@end


SWIFT_CLASS("_TtC13YunkuSwiftSDK10EntManager")
@interface EntManager : ParentEngine
- (nonnull instancetype)initWithClientId:(NSString * _Nonnull)clientId clientSecret:(NSString * _Nonnull)clientSecret isEnt:(BOOL)isEnt OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithClientId:(NSString * _Nonnull)clientId clientSecret:(NSString * _Nonnull)clientSecret isEnt:(BOOL)isEnt token:(NSString * _Nonnull)token OBJC_DESIGNATED_INITIALIZER;
- (NSDictionary<NSString *, id> * _Nonnull)getRoles;
- (NSDictionary<NSString *, id> * _Nonnull)getMembers:(NSInteger)start size:(NSInteger)size;
- (NSDictionary<NSString *, id> * _Nonnull)getGroups;
- (NSDictionary<NSString *, id> * _Nonnull)getMemberFileLink:(NSInteger)memberId fileOnly:(BOOL)fileOnly;
- (NSDictionary<NSString *, id> * _Nonnull)getMemberById:(NSInteger)memberId;
- (NSDictionary<NSString *, id> * _Nonnull)getMemberByOutId:(NSString * _Nonnull)outId;
- (NSDictionary<NSString *, id> * _Nonnull)getMemberByAccount:(NSString * _Nonnull)account;
- (NSDictionary<NSString *, id> * _Nonnull)addSyncMember:(NSString * _Nonnull)oudId memberName:(NSString * _Nonnull)memberName account:(NSString * _Nonnull)account memberEmail:(NSString * _Nullable)memberEmail memberPhone:(NSString * _Nullable)memberPhone password:(NSString * _Nullable)password;
- (NSDictionary<NSString *, id> * _Nonnull)delSyncMember:(NSArray<NSString *> * _Nonnull)members;
- (NSDictionary<NSString *, id> * _Nonnull)addSyncGroup:(NSString * _Nonnull)outId name:(NSString * _Nonnull)name parentOutId:(NSString * _Nullable)parentOutId;
- (NSDictionary<NSString *, id> * _Nonnull)delSyncGroup:(NSArray<NSString *> * _Nonnull)groups;
- (NSDictionary<NSString *, id> * _Nonnull)addSyncGroupMember:(NSString * _Nonnull)groupOutId members:(NSArray<NSString *> * _Nonnull)members;
- (NSDictionary<NSString *, id> * _Nonnull)delSyncGroupMember:(NSString * _Nonnull)groupOutId members:(NSArray<NSString *> * _Nonnull)members;
- (NSDictionary<NSString *, id> * _Nonnull)getGroupMembers:(NSInteger)groupId start:(NSInteger)start size:(NSInteger)size showChild:(BOOL)showChild;
- (EntManager * _Nonnull)clone;
@end


/// HTTP status codes as per http://en.wikipedia.org/wiki/List_of_HTTP_status_codes
///
/// The RF2616 standard is completely covered (http://www.ietf.org/rfc/rfc2616.txt)
typedef SWIFT_ENUM(NSInteger, HTTPStatusCode) {
  HTTPStatusCodeContinue = 100,
  HTTPStatusCodeSwitchingProtocols = 101,
  HTTPStatusCodeProcessing = 102,
  HTTPStatusCodeOK = 200,
  HTTPStatusCodeCreated = 201,
  HTTPStatusCodeAccepted = 202,
  HTTPStatusCodeNonAuthoritativeInformation = 203,
  HTTPStatusCodeNoContent = 204,
  HTTPStatusCodeResetContent = 205,
  HTTPStatusCodePartialContent = 206,
  HTTPStatusCodeMultiStatus = 207,
  HTTPStatusCodeAlreadyReported = 208,
  HTTPStatusCodeIMUsed = 226,
  HTTPStatusCodeMultipleChoices = 300,
  HTTPStatusCodeMovedPermanently = 301,
  HTTPStatusCodeFound = 302,
  HTTPStatusCodeSeeOther = 303,
  HTTPStatusCodeNotModified = 304,
  HTTPStatusCodeUseProxy = 305,
  HTTPStatusCodeSwitchProxy = 306,
  HTTPStatusCodeTemporaryRedirect = 307,
  HTTPStatusCodePermanentRedirect = 308,
  HTTPStatusCodeBadRequest = 400,
  HTTPStatusCodeUnauthorized = 401,
  HTTPStatusCodePaymentRequired = 402,
  HTTPStatusCodeForbidden = 403,
  HTTPStatusCodeNotFound = 404,
  HTTPStatusCodeMethodNotAllowed = 405,
  HTTPStatusCodeNotAcceptable = 406,
  HTTPStatusCodeProxyAuthenticationRequired = 407,
  HTTPStatusCodeRequestTimeout = 408,
  HTTPStatusCodeConflict = 409,
  HTTPStatusCodeGone = 410,
  HTTPStatusCodeLengthRequired = 411,
  HTTPStatusCodePreconditionFailed = 412,
  HTTPStatusCodeRequestEntityTooLarge = 413,
  HTTPStatusCodeRequestURITooLong = 414,
  HTTPStatusCodeUnsupportedMediaType = 415,
  HTTPStatusCodeRequestedRangeNotSatisfiable = 416,
  HTTPStatusCodeExpectationFailed = 417,
  HTTPStatusCodeImATeapot = 418,
  HTTPStatusCodeAuthenticationTimeout = 419,
  HTTPStatusCodeUnprocessableEntity = 422,
  HTTPStatusCodeLocked = 423,
  HTTPStatusCodeFailedDependency = 424,
  HTTPStatusCodeUpgradeRequired = 426,
  HTTPStatusCodePreconditionRequired = 428,
  HTTPStatusCodeTooManyRequests = 429,
  HTTPStatusCodeRequestHeaderFieldsTooLarge = 431,
  HTTPStatusCodeLoginTimeout = 440,
  HTTPStatusCodeNoResponse = 444,
  HTTPStatusCodeRetryWith = 449,
  HTTPStatusCodeUnavailableForLegalReasons = 451,
  HTTPStatusCodeRequestHeaderTooLarge = 494,
  HTTPStatusCodeCertError = 495,
  HTTPStatusCodeNoCert = 496,
  HTTPStatusCodeHTTPToHTTPS = 497,
  HTTPStatusCodeTokenExpired = 498,
  HTTPStatusCodeClientClosedRequest = 499,
  HTTPStatusCodeInternalServerError = 500,
  HTTPStatusCodeNotImplemented = 501,
  HTTPStatusCodeBadGateway = 502,
  HTTPStatusCodeServiceUnavailable = 503,
  HTTPStatusCodeGatewayTimeout = 504,
  HTTPStatusCodeHTTPVersionNotSupported = 505,
  HTTPStatusCodeVariantAlsoNegotiates = 506,
  HTTPStatusCodeInsufficientStorage = 507,
  HTTPStatusCodeLoopDetected = 508,
  HTTPStatusCodeBandwidthLimitExceeded = 509,
  HTTPStatusCodeNotExtended = 510,
  HTTPStatusCodeNetworkAuthenticationRequired = 511,
  HTTPStatusCodeNetworkTimeoutError = 599,
};

typedef SWIFT_ENUM(NSInteger, LogLevel) {
  LogLevelInfo = 0,
  LogLevelWarning = 1,
  LogLevelError = 2,
};

typedef SWIFT_ENUM(NSInteger, MemberType) {
  MemberTypeAccount = 0,
  MemberTypeOutId = 1,
  MemberTypeMemberId = 2,
};


@interface NSData (SWIFT_EXTENSION(YunkuSwiftSDK))
@end


@interface NSData (SWIFT_EXTENSION(YunkuSwiftSDK))
@end


@interface NSData (SWIFT_EXTENSION(YunkuSwiftSDK))
- (NSData * _Nonnull)sha1;
@end

typedef SWIFT_ENUM(NSInteger, NetType) {
  NetTypeDefault = 0,
  NetTypeIn = 1,
};



SWIFT_CLASS("_TtC13YunkuSwiftSDK12ReturnResult")
@interface ReturnResult : NSObject
@property (nonatomic, copy) NSDictionary<NSString *, id> * _Null_unspecified result;
@property (nonatomic) NSInteger code;
+ (ReturnResult * _Nonnull)create:(NSDictionary<NSString *, id> * _Nonnull)dic;
@end



SWIFT_PROTOCOL("_TtP13YunkuSwiftSDK14UploadCallBack_")
@protocol UploadCallBack
- (void)onSuccess:(NSString * _Nonnull)fileHash fullPath:(NSString * _Nonnull)fullPath;
- (void)onFail:(NSString * _Nonnull)errorMsg;
- (void)onProgress:(float)percent;
@end


SWIFT_CLASS("_TtC13YunkuSwiftSDK13UploadManager")
@interface UploadManager : SignAbility
- (void)stop;
@end

#pragma clang diagnostic pop
