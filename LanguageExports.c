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

#include "LanguageExports.h"

#ifdef __cplusplus
extern "C"
{
#endif
DLL_FUNC void Curl_DoGetEx(CurlSock* curl_info, CurlMemoryStruct* res)
{
    CurlMemoryStruct* data = Curl_DoGet(curl_info);
    memcpy(res, data, sizeof(*data));
}

DLL_FUNC void Curl_DoPostEx(CurlSock* curl_info, CurlMemoryStruct* res)
{
    CurlMemoryStruct* data = Curl_DoPost(curl_info);
    memcpy(res, data, sizeof(*data));
}

DLL_FUNC void Curl_PerformEx(CurlSock* curl_info, CurlMemoryStruct* res)
{
    CurlMemoryStruct* data = Curl_Perform(curl_info);
    memcpy(res, data, sizeof(*data));
}

DLL_FUNC void Curl_GetHeadersEx(CurlSock* curl_info, CurlMemoryStruct* res)
{
    CurlMemoryStruct* data = Curl_GetHeaders(curl_info);
    memcpy(res, data, sizeof(*data));
}

DLL_FUNC void Curl_MSTPC(CurlSock* curl_info, CurlMemoryStruct* res)
{
    CurlMemoryStruct* data = (CurlMemoryStruct *)curl_info->data;
    memcpy(res, data, sizeof(*data));
}
#ifdef __cplusplus
}
#endif

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
        #if defined(_WIN32) || defined(_WIN64)
        *Address = (void*)GetProcAddress(module, PascalExports[Index * 2]);
        #else
        *Address = (void*)dlsym(RTLD_DEFAULT, PascalExports[Index * 2]);
        #endif
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
