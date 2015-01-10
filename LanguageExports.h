/** © 2014, Brandon T. All Rights Reserved.

    This project is licensed under the General Public License v3.
    This project uses LibCurl and LibSSL.
    In addition to the project's licenses, the following exception applies:

        In addition, as a special exception, the copyright holders give
        permission to link the code of portions of this program with the
        OpenSSL library under certain conditions as described in each
        individual source file, and distribute linked combinations including
        the two.

        You must obey the GNU General Public License in all respects for all
        of the code used other than OpenSSL. If you modify file(s) with this
        exception, you may extend this exception to your version of the
        file(s), but you are not obligated to do so. If you do not wish to do
        so, delete this exception statement from your version. If you delete
        this exception statement from all source files in the program, then
        also delete it here.

						Author : Brandon T.
						Contact: Brandon.T-@Live.com
**/

#ifndef LANGUAGEEXPORTS_HPP_INCLUDED
#define LANGUAGEEXPORTS_HPP_INCLUDED

#include "Exports.h"
#include "jni.h"
#include "CurlSSL.h"

#define JAVA_EXPORT __declspec(dllexport)



                                    /** PASCAL EXPORTS **/

static const char* PascalExports[] =
{
    #ifndef CURL_SSL
    "AcceptSocket", "Function Pro_AcceptSocket(var ssl_info, ssl_client_info: SSLSocket): Boolean;",
    "BindSocket", "Function Pro_BindSocket(var ssl_info: SSLSocket): Boolean;",
    "BytesPendingSocket", "Function Pro_BytesPendingSocket(var ssl_info: SSLSocket): Integer;",
    "CreateSocket", "Function Pro_CreateSocket(var ssl_info: SSLSocket): Boolean;",
    "ConnectSocket", "Function Pro_ConnectSocket(var ssl_info: SSLSocket): Boolean;",
    "ListenSocket", "Function Pro_ListenSocket(var ssl_info: SSLSocket): Boolean;",
    "SetBlockingSocket", "Function Pro_SetBlockingSocket(var ssl_info: SSLSocket): Boolean;",
    "SetTimeoutSocket", "Function Pro_SetTimeoutSocket(var ssl_info: SSLSocket): Boolean;",
    "SelectSocket", "Function Pro_SelectSocket(var ssl_info: SSLSocket; Read: Boolean): Integer;",
    "CloseSocket", "Function Pro_CloseSocket(var ssl_info: SSLSocket): Boolean;",
    "FreeSocket", "Function Pro_FreeSocket(var ssl_info: SSLSocket): Boolean;",
    "ReadSocket", "Function Pro_ReadSocket(var ssl_info: SSLSocket; Buffer: PChar; Size: Cardinal): Integer;",
    "WriteSocket", "Function Pro_WriteSocket(var ssl_info: SSLSocket; Buffer: String; Size: Cardinal): Integer;",
    #else
    "Curl_InitSocket", "Procedure Pro_InitSocket(var curl_info: SSLSocket; WriteFunc: ProWritePtr; HeaderFunc: ProWritePtr; ErrorHandlerFunc: ProErrorHandlerPtr; StrLenFunc: ProLenPtr);",
    "Curl_CreateSocket", "Procedure Pro_CreateSocket(var curl_info: SSLSocket; useragent: String);",
    "Curl_FreeSocket", "Procedure Pro_FreeSocket(var curl_info: SSLSocket);",
    "Curl_SetURLFollow", "Procedure Pro_SetURLFollow(var curl_info: SSLSocket; follow: Boolean);",
    "Curl_SetSSL", "Procedure Pro_SetSSL(var curl_info: SSLSocket; try_set: Boolean; verifypeer: Boolean; verifyhost: Boolean);",
    "Curl_SetCookies", "Procedure Pro_SetCookies(var curl_info: SSLSocket; const cookiejar: String; const cookiefile: String);",
    "Curl_SetHeaderCapture", "Procedure Pro_SetHeaderCapture(var curl_info: SSLSocket; enable: boolean);",
    "Curl_SetHeader", "Function Pro_SetHeader(var curl_info: SSLSocket; const key: String; const value: String): Boolean;",
    "Curl_CustomRequest", "Procedure Pro_CustomRequest(var curl_info: SSLSocket; const request: String);",
    "Curl_SetNoBody", "Procedure Pro_SetNoBody(var curl_info: SSLSocket; enable: Boolean);",
    "Curl_SetVerbose", "Procedure Pro_SetVerbose(var curl_info: SSLSocket; enable: Boolean);",
    "Curl_GetHostLocation", "Function Pro_GetHostLocation(var address: String; var buffer: String): String;",
    "Curl_GetRequestLocation", "Function Pro_GetRequestLocation(var address: String; var buffer: String): String;",
    "Curl_SetURL", "Procedure Pro_SetURL(var curl_info: SSLSocket; const URL: String);",
    "Curl_SetUpload", "Procedure Pro_SetUpload(var curl_info: SSLSocket; enable: Boolean);",
    "Curl_SetLogin", "Procedure Pro_SetLogin(var curl_info: SSLSocket; const user: String; const pwd: String);",
    "Curl_ClearParams", "Procedure Pro_ClearParameters(var curl_info: SSLSocket);",
    "Curl_AddParameter", "Function Pro_AddParameter(var curl_info: SSLSocket; const key: String; const value: String; escape: Boolean): Boolean;",
    "Curl_DoGet", "Function Pro_DoGet(var curl_info: SSLSocket): PChar;",
    "Curl_DoGetEx", "Procedure Pro_DoGetEx(var curl_info: SSLSocket; var Res: ProMemoryStruct);",
    "Curl_DoPost", "Function Pro_DoPost(var curl_info: SSLSocket): PChar;",
    "Curl_DoPostEx", "Procedure Pro_DoPostEx(var curl_info: SSLSocket; var Res: ProMemoryStruct);",
    "Curl_Perform", "Function Pro_Perform(var curl_info: SSLSocket): PChar;",
    "Curl_PerformEx", "Procedure Pro_PerformEx(var curl_info: SSLSocket; var Res: ProMemoryStruct);",
    "Curl_GetHeaders", "Function Pro_GetHeaders(var curl_info: SSLSocket): PChar;",
    "Curl_GetHeaderEx", "Procedure Pro_GetHeadersEx(var curl_info: SSLSocket; var Res: ProMemoryStruct);",
    "Curl_SMTP", "Function Pro_SMTP(var curl_info: SSLSocket; url, user, pwd, name, recipient, cc, bcc, subject, body, bodymime, file, filemime: PChar): Boolean;",
    "Curl_MSTPC", "Procedure Pro_MSTPC(var curl_info: SSLSocket; var Res: ProMemoryStruct);"
    #endif
};

