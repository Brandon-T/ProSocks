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
#ifdef __cplusplus
extern "C"
{
#endif //defined
bool __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, void* lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            module = hinstDLL;
            DisableThreadLibraryCalls(hinstDLL);

            SSL_library_init();
            SSL_load_error_strings();
            OpenSSL_add_all_algorithms();
            break;

        case DLL_PROCESS_DETACH:
            ERR_free_strings();
            EVP_cleanup();
            CRYPTO_cleanup_all_ex_data();
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;
    }

    return true;
}
#ifdef __cplusplus
}
#endif //defined
#else
void load() __attribute__((constructor))
{
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
}

void unload() __attribute__((destructor))
{
    ERR_free_strings();
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
}
#endif
