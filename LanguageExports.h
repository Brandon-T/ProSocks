/**  © 2014, Brandon T. All Rights Reserved.
  *
  *  This file is part of the ProSock Library.
  *  You may use this file only for your personal, and non-commercial use.
  *  You may not modify or use the contents of this file for any purpose (other
  *  than as specified above) without the express written consent of the author.
  *  You may not reproduce, republish, post, transmit, publicly display,
  *  publicly perform, or distribute in print or electronically any of the contents
  *  of this file without express consent of rightful owner.
  *  This License is subject to change at any time without notice/warning.
  *
  *						Author : Brandon T.
  *						Contact: Brandon.T-@Live.com
  */

#ifndef LANGUAGEEXPORTS_HPP_INCLUDED
#define LANGUAGEEXPORTS_HPP_INCLUDED

#include "Exports.h"
#include "jni.h"

#define JAVA_EXPORT __declspec(dllexport)



                                    /** PASCAL EXPORTS **/

static const char* PascalExports[] =
{
    "AcceptSocket", "Function Pro_AcceptSocket(ssl_info, ssl_client_info: ^SSLSocket): Boolean;",
    "BindSocket", "Function Pro_BindSocket(ssl_info: ^SSLSocket): Boolean;",
    "BytesPendingSocket", "Function Pro_BytesPendingSocket(ssl_info: ^SSLSocket): Integer;",
    "CreateSocket", "Function Pro_CreateSocket(ssl_info: ^SSLSocket): Boolean;",
    "ConnectSocket", "Function Pro_ConnectSocket(ssl_info: ^SSLSocket): Boolean;",
    "ListenSocket", "Function Pro_ListenSocket(ssl_info: ^SSLSocket): Boolean;",
    "SetBlockingSocket", "Function Pro_SetBlockingSocket(ssl_info: ^SSLSocket): Boolean;",
    "SetTimeoutSocket", "Function Pro_SetTimeoutSocket(ssl_info: ^SSLSocket): Boolean;",
    "SelectSocket", "Function Pro_SelectSocket(ssl_info: ^SSLSocket; Read: Boolean): Integer;",
    "CloseSocket", "Function Pro_CloseSocket(ssl_info: ^SSLSocket): Boolean;",
    "FreeSocket", "Function Pro_FreeSocket(ssl_info: ^SSLSocket): Boolean;",
    "ReadSocket", "Function Pro_ReadSocket(ssl_info: ^SSLSocket; Buffer: ^Char; Size: Cardinal): Integer;",
    "WriteSocket", "Function Pro_WriteSocket(ssl_info: ^SSLSocket; Buffer: String; Size: Cardinal): Integer;"
};

static const char* PascalTypes[] =
{
	"SSLSocketType", "(TLS1_CLIENT_METHOD,\
								TLS1_SERVER_METHOD,\
								TLS11_CLIENT_METHOD,\
								TLS11_SERVER_METHOD,\
								SSL2_CLIENT_METHOD,\
								SSL2_SERVER_METHOD,\
								SSL3_CLIENT_METHOD,\
								SSL3_SERVER_METHOD,\
								SSL23_CLIENT_METHOD,\
								SSL23_SERVER_METHOD);",

	#ifndef x86_64
	"SSLSocket", "packed record\
							sock: Cardinal;\
							ssl: Cardinal;\
							ctx: Cardinal;\
							address: PChar;\
							port: Word;\
							socktype: SSLSocketType;\
							timeout: Cardinal;\
							connected: Boolean;\
							blockmode: Boolean;\
						end;",
	#else
	"SSLSocket", "packed record\
							sock: Cardinal;\
							ssl: Int64;\
							ctx: Int64;\
							address: PChar64;\
							port: Word;\
							socktype: SSLSocketType;\
							timeout: Cardinal;\
							connected: Boolean;\
							blockmode: Boolean;\
						end;"
	#endif
};

static const long int PascalExportCount = sizeof(PascalExports) / (sizeof(PascalExports[0]) * 2);
static const long int PascalTypeCount = sizeof(PascalTypes) / (sizeof(PascalTypes[0]) * 2);

#ifdef __cplusplus
extern "C"
{
#endif //defined
DLL_FUNC int GetPluginABIVersion();
DLL_FUNC int GetFunctionCount();
DLL_FUNC int GetTypeCount();
DLL_FUNC int GetFunctionInfo(int Index, void** Address, char** Definition);
DLL_FUNC int GetTypeInfo(int Index, char** Type, char** Definition);
#ifdef __cplusplus
}
#endif //defined


                                    /** JAVA EXPORTS **/

#ifdef __cplusplus
extern "C"
{
#endif //defined
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
#endif //defined

#endif // LANGUAGEEXPORTS_HPP_INCLUDED
