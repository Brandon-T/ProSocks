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

#include "CurlSSL.h"

char* base64encode(const uint8_t *in, uint32_t in_len)
{
    unsigned int c[4] = {0};
    unsigned int i = 0, j = 0;
    static unsigned char indexes[] = {0, 2, 1};
    static const char *Base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    unsigned int out_len = 4 * ((in_len + 2) / 3);
    char* out = (char*)malloc(out_len + 1);
    if (!out) return NULL;

    while(i < in_len)
    {
        c[0] = in[i++]; c[1] = in[i++]; c[2] = in[i++];
        c[3] = (c[0] << 0x10) + (c[1] << 0x08) + c[2];
        out[j++] = Base64Chars[(c[3] >> 3 * 6) & 0x3F];
        out[j++] = Base64Chars[(c[3] >> 2 * 6) & 0x3F];
        out[j++] = Base64Chars[(c[3] >> 1 * 6) & 0x3F];
        out[j++] = Base64Chars[(c[3] >> 0 * 6) & 0x3F];
    }

    for (i = 0; i < indexes[in_len % 3]; ++i)
        out[out_len - 1 - i] = '=';
    out[out_len] = '\0';
    return out;
}

uint32_t CRC32(void* Data, size_t Size, uint32_t InitialValue)
{
    static const uint32_t LookUpTable[256] =
    {
        0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
        0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
        0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
        0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
        0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
        0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
        0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
        0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
        0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
        0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
        0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
        0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
        0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
        0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
        0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
        0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
        0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
        0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
        0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
        0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
        0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
        0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
        0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
        0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
        0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
        0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
        0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
        0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
        0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
        0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
        0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
        0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
        0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
        0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
        0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
        0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
        0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
        0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
        0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
        0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
        0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
        0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
        0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
        0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
        0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
        0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
        0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
        0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
        0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
        0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
        0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
        0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
        0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
        0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
        0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
        0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
        0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
        0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
        0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
        0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
        0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
        0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
        0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
        0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
    };

    uint32_t CRC = ~InitialValue;
    uint8_t* Pointer = (uint8_t*)Data;

    size_t I = 0;
    for(; I < Size; ++I)
    {
        CRC = LookUpTable[(CRC ^ *Pointer++) & 0xFF] ^ (CRC >> 8);
    }

    return ~CRC;
}

void Curl_InitMemoryStruct(CurlMemoryStruct** ptr)
{
    if (ptr && *ptr)
        return;

    *ptr = malloc(sizeof(**ptr));
    if (ptr && *ptr)
    {
        (*ptr)->memory = NULL;
        (*ptr)->size = 0;
    }
}

void Curl_FreeInternalMemoryStruct(CurlMemoryStruct* ptr)
{
    if (ptr)
    {
        free(ptr->memory);
        ptr->memory = NULL;
        ptr->size = 0;
    }
}

void Curl_FreeMemoryStruct(CurlMemoryStruct** ptr)
{
    if (ptr && *ptr)
    {
        Curl_FreeInternalMemoryStruct(*ptr);
        free(*ptr);
        *ptr = NULL;
    }
}

size_t Internal_ReadFunction(void *contents, size_t size, size_t nmemb, void *userp)
{
    const char *pdata = NULL;
    CurlMemoryStruct *mem = (CurlMemoryStruct *)userp;

	if((size == 0) || (nmemb == 0) || ((size * nmemb) < 1))
	{
		return 0;
	}

	pdata = ((char **)mem->memory)[mem->size];

	if (pdata)
	{
		size_t len = strlen(pdata);
		memcpy(contents, pdata, len);
		mem->size++;
		return len;
	}
	return 0;
}

size_t Internal_WriteFunction(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    CurlMemoryStruct *mem = (CurlMemoryStruct *)userp;
    mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);

    if (mem->memory == NULL) return 0;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

void Curl_InitSocket(CurlSock* curl_info,
                  size_t (*func_write_buffer)(void *contents, size_t size, size_t nmemb, void *userp),
                  size_t (*func_write_header)(void *contents, size_t size, size_t nmemb, void *userp),
                  size_t (*func_error_handler)(const void* str, long errorcode),
                  size_t (*func_str_len)(void *str)
                  )
{
    if (curl_info)
    {
        curl_info->func_write_buffer = func_write_buffer;
        curl_info->func_write_header = func_write_header;
        curl_info->func_error_handler = func_error_handler;
        curl_info->func_str_len = func_str_len;
    }
}

