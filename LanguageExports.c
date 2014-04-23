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

#include "LanguageExports.h"

int GetPluginABIVersion()
{
    return 2;
}

int GetFunctionCount()
{
    return PascalExportCount;
}

int GetTypeCount()
{
	return PascalTypeCount;
}

int GetFunctionInfo(int Index, void** Address, char** Definition)
{
    if (Index < PascalExportCount)
    {
        *Address = (void*)GetProcAddress(module, PascalExports[Index * 2]);
        strcpy(*Definition, PascalExports[Index * 2 + 1]);
        return Index;
    }
    return -1;
}

int GetTypeInfo(int Index, char** Type, char** Definition)
{
	if (Index < PascalTypeCount)
	{
		strcpy(*Type, PascalTypes[Index * 2 + 0]);
		strcpy(*Definition, PascalTypes[Index * 2 + 1]);
		return Index;
	}
	return -1;
}

#if defined __cplusplus
void JSSLInfo_To_CSSLInfo(JNIEnv* env, jobject jssl_info, SSLSocket* ssl_info, jstring* addr)
{
    jclass cls = env->GetObjectClass(jssl_info);
    jclass tcls = env->FindClass("Lnatives/SSLSocketType;");

    jfieldID sockID = env->GetFieldID(cls, "sock", "I");
    jfieldID sslID = env->GetFieldID(cls, "ssl", "J");
    jfieldID ctxID = env->GetFieldID(cls, "ctx", "J");
    jfieldID addressID = env->GetFieldID(cls, "address", "Ljava/lang/String;");
    jfieldID portID = env->GetFieldID(cls, "port", "I");
    jfieldID typeID = env->GetFieldID(cls, "type", "Lnatives/SSLSocketType;");
    jfieldID timeoutID = env->GetFieldID(cls, "timeout", "I");
    jfieldID connectID = env->GetFieldID(cls, "connected", "Z");
    jfieldID blockmodeID = env->GetFieldID(cls, "blockmode", "Z");

    jobject typeObj = env->GetObjectField(jssl_info, typeID);
    jmethodID mTypeID = env->GetMethodID(tcls, "ordinal", "()I");

    ssl_info->sock = env->GetIntField(jssl_info, sockID);
    ssl_info->ssl = (SSL*)env->GetLongField(jssl_info, sslID);
    ssl_info->ctx = (SSL_CTX*)env->GetLongField(jssl_info, ctxID);

    *addr = (jstring)env->GetObjectField(jssl_info, addressID);

    ssl_info->address = env->GetStringUTFChars(*addr, 0);
    ssl_info->port = env->GetIntField(jssl_info, portID);
    ssl_info->type = (SSLSocketType)env->CallIntMethod(typeObj, mTypeID);
    ssl_info->timeout = env->GetIntField(jssl_info, timeoutID);
    ssl_info->connected = env->GetBooleanField(jssl_info, connectID);
    ssl_info->blockmode = env->GetBooleanField(jssl_info, blockmodeID);
}

void CSSLInfo_To_JSSLInfo(JNIEnv* env, jobject jssl_info, SSLSocket* ssl_info, jstring* addr)
{
    jclass cls = env->GetObjectClass(jssl_info);
    jfieldID sockID = env->GetFieldID(cls, "sock", "I");
    jfieldID sslID = env->GetFieldID(cls, "ssl", "J");
    jfieldID ctxID = env->GetFieldID(cls, "ctx", "J");
    jfieldID timeoutID = env->GetFieldID(cls, "timeout", "I");
    jfieldID connectID = env->GetFieldID(cls, "connected", "Z");
    jfieldID blockmodeID = env->GetFieldID(cls, "blockmode", "Z");

    env->SetIntField(jssl_info, sockID, ssl_info->sock);
    env->SetLongField(jssl_info, sslID, (jlong)ssl_info->ssl);
    env->SetLongField(jssl_info, ctxID, (jlong)ssl_info->ctx);
    env->SetBooleanField(jssl_info, timeoutID, (jint)ssl_info->timeout);
    env->SetBooleanField(jssl_info, connectID, ssl_info->connected);
    env->SetBooleanField(jssl_info, blockmodeID, ssl_info->blockmode);
    env->ReleaseStringUTFChars(*addr, ssl_info->address);
    *addr = NULL;
}

JAVA_EXPORT jboolean Java_natives_Natives_CreateSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    jstring addr = NULL;
    SSLSocket ssl_info = {0};
    JSSLInfo_To_CSSLInfo(env, jssl_info, &ssl_info, &addr);
    bool result = CreateSocket(&ssl_info);
    CSSLInfo_To_JSSLInfo(env, jssl_info, &ssl_info, &addr);
    return result;
}