static const char* PascalTypes[] =
{
    #ifndef CURL_SSL
	"SSLSocketType", "(TLS1_CLIENT_METHOD, TLS1_SERVER_METHOD, TLS11_CLIENT_METHOD, TLS11_SERVER_METHOD, SSL2_CLIENT_METHOD, SSL2_SERVER_METHOD, SSL3_CLIENT_METHOD, SSL3_SERVER_METHOD, SSL23_CLIENT_METHOD, SSL23_SERVER_METHOD);",
	"SSLSocket", "{$IFNDEF LAPE}record sock: Cardinal; ssl: Cardinal; ctx: Cardinal; address: PChar; socktype: Integer; timeout: Cardinal; port: Word; connected: Boolean; blockmode: Boolean; end;{$ELSE}packed record sock: Cardinal; ssl: Cardinal; ctx: Cardinal; address: PChar; socktype: SSLSocketType; timeout: Cardinal; port: Word; connected: Boolean; blockmode: Boolean; end;{$ENDIF}"
    #else
    "ProWritePtr", "Function(contents: PChar; size: PtrUInt; nmemb: PtrUint; var userp: String): PtrUInt;",
    "ProErrorHandlerPtr", "Function(str: PChar; errorcode: LongInt): PtrUInt;",
    "ProLenPtr", "Function(var Str: String): PtrUInt",
    "ProMemoryStruct", "{$IFNDEF LAPE}record memory: PChar; size: PtrUInt; end;{$ELSE}packed record memory: PChar; size: PtrUInt; end;{$ENDIF}",
    "SSLSocket", "{$IFNDEF LAPE}record curl_handle: PtrUInt; headers: PChar; data: PChar; params: PChar; LengthFunc: ProLenPtr; ErrorHandlerFunc: ProErrorHandlerPtr; WriteFunc: ProWritePtr; HeaderFunc: ProWritePtr; hdrs: PChar; Timeout: Cardinal; Port: Word; caller_allocates: Boolean; end;{$ELSE}packed record curl_handle: PtrUInt; headers: PChar; data: PChar; params: PChar; LengthFunc: ProLenPtr; ErrorHandlerFunc: ProErrorHandlerPtr; WriteFunc: ProWritePtr; HeaderFunc: ProWritePtr; hdrs: PChar; Timeout: Cardinal; Port: Word; caller_allocates: Boolean; end;{$ENDIF}"
    #endif
};