void Curl_CreateSocket(CurlSock* curl_info, const char* useragent)
{
    if (!useragent || (strlen(useragent) < 1))
    {
        useragent = "Mozilla/5.0 (Windows NT 6.2; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1667.0 Safari/537.36";
    }

    curl_info->curl_handle = curl_easy_init();

    if (curl_info->curl_handle)
    {
        if (!curl_info->caller_allocates || !curl_info->func_write_buffer)
        {
            curl_info->func_write_buffer = Internal_WriteFunction;
            curl_info->caller_allocates = false;
        }
        Curl_InitMemoryStruct((CurlMemoryStruct **)&curl_info->data);
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_TIMEOUT_MS, curl_info->timeout);
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_PORT, curl_info->port);
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_FAILONERROR, true);
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_USERAGENT, useragent);
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_WRITEFUNCTION, curl_info->func_write_buffer);
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_WRITEDATA, curl_info->data);
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_AUTOREFERER, 1L);
    }
}

void Curl_FreeSocket(CurlSock* curl_info)
{
    if (!curl_info->caller_allocates)
    {
        Curl_FreeMemoryStruct((CurlMemoryStruct **)curl_info->headers);
        Curl_FreeMemoryStruct((CurlMemoryStruct **)curl_info->params);
        Curl_FreeMemoryStruct((CurlMemoryStruct **)curl_info->data);
    }

    curl_slist_free_all(curl_info->hdrs);
    curl_easy_cleanup(curl_info->curl_handle);
    curl_info->curl_handle = NULL;
    memset(curl_info, 0, sizeof(*curl_info));
}

void Curl_SetURLFollow(CurlSock* curl_info, bool follow)
{
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_FOLLOWLOCATION, follow);
}

void Curl_SetSSL(CurlSock* curl_info, bool tryset, bool VerifyPeer, bool VerifyHost)
{
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_USE_SSL, tryset ? CURLUSESSL_TRY : CURLUSESSL_ALL);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_SSL_VERIFYPEER, VerifyPeer ? 2L : 0L);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_SSL_VERIFYHOST, VerifyHost ? 2L : 0L);
}

void Curl_SetCookies(CurlSock* curl_info, const char *CookieJar, const char *CookieFile)
{
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_COOKIEJAR, CookieJar);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_COOKIEFILE, CookieFile);
}

void Curl_SetHeaderCapture(CurlSock* curl_info, bool Enable)
{
    if (!curl_info->caller_allocates)
    {
        Curl_FreeMemoryStruct((CurlMemoryStruct **)&curl_info->headers);
        Curl_InitMemoryStruct((CurlMemoryStruct **)&curl_info->headers);
    }
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_HEADERFUNCTION, Enable ? curl_info->func_write_header : NULL);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_HEADERDATA, Enable ? curl_info->headers : NULL);
}

bool Curl_SetHeader(CurlSock* curl_info, const char* Key, const char* Value)
{
    if (Key == NULL && Value == NULL)
    {
        curl_slist_free_all(curl_info->hdrs);
        curl_info->hdrs = NULL;
        return false;
    }

    char buffer[512];
    sprintf(buffer, "%s: %s", Key, Value);
    struct curl_slist *tmp = curl_slist_append(curl_info->hdrs, buffer);
    if (tmp)
    {
        curl_info->hdrs = tmp;
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_HTTPHEADER, curl_info->hdrs);
        return true;
    }
    curl_slist_free_all(curl_info->hdrs);
    return false;
}

void Curl_CustomRequest(CurlSock* curl_info, const char* request)
{
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_CUSTOMREQUEST, request);
}

void Curl_SetNoBody(CurlSock* curl_info, bool Enabled)
{
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_NOBODY, Enabled);
}

void Curl_SetVerbose(CurlSock* curl_info, bool Enabled)
{
     curl_easy_setopt(curl_info->curl_handle, CURLOPT_VERBOSE, Enabled);
}

