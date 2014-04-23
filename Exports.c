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

#include "Exports.h"

#if defined _WIN32 || defined _WIN64
HMODULE module = NULL;
#endif // defined

#if defined _WIN32 || defined _WIN64
/*const char* inet_ntop(int af, const void* src, char* dst, socklen_t cnt)
{
    struct sockaddr_in srcaddr = {0};
    memset(&srcaddr, 0, sizeof(struct sockaddr_in));
    memcpy(&srcaddr.sin_addr, src, sizeof(srcaddr.sin_addr));

    srcaddr.sin_family = af;
    return WSAAddressToString((struct sockaddr*) &srcaddr, sizeof(struct sockaddr_in), 0, dst, (LPDWORD) &cnt) ? dst : NULL;
}*/

const char* inet_ntop(int af, const void* src, char* dst, socklen_t cnt)
{
    if (af == AF_INET)
    {
        struct sockaddr_in in;
        memset(&in, 0, sizeof(in));
        in.sin_family = AF_INET;
        memcpy(&in.sin_addr, src, sizeof(struct in_addr));
        getnameinfo((struct sockaddr*)&in, sizeof(struct sockaddr_in), dst, cnt, NULL, 0, NI_NUMERICHOST);
        return dst;
    }
    else if (af == AF_INET6)
    {
        struct sockaddr_in6 in;
        memset(&in, 0, sizeof(in));
        in.sin6_family = AF_INET6;
        memcpy(&in.sin6_addr, src, sizeof(struct in_addr6));
        getnameinfo((struct sockaddr*)&in, sizeof(struct sockaddr_in6), dst, cnt, NULL, 0, NI_NUMERICHOST);
        return dst;
    }
    return NULL;
}

int inet_pton(int af, const char* src, void* dst)
{
    struct addrinfo hints, *res, *ressave;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = af;

    if (!getaddrinfo(src, NULL, &hints, &res))
    {
        ressave = res;
        while (res)
        {
            memcpy(dst, res->ai_addr, res->ai_addrlen);
            res = res->ai_next;
        }
        freeaddrinfo(ressave);
        return 0;
    }
    return -1;
}
#endif // defined

bool CreateSocket(SSLSocket* ssl_info)
{
    ssl_info->sock = 0;
    ssl_info->ssl = NULL;
    ssl_info->ctx = NULL;
    ssl_info->connected = false;

    #if defined _WIN32 || defined _WIN64
    WSADATA wsaData = {0};
    return !WSAStartup(MAKEWORD(2, 2), &wsaData);
    #else
    return true;
    #endif
}

bool ConnectSocket(SSLSocket* ssl_info)
{
    struct addrinfo hints = {0};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    char port[6] = {0};
    sprintf(&port[0], "%d", ssl_info->port);

    struct addrinfo* it = NULL, *result = NULL;
    getaddrinfo(ssl_info->address, &port[0], &hints, &result);

    for (it = result; it != NULL; it = it->ai_next)
    {
        if ((ssl_info->sock = socket(it->ai_family, it->ai_socktype, it->ai_protocol)) != INVALID_SOCKET)
        {
            SetBlockingSocket(ssl_info);
            SetTimeoutSocket(ssl_info);
            if (connect(ssl_info->sock, it->ai_addr, it->ai_addrlen) == SOCKET_ERROR)
            {
                #if defined _WIN32 || defined _WIN64
                long unsigned int err = WSAGetLastError();
                if (err != WSAEWOULDBLOCK)
                {
                    closesocket(ssl_info->sock);
                    ssl_info->sock = 0;
                }
                #else
                long unsigned int err = errno;
                if (err != EWOULDBLOCK && err != EAGAIN)
                {
                    close(ssl_info->sock);
                    ssl_info->sock = 0;
                }
                #endif
            }
            break;
        }
    }

    freeaddrinfo(result);
    return ssl_info->sock ? InitSSL(ssl_info) : false;
}

bool BindSocket(SSLSocket* ssl_info)
{
    struct addrinfo hints = {0};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    char port[6] = {0};
    sprintf(&port[0], "%d", ssl_info->port);

    struct addrinfo* it = NULL, *result = NULL;
    getaddrinfo(ssl_info->address, &port[0], &hints, &result);

    for (it = result; it != NULL; it = it->ai_next)
    {
        if ((ssl_info->sock = socket(it->ai_family, it->ai_socktype, it->ai_protocol)) != INVALID_SOCKET)
        {
            char yes = '1';
            SetBlockingSocket(ssl_info);
            SetTimeoutSocket(ssl_info);
            setsockopt(ssl_info->sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
            if (bind(ssl_info->sock, it->ai_addr, it->ai_addrlen) == SOCKET_ERROR)
            {
                #if defined _WIN32 || defined _WIN64
                if (WSAGetLastError() != EWOULDBLOCK && WSAGetLastError() != EAGAIN)
                {
                    closesocket(ssl_info->sock);
                    ssl_info->sock = 0;
                }
                #else
                if (errno != EWOULDBLOCK && ernno != EAGAIN)
                {
                    close(ssl_info->sock);
                    ssl_info->sock = 0;
                }
                #endif
            }
            break;
        }
    }

    freeaddrinfo(result);
    return ssl_info->sock ? InitSSL(ssl_info) : false;
}

bool ListenSocket(SSLSocket* ssl_info)
{
    return listen(ssl_info->sock, SOMAXCONN) != SOCKET_ERROR;
}

bool SetBlockingSocket(SSLSocket* ssl_info)
{
    #if defined _WIN32 || defined _WIN64
    unsigned long int mode = ssl_info->blockmode ? 0 : 1;
    return !ioctlsocket(ssl_info->sock, FIONBIO, &mode);
    #elif defined O_NONBLOCK
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) return false;
    flags = ssl_info->blockmode ? (flags &~ O_NONBLOCK) : (flags | O_NONBLOCK);
    return !fcntl(fd, F_SETFL, flags);
    #else
    unsigned long int mode = sock_info->blockmode ? 0 : 1;
    return ioctl(sock_info->sock, FIOBIO, &mode);
    #endif //defined
}