JAVA_EXPORT jboolean Java_natives_Natives_ConnectSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    jstring addr = NULL;
    SSLSocket ssl_info = {0};
    JSSLInfo_To_CSSLInfo(env, jssl_info, &ssl_info, &addr);
    bool result = ConnectSocket(&ssl_info);
    CSSLInfo_To_JSSLInfo(env, jssl_info, &ssl_info, &addr);
    return result;
}

JAVA_EXPORT jboolean Java_natives_Natives_BindSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    jstring addr = NULL;
    SSLSocket ssl_info = {0};
    JSSLInfo_To_CSSLInfo(env, jssl_info, &ssl_info, &addr);
    bool result = BindSocket(&ssl_info);
    CSSLInfo_To_JSSLInfo(env, jssl_info, &ssl_info, &addr);
    return result;
}

JAVA_EXPORT jboolean Java_natives_Natives_ListenSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = env->GetObjectClass(jssl_info);
    jfieldID sockID = env->GetFieldID(ssl_cls, "sock", "I");
    ssl_info.sock = env->GetIntField(jssl_info, sockID);
    return ListenSocket(&ssl_info);
}

JAVA_EXPORT jboolean Java_natives_Natives_SetBlockingSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = env->GetObjectClass(jssl_info);
    jfieldID sockID = env->GetFieldID(ssl_cls, "sock", "I");
    jfieldID blockmodeID = env->GetFieldID(ssl_cls, "blockmode", "Z");

    ssl_info.sock = env->GetIntField(jssl_info, sockID);
    ssl_info.blockmode = env->GetBooleanField(jssl_info, sockID);
    bool Result = SetBlockingSocket(&ssl_info);
    env->SetBooleanField(jssl_info, blockmodeID, ssl_info.blockmode);
    return Result;
}

JAVA_EXPORT jboolean Java_natives_Natives_SetTimeoutSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = env->GetObjectClass(jssl_info);
    jfieldID sockID = env->GetFieldID(ssl_cls, "sock", "I");
    jfieldID blockmodeID = env->GetFieldID(ssl_cls, "blockmode", "Z");
    jfieldID timeoutID = env->GetFieldID(ssl_cls, "timeout", "I");

    ssl_info.sock = env->GetIntField(jssl_info, sockID);
    ssl_info.blockmode = env->GetBooleanField(jssl_info, blockmodeID);
    ssl_info.timeout = env->GetIntField(jssl_info, timeoutID);
    return SetTimeoutSocket(&ssl_info);
}

JAVA_EXPORT jint Java_natives_Natives_SelectSocket(JNIEnv* env, jclass cls, jobject jssl_info, jboolean read)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = env->GetObjectClass(jssl_info);
    jfieldID sockID = env->GetFieldID(ssl_cls, "sock", "I");
    jfieldID blockmodeID = env->GetFieldID(ssl_cls, "blockmode", "Z");
    jfieldID timeoutID = env->GetFieldID(ssl_cls, "timeout", "I");

    ssl_info.sock = env->GetIntField(jssl_info, sockID);
    ssl_info.blockmode = env->GetBooleanField(jssl_info, blockmodeID);
    ssl_info.timeout = env->GetIntField(jssl_info, timeoutID);
    return SelectSocket(&ssl_info, read);
}

JAVA_EXPORT jboolean Java_natives_Natives_CloseSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    jstring addr = NULL;
    SSLSocket ssl_info = {0};
    JSSLInfo_To_CSSLInfo(env, jssl_info, &ssl_info, &addr);
    bool result = CloseSocket(&ssl_info);
    CSSLInfo_To_JSSLInfo(env, jssl_info, &ssl_info, &addr);
    return result;
}

JAVA_EXPORT jboolean Java_natives_Natives_FreeSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    jstring addr = NULL;
    SSLSocket ssl_info = {0};
    JSSLInfo_To_CSSLInfo(env, jssl_info, &ssl_info, &addr);
    bool result = FreeSocket(&ssl_info);
    CSSLInfo_To_JSSLInfo(env, jssl_info, &ssl_info, &addr);
    return result;
}