const char* Curl_GetHostLocation(const char* address, char* buffer)
{
    const char* addr = strstr(address, "://");
    if (addr)
        strcpy(buffer, addr + 3);

    if ((addr = strstr(buffer, "/")))
        buffer[addr - buffer] = '\0';

    return addr ? buffer : NULL;
}

const char* Curl_GetRequestLocation(const char* address, char* buffer)
{
    const char* addr = strstr(address, "://");
    if (buffer)
    {
        if (addr)
            strcpy(buffer, addr + 3);

        if ((addr = strstr(buffer, "/")))
        {
            strcpy(buffer, addr + 1);
        }
    }
    else
    {
        addr = strstr(addr + 3, "/");
        return addr ? addr + 1 : NULL;
    }

    return addr ? buffer : NULL;
}

void Curl_SetURL(CurlSock* curl_info, const char *URL)
{
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_URL, URL);
}

void Curl_SetUpload(CurlSock* curl_info, bool Enabled)
{
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_READDATA, curl_info->params);
    if (Enabled)
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_READFUNCTION, Internal_ReadFunction);
    else
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_READFUNCTION, fread);

    curl_easy_setopt(curl_info->curl_handle, CURLOPT_UPLOAD, Enabled);

    if (Enabled)
        curl_easy_setopt(curl_info->curl_handle, CURLOPT_POST, 0L);
}

void Curl_SetLogin(CurlSock* curl_info, const char* username, const char* password)
{
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_USERNAME, username);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_PASSWORD, password);
}

void Curl_ClearParams(CurlSock* curl_info)
{
    if (!curl_info->caller_allocates && curl_info->params)
    {
        Curl_FreeMemoryStruct((CurlMemoryStruct **)&curl_info->params);
    }
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_POSTFIELDS, NULL);
}

bool Curl_AddParameter(CurlSock* curl_info, const char *Key, const char *Value, bool Escape)
{
    const char* val = NULL;
    CurlMemoryStruct* params = NULL;

    if (Key && Value && strlen(Key) && strlen(Value))
    {
        val = Escape ? curl_easy_escape(curl_info->curl_handle, Value, 0) : Value;

        if (curl_info->caller_allocates)
        {
            if (curl_info->func_str_len(curl_info->params))
            {
                curl_info->func_write_buffer((void *)"&", 1, 1, curl_info->params);
            }
        }
        else
        {
            Curl_InitMemoryStruct((CurlMemoryStruct **)&curl_info->params);
            params = (CurlMemoryStruct *)curl_info->params;
            if (params->size)
            {
                curl_info->func_write_buffer((void *)"&", 1, 1, params);
            }
        }

        curl_info->func_write_buffer((void *)Key, 1, strlen(Key), curl_info->params);
        curl_info->func_write_buffer((void *)"=", 1, 1, curl_info->params);
        curl_info->func_write_buffer((void *)val, 1, strlen(val), curl_info->params);
        return true;
    }
    return false;
}

CurlMemoryStruct* Curl_DoGet(CurlSock* curl_info)
{
    if (curl_info->caller_allocates)
    {
        curl_info->func_write_buffer(NULL, 0, 0, curl_info->headers);
        curl_info->func_write_buffer(NULL, 0, 0, curl_info->data);
    }
    else
    {
        Curl_FreeInternalMemoryStruct((CurlMemoryStruct *)curl_info->headers);
        Curl_FreeInternalMemoryStruct((CurlMemoryStruct *)curl_info->data);
    }

    curl_easy_setopt(curl_info->curl_handle, CURLOPT_UPLOAD, 0L);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_POST, 0L);
    return Curl_Perform(curl_info);
}

CurlMemoryStruct* Curl_DoPost(CurlSock* curl_info)
{
    if (curl_info->caller_allocates)
    {
        curl_info->func_write_buffer(NULL, 0, 0, curl_info->headers);
        curl_info->func_write_buffer(NULL, 0, 0, curl_info->data);
    }
    else
    {
        Curl_FreeInternalMemoryStruct((CurlMemoryStruct *)curl_info->headers);
        Curl_FreeInternalMemoryStruct((CurlMemoryStruct *)curl_info->data);
    }

    curl_easy_setopt(curl_info->curl_handle, CURLOPT_UPLOAD, 0L);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_POST, 1L);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_POSTFIELDS, curl_info->caller_allocates ? curl_info->params : ((CurlMemoryStruct *)curl_info->params)->memory);
    CurlMemoryStruct* res = Curl_Perform(curl_info);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_POST, 0L);
    return res;
}

