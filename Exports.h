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

#ifndef EXPORTS_HPP_INCLUDED
#define EXPORTS_HPP_INCLUDED

#if defined _WIN32 || defined _WIN64
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#ifdef BUILD_DLL
#define DLL_FUNC __declspec(dllexport)
#else
#define DLL_FUNC __declspec(dllimport)
#endif // BUILD_DLL

#if defined _WIN32 || defined _WIN64
extern HMODULE module;
#endif // defined

#ifndef __cplusplus
typedef enum {false, true} bool;
#endif

typedef enum
{
    TLS1_CLIENT_METHOD,
    TLS1_SERVER_METHOD,
    TLS11_CLIENT_METHOD,
    TLS11_SERVER_METHOD,
    SSL2_CLIENT_METHOD,
    SSL2_SERVER_METHOD,
    SSL3_CLIENT_METHOD,
    SSL3_SERVER_METHOD,
    SSL23_CLIENT_METHOD,
    SSL23_SERVER_METHOD
} SSLSocketType;

#pragma pack(push, 1)
typedef struct
{
    long unsigned int sock;
    SSL* ssl;
    SSL_CTX* ctx;
    const char* address;
    unsigned short port;
    SSLSocketType type;
    long unsigned int timeout;
    bool connected;
    bool blockmode;
} SSLSocket;
#pragma pack(pop)


#ifdef __cplusplus
extern "C"
{
#endif //defined
DLL_FUNC bool CreateSocket(SSLSocket* ssl_info);
DLL_FUNC bool ConnectSocket(SSLSocket* ssl_info);
DLL_FUNC bool BindSocket(SSLSocket* ssl_info);
DLL_FUNC bool ListenSocket(SSLSocket* ssl_info);
DLL_FUNC bool SetBlockingSocket(SSLSocket* ssl_info);
DLL_FUNC bool SetTimeoutSocket(SSLSocket* ssl_info);
DLL_FUNC int SelectSocket(SSLSocket* ssl_info, bool Read);
DLL_FUNC bool CloseSocket(SSLSocket* ssl_info);
DLL_FUNC bool FreeSocket(SSLSocket* ssl_info);
DLL_FUNC bool AcceptSocket(SSLSocket* ssl_info, SSLSocket* ssl_client_info);
DLL_FUNC long int ReadSocket(SSLSocket* ssl_info, void* Buffer, unsigned int Size);
DLL_FUNC long int WriteSocket(SSLSocket* ssl_info, void* Buffer, unsigned int Size);
DLL_FUNC long int BytesPendingSocket(SSLSocket* ssl_info);
#ifdef __cplusplus
}
#endif //defined

bool InitSSL(SSLSocket* ssl_info);
bool FreeSSL(SSLSocket* ssl_info);


#endif // EXPORTS_HPP_INCLUDED