JAVA_EXPORT jboolean Java_natives_Natives_AcceptSocket(JNIEnv* env, jclass cls, jobject jssl_info, jobject jssl_client_info)
{
    SSLSocket ssl_info = {0};
    SSLSocket ssl_client_info = {0};
    jclass ssl_cls = env->GetObjectClass(jssl_info);
    jfieldID sslID = env->GetFieldID(ssl_cls, "ssl", "J");
    jfieldID sockID = env->GetFieldID(ssl_cls, "sock", "J");

    ssl_info.ssl = (SSL*)env->GetLongField(jssl_info, sslID);
    bool result = AcceptSocket(&ssl_info, &ssl_client_info);
    env->SetLongField(jssl_client_info, sslID, (jlong)ssl_client_info.ssl);
    env->SetLongField(jssl_client_info, sockID, ssl_client_info.sock);
    return result;
}

JAVA_EXPORT jint Java_natives_Natives_ReadSocket(JNIEnv* env, jclass cls, jobject jssl_info, jbyteArray Buffer)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = env->GetObjectClass(jssl_info);
    jfieldID sslID = env->GetFieldID(ssl_cls, "ssl", "J");
    ssl_info.ssl = (SSL*)env->GetLongField(jssl_info, sslID);

    jbyte* buffer = env->GetByteArrayElements(Buffer, 0);
    jint Size = env->GetArrayLength(Buffer);
    jint result = ReadSocket(&ssl_info, buffer, Size);
    env->ReleaseByteArrayElements(Buffer, buffer, 0);
    return result;
}

JAVA_EXPORT jint Java_natives_Natives_WriteSocket(JNIEnv* env, jclass cls, jobject jssl_info, jbyteArray Buffer)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = env->GetObjectClass(jssl_info);
    jfieldID sslID = env->GetFieldID(ssl_cls, "ssl", "J");
    ssl_info.ssl = (SSL*)env->GetLongField(jssl_info, sslID);

    jbyte* buffer = env->GetByteArrayElements(Buffer, 0);
    jint Size = env->GetArrayLength(Buffer);
    jint result = WriteSocket(&ssl_info, buffer, Size);
    env->ReleaseByteArrayElements(Buffer, buffer, 0);
    return result;
}

JAVA_EXPORT jint Java_natives_Natives_BytesPendingSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = env->GetObjectClass(jssl_info);
    jfieldID sslID = env->GetFieldID(ssl_cls, "ssl", "J");
    ssl_info.ssl = (SSL*)env->GetLongField(jssl_info, sslID);
    return BytesPendingSocket(&ssl_info);
}
#else
void JSSLInfo_To_CSSLInfo(JNIEnv* env, jobject jssl_info, SSLSocket* ssl_info, jstring* addr)
{
    jclass cls = (*env)->GetObjectClass(env, jssl_info);
    jclass tcls = (*env)->FindClass(env, "Lnatives/SSLSocketType;");

    jfieldID sockID = (*env)->GetFieldID(env, cls, "sock", "I");
    jfieldID sslID = (*env)->GetFieldID(env, cls, "ssl", "J");
    jfieldID ctxID = (*env)->GetFieldID(env, cls, "ctx", "J");
    jfieldID addressID = (*env)->GetFieldID(env, cls, "address", "Ljava/lang/String;");
    jfieldID portID = (*env)->GetFieldID(env, cls, "port", "I");
    jfieldID typeID = (*env)->GetFieldID(env, cls, "type", "Lnatives/SSLSocketType;");
    jfieldID timeoutID = (*env)->GetFieldID(env, cls, "timeout", "I");
    jfieldID connectID = (*env)->GetFieldID(env, cls, "connected", "Z");
    jfieldID blockmodeID = (*env)->GetFieldID(env, cls, "blockmode", "Z");

    jobject typeObj = (*env)->GetObjectField(env, jssl_info, typeID);
    jmethodID mTypeID = (*env)->GetMethodID(env, tcls, "ordinal", "()I");

    ssl_info->sock = (*env)->GetIntField(env, jssl_info, sockID);
    ssl_info->ssl = (SSL*)(*env)->GetLongField(env, jssl_info, sslID);
    ssl_info->ctx = (SSL_CTX*)(*env)->GetLongField(env, jssl_info, ctxID);

    *addr = (jstring)(*env)->GetObjectField(env, jssl_info, addressID);

    ssl_info->address = (*env)->GetStringUTFChars(env, *addr, 0);
    ssl_info->port = (*env)->GetIntField(env, jssl_info, portID);
    ssl_info->type = (SSLSocketType)(*env)->CallIntMethod(env, typeObj, mTypeID);
    ssl_info->timeout = (*env)->GetIntField(env, jssl_info, timeoutID);
    ssl_info->connected = (*env)->GetBooleanField(env, jssl_info, connectID);
    ssl_info->blockmode = (*env)->GetBooleanField(env, jssl_info, blockmodeID);
}