bool SetTimeoutSocket(SSLSocket* ssl_info)
{
    bool result = false;
    #if defined _WIN32 || defined _WIN64
    result = setsockopt(ssl_info->sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&ssl_info->timeout, sizeof(ssl_info->timeout));
    result = result && setsockopt(ssl_info->sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&ssl_info->timeout, sizeof(ssl_info->timeout));
    #else
    struct timeval tv = {0};
    tv.tv_sec = ssl_info->timeout / 1000;
    tv.tv_usec = ssl_info->timeout % 1000;
    result = setsockopt(ssl_info->sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));
    result = result && setsockopt(ssl_info->sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(tv));
    #endif // defined
    return result;
}

void LastError(int errorcode)
{
    #if defined _WIN32 || defined _WIN64
    char* s = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&s, 0, NULL);
    printf("\n%s\n", s);
    LocalFree(s);
    #else
    perror(errorcode);
    #endif //defined
}

int SelectSocket(SSLSocket* ssl_info, bool Read)
{
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(ssl_info->sock, &fds);
    struct timeval tv = {0};
    tv.tv_sec = ssl_info->timeout / 1000;
    tv.tv_usec = ssl_info->timeout % 1000;
    return select(ssl_info->sock + 1, Read ? &fds : NULL, Read ? NULL : &fds, NULL, &tv);
}

bool CloseSocket(SSLSocket* ssl_info)
{
    if (ssl_info->sock)
    {
        #if defined _WIN32 || defined _WIN64
        closesocket(ssl_info->sock);
        #else
        close(ssl_info->sock);
        #endif
        shutdown(ssl_info->sock, SD_BOTH);
        ssl_info->sock = 0;
        return true;
    }
    return false;
}

bool FreeSocket(SSLSocket* ssl_info)
{
    bool Result = FreeSSL(ssl_info);
    return CloseSocket(ssl_info) && Result;
}

bool AcceptSocket(SSLSocket* ssl_info, SSLSocket* ssl_client_info)
{
    static int size = sizeof(struct sockaddr);
    static struct sockaddr* client_info = NULL;
    ssl_client_info->sock = accept(ssl_info->sock, client_info, &size);

    if (ssl_client_info->sock != INVALID_SOCKET)
    {
        if (InitSSL(ssl_client_info))
        {
            return SSL_accept(ssl_client_info->ssl) == 1;
        }
        #if defined _WIN32 || defined _WIN64
        closesocket(ssl_client_info->sock);
        #else
        close(ssl_client_info->sock);
        #endif // defined
    }
    return false;
}

long int ReadSocket(SSLSocket* ssl_info, void* Buffer, unsigned int Size)
{
    return SSL_read(ssl_info->ssl, Buffer, Size);
}

long int WriteSocket(SSLSocket* ssl_info, void* Buffer, unsigned int Size)
{
    return SSL_write(ssl_info->ssl, Buffer, Size);
}

long int BytesPendingSocket(SSLSocket* ssl_info)
{
    return SSL_pending(ssl_info->ssl);
}

bool InitSSL(SSLSocket* ssl_info)
{
    if (!ssl_info->ctx)
    {
        switch(ssl_info->type)
        {
            case TLS1_CLIENT_METHOD:
                ssl_info->ctx = SSL_CTX_new(TLSv1_client_method());
                break;

            case TLS1_SERVER_METHOD:
                ssl_info->ctx = SSL_CTX_new(TLSv1_server_method());
                break;

            case TLS11_CLIENT_METHOD:
                ssl_info->ctx = SSL_CTX_new(TLSv1_1_client_method());
                break;

            case TLS11_SERVER_METHOD:
                ssl_info->ctx = SSL_CTX_new(TLSv1_1_server_method());
                break;

            case SSL2_CLIENT_METHOD:
                ssl_info->ctx = SSL_CTX_new(SSLv2_client_method());
                break;

            case SSL2_SERVER_METHOD:
                ssl_info->ctx = SSL_CTX_new(SSLv2_server_method());
                break;

            case SSL3_CLIENT_METHOD:
                ssl_info->ctx = SSL_CTX_new(SSLv3_client_method());
                break;

            case SSL3_SERVER_METHOD:
                ssl_info->ctx = SSL_CTX_new(SSLv3_server_method());
                break;

            case SSL23_CLIENT_METHOD:
                ssl_info->ctx = SSL_CTX_new(SSLv23_client_method());
                break;

            case SSL23_SERVER_METHOD:
                ssl_info->ctx = SSL_CTX_new(SSLv23_server_method());
                break;

            default:
                FreeSSL(ssl_info);
                return false;
        }
    }

    if (!ssl_info->ssl)
    {
        ssl_info->ssl = SSL_new(ssl_info->ctx);
        SSL_set_fd(ssl_info->ssl, ssl_info->sock);
    }

    return ssl_info->connected = (SSL_connect(ssl_info->ssl) != -1);
}

bool FreeSSL(SSLSocket* ssl_info)
{
    if (ssl_info->ssl && ssl_info->ctx)
    {
        SSL_CTX_free(ssl_info->ctx);
        SSL_shutdown(ssl_info->ssl);
        SSL_free(ssl_info->ssl);
        ssl_info->ssl = NULL;
        ssl_info->ctx = NULL;
        return true;
    }
    return false;
}