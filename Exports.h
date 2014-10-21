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

#ifdef CURL_SSL
#include "CurlSSL.h"
#endif

#ifndef __cplusplus
#if __STDC_VERSION__ >= 199901L
#define standard_c_1999
#include <stdbool.h>
#elifndef bool_defined
typedef enum {false, true} bool;
#endif
#endif

#ifndef DLL_FUNC
#ifdef BUILD_DLL
#define DLL_FUNC __declspec(dllexport)
#else
#define DLL_FUNC __declspec(dllimport)
#endif
#endif

#if defined _WIN32 || defined _WIN64
extern HMODULE module;
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
    SSLSocketType type;
    long unsigned int timeout;
    unsigned short port;
    #if defined __cplusplus || defined standard_c_1999
    bool connected;
    bool blockmode;
    #else
    unsigned char connected;
    unsigned char blockmode;
    #endif
} SSLSocket;
#pragma pack(pop)


#ifdef __cplusplus
extern "C"
{
#endif
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
#endif

#ifdef __cplusplus
extern "C"
{
#endif
bool InitSSL(SSLSocket* ssl_info);
bool FreeSSL(SSLSocket* ssl_info);


#ifdef DEBUG
void PrintLastError(int errorcode);
void PrintSocketInfo(SSLSocket* ssl_info);
#endif
#ifdef __cplusplus
}
#endif


#endif
