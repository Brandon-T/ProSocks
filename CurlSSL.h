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

#ifndef CURL_H_INCLUDED
#define CURL_H_INCLUDED

#include <curl/curl.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __cplusplus
#if __STDC_VERSION__ >= 199901L
#define standard_c_1999
#include <stdbool.h>
#else
#define bool_defined
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

#pragma pack(push, 1)
typedef struct
{
    char *memory;
    size_t size;
} CurlMemoryStruct;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    CURL *curl_handle;
    char* headers;
    char* data;
    char* params;

    size_t (*func_str_len)(void *str);
    size_t (*func_error_handler)(const void* str, long errorcode);
    size_t (*func_write_buffer)(void *contents, size_t size, size_t nmemb, void *userp);
    size_t (*func_write_header)(void *contents, size_t size, size_t nmemb, void *userp);

    struct curl_slist* hdrs;
    long unsigned int timeout;
    unsigned short port;
    #if defined __cplusplus || defined standard_c_1999
    bool caller_allocates;
    #else
    unsigned char caller_allocates;
    #endif
} CurlSock;
#pragma pack(pop)

#ifdef __cplusplus
extern "C"
{
#endif
DLL_FUNC void Curl_InitMemoryStruct(CurlMemoryStruct** ptr);
DLL_FUNC void Curl_FreeMemoryStruct(CurlMemoryStruct** ptr);

DLL_FUNC void Curl_InitSocket(CurlSock* curl_info,
                  size_t (*func_write_buffer)(void *contents, size_t size, size_t nmemb, void *userp),
                  size_t (*func_write_header)(void *contents, size_t size, size_t nmemb, void *userp),
                  size_t (*func_error_handler)(const void* str, long errorcode),
                  size_t (*func_str_len)(void *str)
                  );

DLL_FUNC void Curl_CreateSocket(CurlSock* curl_info, const char* useragent);
DLL_FUNC void Curl_FreeSocket(CurlSock* curl_info);
DLL_FUNC void Curl_SetURLFollow(CurlSock* curl_info, bool follow);
DLL_FUNC void Curl_SetSSL(CurlSock* curl_info, bool tryset, bool VerifyPeer, bool VerifyHost);
DLL_FUNC void Curl_SetCookies(CurlSock* curl_info, const char *CookieJar, const char *CookieFile);
DLL_FUNC void Curl_SetHeaderCapture(CurlSock* curl_info, bool Enable);
DLL_FUNC bool Curl_SetHeader(CurlSock* curl_info, const char* Key, const char* Value);
DLL_FUNC void Curl_CustomRequest(CurlSock* curl_info, const char* request);
DLL_FUNC void Curl_SetNoBody(CurlSock* curl_info, bool Enabled);
DLL_FUNC void Curl_SetVerbose(CurlSock* curl_info, bool Enabled);

DLL_FUNC const char* Curl_GetHostLocation(const char* address, char* buffer);
DLL_FUNC const char* Curl_GetRequestLocation(const char* address, char* buffer);
DLL_FUNC void Curl_SetURL(CurlSock* curl_info, const char *URL);
DLL_FUNC void Curl_SetUpload(CurlSock* curl_info, bool Enabled);
DLL_FUNC void Curl_SetLogin(CurlSock* curl_info, const char* username, const char* password);
DLL_FUNC void Curl_ClearParams(CurlSock* curl_info);
DLL_FUNC bool Curl_AddParameter(CurlSock* curl_info, const char *Key, const char *Value, bool Escape);
DLL_FUNC CurlMemoryStruct* Curl_DoGet(CurlSock* curl_info);
DLL_FUNC CurlMemoryStruct* Curl_DoPost(CurlSock* curl_info);
DLL_FUNC CurlMemoryStruct* Curl_Perform(CurlSock* curl_info);
DLL_FUNC CurlMemoryStruct* Curl_GetHeaders(CurlSock* curl_info);

DLL_FUNC bool Curl_SMTP(CurlSock* curl_info, const char* url, const char* user, const char* pwd, const char* name, const char* to, const char* cc, const char* bcc, const char* subject, const char* body, const char* bodymime, const char* file, const char* filemime);
#ifdef __cplusplus
}
#endif

#endif // CURL_H_INCLUDED