CurlMemoryStruct* Curl_Perform(CurlSock* curl_info)
{
    CURLcode res = curl_easy_perform(curl_info->curl_handle);
    if (res != CURLE_OK)
    {
        if (curl_info->caller_allocates)
        {
            curl_info->func_write_buffer(NULL, 0, 0, curl_info->headers);
            curl_info->func_write_buffer(NULL, 0, 0, curl_info->data);
        }
        else
        {
            Curl_FreeInternalMemoryStruct((CurlMemoryStruct *)curl_info->headers);
            Curl_FreeInternalMemoryStruct((CurlMemoryStruct *)curl_info->data);
        }

        if (curl_info->func_error_handler)
        {
            curl_info->func_error_handler(curl_easy_strerror(res), res);
        }
    }
    return (CurlMemoryStruct *)curl_info->data;
}

CurlMemoryStruct* Curl_GetHeaders(CurlSock* curl_info)
{
    return (CurlMemoryStruct *)curl_info->headers;
}

void Curl_SMTP_AddRecipient(struct curl_slist **recipients, int* count, char **data, const char *type, const char *who)
{
    if (who == NULL || type == NULL || (strlen(who) < 1) || (strlen(type) < 1))
        return;

    int tmp = *count;
    char *pch = strtok((char *)who, "\r\n");
    while (pch != NULL)
    {
        data[tmp] = (char*)malloc(strlen(pch) + strlen(type) + 3);
        sprintf(data[tmp], pch);
        *recipients = curl_slist_append(*recipients, data[tmp]);
        strcpy(data[tmp] + sprintf(data[tmp], "%s: <%s>", type, pch), "\r\n");
        pch = strtok(NULL, "\r\n");
        ++tmp;
    }
    *count = tmp;
}

bool Curl_SMTP_AddAttachment(int* count, char **data, const char* file, const char* mime)
{
    char* fb = NULL;
    size_t fs = 0;
    FILE* fp = fopen(file, "rb");

    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        fs = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        fb = (char*)malloc(fs);
        int read = fread(fb, sizeof(char), fs, fp);
        if (read != fs)
        {
            fclose(fp);
            return false;
        }
        fclose(fp);
    }

    char* buff = base64encode((const uint8_t*)fb, fs);
    free(fb);

    int tmp = *count;
    const char* content_type = "Content-Type: %s; name=\"%s\"\r\n";
    const char* encoding_type = "Content-Transfer-Encoding: base64\r\n";
    const char* disposition = "Content-Disposition: attachment; filename=\"%s\"\r\n";

    data[tmp] = (char*)malloc(strlen(content_type) + strlen(file) + strlen(mime) + 1);
    sprintf(data[tmp++], content_type, mime, file);

    data[tmp] = (char*)malloc(strlen(encoding_type) + 1);
    sprintf(data[tmp++], encoding_type);

    data[tmp] = (char*)malloc(strlen(disposition) + strlen(file) + 1);
    sprintf(data[tmp++], disposition, file);
    data[tmp++] = buff;
    *count = tmp;
    return true;
}