static const long int PascalExportCount = sizeof(PascalExports) / (sizeof(PascalExports[0]) * 2);
static const long int PascalTypeCount = sizeof(PascalTypes) / (sizeof(PascalTypes[0]) * 2);

#ifdef __cplusplus
extern "C"
{
#endif
DLL_FUNC int GetPluginABIVersion();
DLL_FUNC int GetFunctionCount();
DLL_FUNC int GetTypeCount();
DLL_FUNC int GetFunctionInfo(int Index, void** Address, char** Definition);
DLL_FUNC int GetTypeInfo(int Index, char** Type, char** Definition);
#ifdef __cplusplus
}
#endif


                                    /** JAVA EXPORTS **/

#ifdef __cplusplus
extern "C"
{
#endif
JAVA_EXPORT jboolean Java_natives_Natives_CreateSocket(JNIEnv* env, jclass cls, jobject jssl_info);
JAVA_EXPORT jboolean Java_natives_Natives_ConnectSocket(JNIEnv* env, jclass cls, jobject jssl_info);
JAVA_EXPORT jboolean Java_natives_Natives_BindSocket(JNIEnv* env, jclass cls, jobject jssl_info);
JAVA_EXPORT jboolean Java_natives_Natives_ListenSocket(JNIEnv* env, jclass cls, jobject jssl_info);
JAVA_EXPORT jboolean Java_natives_Natives_SetBlockingSocket(JNIEnv* env, jclass cls, jobject jssl_info);
JAVA_EXPORT jboolean Java_natives_Natives_SetTimeoutSocket(JNIEnv* env, jclass cls, jobject jssl_info);
JAVA_EXPORT jint Java_natives_Natives_SelectSocket(JNIEnv* env, jclass cls, jobject jssl_info, jboolean read);
JAVA_EXPORT jboolean Java_natives_Natives_CloseSocket(JNIEnv* env, jclass cls, jobject jssl_info);
JAVA_EXPORT jboolean Java_natives_Natives_FreeSocket(JNIEnv* env, jclass cls, jobject jssl_info);
JAVA_EXPORT jboolean Java_natives_Natives_AcceptSocket(JNIEnv* env, jclass cls, jobject jssl_info, jobject jssl_client_info);
JAVA_EXPORT jint Java_natives_Natives_ReadSocket(JNIEnv* env, jclass cls, jobject jssl_info, jbyteArray Buffer);
JAVA_EXPORT jint Java_natives_Natives_WriteSocket(JNIEnv* env, jclass cls, jobject jssl_info, jbyteArray Buffer);
JAVA_EXPORT jint Java_natives_Natives_BytesPendingSocket(JNIEnv* env, jclass cls, jobject jssl_info);
#ifdef __cplusplus
}
#endif

#endif