void CSSLInfo_To_JSSLInfo(JNIEnv* env, jobject jssl_info, SSLSocket* ssl_info, jstring* addr)
{
    jclass cls = (*env)->GetObjectClass(env, jssl_info);
    jfieldID sockID = (*env)->GetFieldID(env, cls, "sock", "I");
    jfieldID sslID = (*env)->GetFieldID(env, cls, "ssl", "J");
    jfieldID ctxID = (*env)->GetFieldID(env, cls, "ctx", "J");
    jfieldID timeoutID = (*env)->GetFieldID(env, cls, "timeout", "I");
    jfieldID connectID = (*env)->GetFieldID(env, cls, "connected", "Z");
    jfieldID blockmodeID = (*env)->GetFieldID(env, cls, "blockmode", "Z");

    (*env)->SetIntField(env, jssl_info, sockID, ssl_info->sock);
    (*env)->SetLongField(env, jssl_info, sslID, (jlong)ssl_info->ssl);
    (*env)->SetLongField(env, jssl_info, ctxID, (jlong)ssl_info->ctx);
    (*env)->SetBooleanField(env, jssl_info, timeoutID, (jint)ssl_info->timeout);
    (*env)->SetBooleanField(env, jssl_info, connectID, ssl_info->connected);
    (*env)->SetBooleanField(env, jssl_info, blockmodeID, ssl_info->blockmode);
    (*env)->ReleaseStringUTFChars(env, *addr, ssl_info->address);
    *addr = NULL;
}

JAVA_EXPORT jboolean Java_natives_Natives_CreateSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    jstring addr = NULL;
    SSLSocket ssl_info = {0};
    JSSLInfo_To_CSSLInfo(env, jssl_info, &ssl_info, &addr);
    bool result = CreateSocket(&ssl_info);
    CSSLInfo_To_JSSLInfo(env, jssl_info, &ssl_info, &addr);
    return result;
}

JAVA_EXPORT jboolean Java_natives_Natives_ConnectSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    jstring addr = NULL;
    SSLSocket ssl_info = {0};
    JSSLInfo_To_CSSLInfo(env, jssl_info, &ssl_info, &addr);
    bool result = ConnectSocket(&ssl_info);
    CSSLInfo_To_JSSLInfo(env, jssl_info, &ssl_info, &addr);
    return result;
}

JAVA_EXPORT jboolean Java_natives_Natives_BindSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    jstring addr = NULL;
    SSLSocket ssl_info = {0};
    JSSLInfo_To_CSSLInfo(env, jssl_info, &ssl_info, &addr);
    bool result = BindSocket(&ssl_info);
    CSSLInfo_To_JSSLInfo(env, jssl_info, &ssl_info, &addr);
    return result;
}

JAVA_EXPORT jboolean Java_natives_Natives_ListenSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = (*env)->GetObjectClass(env, jssl_info);
    jfieldID sockID = (*env)->GetFieldID(env, ssl_cls, "sock", "I");
    ssl_info.sock = (*env)->GetIntField(env, jssl_info, sockID);
    return ListenSocket(&ssl_info);
}

JAVA_EXPORT jboolean Java_natives_Natives_SetBlockingSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = (*env)->GetObjectClass(env, jssl_info);
    jfieldID sockID = (*env)->GetFieldID(env, ssl_cls, "sock", "I");
    jfieldID blockmodeID = (*env)->GetFieldID(env, ssl_cls, "blockmode", "Z");

    ssl_info.sock = (*env)->GetIntField(env, jssl_info, sockID);
    ssl_info.blockmode = (*env)->GetBooleanField(env, jssl_info, sockID);
    bool Result = SetBlockingSocket(&ssl_info);
    (*env)->SetBooleanField(env, jssl_info, blockmodeID, ssl_info.blockmode);
    return Result;
}

JAVA_EXPORT jboolean Java_natives_Natives_SetTimeoutSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = (*env)->GetObjectClass(env, jssl_info);
    jfieldID sockID = (*env)->GetFieldID(env, ssl_cls, "sock", "I");
    jfieldID blockmodeID = (*env)->GetFieldID(env, ssl_cls, "blockmode", "Z");
    jfieldID timeoutID = (*env)->GetFieldID(env, ssl_cls, "timeout", "I");

    ssl_info.sock = (*env)->GetIntField(env, jssl_info, sockID);
    ssl_info.blockmode = (*env)->GetBooleanField(env, jssl_info, blockmodeID);
    ssl_info.timeout = (*env)->GetIntField(env, jssl_info, timeoutID);
    return SetTimeoutSocket(&ssl_info);
}