bool Curl_SMTP(CurlSock* curl_info, const char* url, const char* user, const char* pwd, const char* name, const char* to, const char* cc, const char* bcc, const char* subject, const char* body, const char* bodymime, const char* file, const char* filemime)
{
    int i = 1, count = 1;
    struct curl_slist *recipients = NULL;
    void* oldparams = curl_info->params;
    CurlMemoryStruct* data_struct = NULL;
    const char* mime_info = "MIME-Version: 1.0\r\n";
    const char* default_info = "text/plain; charset=\"iso-8859-1\"";
    const char* content_info = "Content-Type: multipart/mixed; boundary=\"----%s----\"\r\n";
    const char* message_info = "Content-Type: %s\r\nContent-Transfer-Encoding: 8bit\r\n\r\n";

    if (name && strlen(name) < 1) name = NULL;
    if (cc && strlen(cc) < 1) cc = NULL;
    if (bcc && strlen(bcc) < 1) bcc = NULL;
    if (subject && strlen(subject) < 1) subject = "";
    if (!body) body = "";
    if (bodymime && strlen(bodymime) < 1) bodymime = NULL;
    if (file && strlen(file) < 1) file = NULL;
    if (filemime && strlen(filemime) < 1) filemime = NULL;

    curl_info->params = NULL;
    Curl_InitMemoryStruct((CurlMemoryStruct **)&curl_info->params);
    data_struct = (CurlMemoryStruct *)curl_info->params;

    Curl_SetLogin(curl_info, user, pwd);
    Curl_SetURL(curl_info, url);
    Curl_SetUpload(curl_info, true);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_MAIL_FROM, user);

    char* data[10000] = {0};
    data_struct->memory = (char*)data;

    char from_buffer[512] = {0};
    if (name == NULL)
        sprintf(from_buffer, "FROM: <%s>\r\n", user);
    else
        sprintf(from_buffer, "FROM: <%s>(%s)\r\n", user, name);
    data[0] = from_buffer;

    Curl_SMTP_AddRecipient(&recipients, &count, data, "TO", to);
    Curl_SMTP_AddRecipient(&recipients, &count, data, "CC", cc);
    Curl_SMTP_AddRecipient(&recipients, &count, data, "BCC", bcc);
    curl_easy_setopt(curl_info->curl_handle, CURLOPT_MAIL_RCPT, recipients);

    data[count] = (char*)malloc(strlen(subject) + 12);
    sprintf(data[count++], "Subject: %s\r\n", subject);

    //Calculate boundary hash.
    char hash_boundary[32];
    time_t now = time(NULL);
    sprintf(hash_boundary, "%d", CRC32(&now, sizeof(now), 0xFFFFFFFF));

    //Setup mime version and type.
    data[count] = (char*)malloc(strlen(mime_info) + 1);
    sprintf(data[count++], mime_info);
    data[count] = (char*)malloc(strlen(content_info) + strlen(hash_boundary) + 1);
    sprintf(data[count++], content_info, hash_boundary);

    //Start of body.
    data[count] = (char*)malloc(strlen(hash_boundary) + 13);
    sprintf(data[count++], "------%s----\r\n", hash_boundary);
    data[count] = (char*)malloc(strlen(message_info) + strlen(bodymime ? bodymime : default_info)  + 1);
    sprintf(data[count++], message_info, bodymime ? bodymime : default_info);

    data[count] = (char*)malloc(strlen(body) + 7);
    sprintf(data[count++], "%s\r\n", body);

    data[count] = (char*)malloc(strlen(hash_boundary) + 13);
    if (file != NULL && filemime != NULL)
    {
        sprintf(data[count++], "------%s----\r\n", hash_boundary);
        //End of body.
        //Start of attachment.
        Curl_SMTP_AddAttachment(&count, data, file, filemime);
        //End of attachment.
    }

    //Termination boundary.
    data[count] = (char*)malloc(strlen(hash_boundary) + 17);
    sprintf(data[count++], "\r\n------%s------\r\n", hash_boundary);

    data[count] = (char*)malloc(5);
    sprintf(data[count++], "\r\n.\r\n");
    data[count++] = NULL;

    CURLcode res = curl_easy_perform(curl_info->curl_handle);
    curl_slist_free_all(recipients);

    for (; i < count; ++i) free(data[i]);
    Curl_FreeMemoryStruct((CurlMemoryStruct **)&curl_info->params);
    curl_info->params = oldparams;

    if (curl_info->caller_allocates)
        curl_info->func_write_buffer(NULL, 0, 0, curl_info->data);
    else
        Curl_FreeInternalMemoryStruct((CurlMemoryStruct *)curl_info->data);

    if (res != CURLE_OK && curl_info->func_error_handler)
    {
        curl_info->func_error_handler(curl_easy_strerror(res), res);
    }

    return res == CURLE_OK;
}
