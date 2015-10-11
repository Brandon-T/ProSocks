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

#include "Exports.h"

#if defined _WIN32 || defined _WIN64
#ifdef __cplusplus
extern "C"
{
#endif
bool __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, void* lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            module = hinstDLL;
            DisableThreadLibraryCalls(hinstDLL);

            #ifndef USE_CURL
            SSL_library_init();
            SSL_load_error_strings();
            OpenSSL_add_all_algorithms();
            #else
            curl_global_init(CURL_GLOBAL_ALL);
            #endif
            break;

        case DLL_PROCESS_DETACH:
            #ifndef USE_CURL
            ERR_free_strings();
            EVP_cleanup();
            CRYPTO_cleanup_all_ex_data();
            #else
            curl_global_cleanup();
            #endif
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
#endif
#else
void __attribute__((constructor)) load()
{
    #ifndef CURL_SSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    #else
    curl_global_init(CURL_GLOBAL_ALL);
    #endif
}

void __attribute__((destructor)) unload()
{
    #ifndef CURL_SSL
    ERR_free_strings();
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    #else
    curl_global_cleanup();
    #endif
}
#endif