JAVA_EXPORT jint Java_natives_Natives_SelectSocket(JNIEnv* env, jclass cls, jobject jssl_info, jboolean read)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = (*env)->GetObjectClass(env, jssl_info);
    jfieldID sockID = (*env)->GetFieldID(env, ssl_cls, "sock", "I");
    jfieldID blockmodeID = (*env)->GetFieldID(env, ssl_cls, "blockmode", "Z");
    jfieldID timeoutID = (*env)->GetFieldID(env, ssl_cls, "timeout", "I");

    ssl_info.sock = (*env)->GetIntField(env, jssl_info, sockID);
    ssl_info.blockmode = (*env)->GetBooleanField(env, jssl_info, blockmodeID);
    ssl_info.timeout = (*env)->GetIntField(env, jssl_info, timeoutID);
    return SelectSocket(&ssl_info, read);
}

JAVA_EXPORT jboolean Java_natives_Natives_CloseSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    jstring addr = NULL;
    SSLSocket ssl_info = {0};
    JSSLInfo_To_CSSLInfo(env, jssl_info, &ssl_info, &addr);
    bool result = CloseSocket(&ssl_info);
    CSSLInfo_To_JSSLInfo(env, jssl_info, &ssl_info, &addr);
    return result;
}

JAVA_EXPORT jboolean Java_natives_Natives_FreeSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    jstring addr = NULL;
    SSLSocket ssl_info = {0};
    JSSLInfo_To_CSSLInfo(env, jssl_info, &ssl_info, &addr);
    bool result = FreeSocket(&ssl_info);
    CSSLInfo_To_JSSLInfo(env, jssl_info, &ssl_info, &addr);
    return result;
}

JAVA_EXPORT jboolean Java_natives_Natives_AcceptSocket(JNIEnv* env, jclass cls, jobject jssl_info, jobject jssl_client_info)
{
    SSLSocket ssl_info = {0};
    SSLSocket ssl_client_info = {0};
    jclass ssl_cls = (*env)->GetObjectClass(env, jssl_info);
    jfieldID sslID = (*env)->GetFieldID(env, ssl_cls, "ssl", "J");
    jfieldID sockID = (*env)->GetFieldID(env, ssl_cls, "sock", "J");

    ssl_info.ssl = (SSL*)(*env)->GetLongField(env, jssl_info, sslID);
    bool result = AcceptSocket(&ssl_info, &ssl_client_info);
    (*env)->SetLongField(env, jssl_client_info, sslID, (jlong)ssl_client_info.ssl);
    (*env)->SetLongField(env, jssl_client_info, sockID, ssl_client_info.sock);
    return result;
}

JAVA_EXPORT jint Java_natives_Natives_ReadSocket(JNIEnv* env, jclass cls, jobject jssl_info, jbyteArray Buffer)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = (*env)->GetObjectClass(env, jssl_info);
    jfieldID sslID = (*env)->GetFieldID(env, ssl_cls, "ssl", "J");
    ssl_info.ssl = (SSL*)(*env)->GetLongField(env, jssl_info, sslID);

    jbyte* buffer = (*env)->GetByteArrayElements(env, Buffer, 0);
    jint Size = (*env)->GetArrayLength(env, Buffer);
    jint result = ReadSocket(&ssl_info, buffer, Size);
    (*env)->ReleaseByteArrayElements(env, Buffer, buffer, 0);
    return result;
}

JAVA_EXPORT jint Java_natives_Natives_WriteSocket(JNIEnv* env, jclass cls, jobject jssl_info, jbyteArray Buffer)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = (*env)->GetObjectClass(env, jssl_info);
    jfieldID sslID = (*env)->GetFieldID(env, ssl_cls, "ssl", "J");
    ssl_info.ssl = (SSL*)(*env)->GetLongField(env, jssl_info, sslID);

    jbyte* buffer = (*env)->GetByteArrayElements(env, Buffer, 0);
    jint Size = (*env)->GetArrayLength(env, Buffer);
    jint result = WriteSocket(&ssl_info, buffer, Size);
    (*env)->ReleaseByteArrayElements(env, Buffer, buffer, 0);
    return result;
}

JAVA_EXPORT jint Java_natives_Natives_BytesPendingSocket(JNIEnv* env, jclass cls, jobject jssl_info)
{
    SSLSocket ssl_info = {0};
    jclass ssl_cls = (*env)->GetObjectClass(env, jssl_info);
    jfieldID sslID = (*env)->GetFieldID(env, ssl_cls, "ssl", "J");
    ssl_info.ssl = (SSL*)(*env)->GetLongField(env, jssl_info, sslID);
    return BytesPendingSocket(&ssl_info);
}
#endif //defined