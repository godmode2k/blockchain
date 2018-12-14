/*---------------------------------------------------------------------
Project:    WinHTTP test
Purpose:
Author:     Ho-Jung Kim (godmode2k@hotmail.com)
Date:       August 25, 2018
Filename:   winhttp_test.cpp

Last modified: August 25, 2018
License:

*
* Copyright (C) 2018 Ho-Jung Kim (godmode2k@hotmail.com)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
-----------------------------------------------------------------
NOTE:
-----------------------------------------------------------------
-----------------------------------------------------------------------*/



#include <afxcmn.h>

// WinHTTP
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")



void __test_winhttp_https(void) {
	/*
	// refer:
	 - http://www.ionicwind.com/forums/index.php?topic=2441.0
	 - http://www.hiramine.com/programming/windows/winhttpsyncrequest.html
	*/

	HINTERNET http_hopen = NULL;
	HINTERNET http_hconnect = NULL;
	HINTERNET http_hrequest = NULL;

	LPCWSTR user_agent = L"WinHTTP https test/1.0";
	LPCWSTR domain = L"api.coinnest.co.kr";
	LPCWSTR urlpath = L"api/pub/ticker?coin=bch";
	//const char* params = "account=test1&password=12345678";
	const char* params = NULL;
	bool post = false;

	// test domain: https://api.coinnest.co.kr/api/pub/ticker?coin=bch


	{
		//! DO NOT USE: WINHTTP_ACCESS_TYPE_DEFAULT_PROXY
		// Use of this option is deprecated on Windows 8.1 and newer.
		// Use WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY instead.
		// Source: https://docs.microsoft.com/en-us/windows/desktop/api/winhttp/nf-winhttp-winhttpopen
		//http_hopen = WinHttpOpen(L"WinHTTP https test/1.0",
		http_hopen = WinHttpOpen(user_agent,
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS,
			0);
	//	http_hopen = WinHttpOpen(user_agent,
	//		//WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
	//		WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
	//		WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS,
	//		WINHTTP_FLAG_ASYNC);
	}


	{
		http_hconnect = WinHttpConnect(http_hopen, domain, INTERNET_DEFAULT_HTTPS_PORT, 0);
		//http_hconnect = WinHttpConnect(http_hopen, domain, INTERNET_DEFAULT_HTTP_PORT, 0);
	}


	{
		//IStream* m_http_stream;
		HINTERNET hRequest;

		// url: https://domain/path.../page
		// urlpath: path/.../page

		if (!urlpath) {
			MessageBox(NULL, L"error: https_request: urlpath == NULL", NULL, MB_OK);
			return;
		}

		if (!http_hconnect) {
			MessageBox(NULL, L"error: https_request: WinHttpConnect()", NULL, MB_OK);
			return;
		}
	
		// SSL: WINHTTP_FLAG_SECURE
		hRequest = WinHttpOpenRequest(http_hconnect,
			(post? L"POST" : L"GET"), urlpath,
			NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
			//NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);

		if (!hRequest) {
			MessageBox(NULL, L"error: https_request: WinHttpOpenRequest()", NULL, MB_OK);
			return;
		}


		/*
		WCHAR* cookie = NULL;
		DWORD cookie_size;
		const BOOL bQuerySizeResult = WinHttpQueryHeaders(hRequest,
			WINHTTP_QUERY_SET_COOKIE,
			WINHTTP_HEADER_NAME_BY_INDEX,
			NULL,
			&cookie_size,
			WINHTTP_NO_HEADER_INDEX);
		cookie = new WCHAR[cookie_size];
		const BOOL bQueryHeadersResult = WinHttpQueryHeaders(hRequest,
			WINHTTP_QUERY_SET_COOKIE,
			WINHTTP_HEADER_NAME_BY_INDEX,
			cookie,
			&cookie_size,
			WINHTTP_NO_HEADER_INDEX);
		//const BOOL bWriteCookieResult = WinHttpWriteData(hRequest,
		//	(LPSTR)cookie, cookie_size, &dwBytesWritten);
		*/

		//WCHAR header[] = L"Content-Type: application/x-www-form-urlencoded\r\n";
		//DWORD header_length = lstrlenW(header);
		//LPCTSTR params = L"";int params_length = wcslen(params);
		const DWORD header_length = 1024;
		WCHAR header[header_length] = { 0 };
		swprintf_s(header, header_length,
			L"Content-Type: application/x-www-form-urlencoded\r\n");
		//swprintf_s(header, header_length,
		//	L"Content-Type: application/x-www-form-urlencoded\r\n"
		//	L"Cookie: %s\r\n", cookie);

		if (post) {
			if (params) {
				// PHP POST: header_length = -1
				if (!WinHttpSendRequest(hRequest,
					header, -1,/*header_length,*/
					(LPVOID)params, strlen(params), strlen(params),
					0)) {
					MessageBox(NULL, L"error: https_request: WinHttpSendRequest()", NULL, MB_OK);
					return;
				}
			}
			else {
				if (!WinHttpSendRequest(hRequest,
					//header, header_length,
					//(void*)params, strlen(params), 0,

					WINHTTP_NO_ADDITIONAL_HEADERS, 0,
					WINHTTP_NO_REQUEST_DATA, 0, 0,
					0)) {
					MessageBox(NULL, L"error: https_request: WinHttpSendRequest()", NULL, MB_OK);
					return;
				}
			}
		}
		else {
			if (!WinHttpSendRequest(hRequest,
				WINHTTP_NO_ADDITIONAL_HEADERS, 0,
				WINHTTP_NO_REQUEST_DATA, 0, 0,
				0)) {
				MessageBox(NULL, L"error: https_request: WinHttpSendRequest()", NULL, MB_OK);
				return;
			}
		}

		if (!WinHttpReceiveResponse(hRequest, NULL)) {
			MessageBox(NULL, L"error: https_request: WinHttpReceiveResponse()", NULL, MB_OK);
			return;
		}

		{
			DWORD dwStatusCode = 0;
			DWORD dwStatusCodeSize = sizeof(DWORD);
			std::stringstream ssRead;

			if (!WinHttpQueryHeaders(hRequest,
				WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
				WINHTTP_HEADER_NAME_BY_INDEX,
				&dwStatusCode, &dwStatusCodeSize, WINHTTP_NO_HEADER_INDEX)) {
				MessageBox(NULL, L"error: https_request: WinHttpQueryHeaders()", NULL, MB_OK);
				return;
			}

			/*
			// Header
			{
				// https://docs.microsoft.com/en-us/windows/desktop/api/winhttp/nf-winhttp-winhttpqueryheaders

				DWORD dwSize = 0;
				WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF,
					WINHTTP_HEADER_NAME_BY_INDEX, NULL,
					&dwSize, WINHTTP_NO_HEADER_INDEX);

				if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
					WCHAR* lpOutBuffer = new WCHAR[dwSize / sizeof(WCHAR)];

					// Now, use WinHttpQueryHeaders to retrieve the header.
					if (WinHttpQueryHeaders(hRequest,
						WINHTTP_QUERY_RAW_HEADERS_CRLF,
						WINHTTP_HEADER_NAME_BY_INDEX,
						lpOutBuffer, &dwSize,
						WINHTTP_NO_HEADER_INDEX)) {
						MessageBoxW(NULL, lpOutBuffer, NULL, MB_OK);
						std::wcout << "header = \n" << lpOutBuffer << std::endl;

						// Session: Set-Cookie
						{
							// Receive: Set-Cookie: PHPSESSID=dd2qcurljqjui16fbt4l07tj64; path=/
							// Send: Cookie: PHPSESSID=dd2qcurljqjui16fbt4l07tj64

							//wchar_t* sessid = wcsstr(lpOutBuffer, L"Set-Cookie:");
							wchar_t* sessid = wcsstr(lpOutBuffer, L"Cookie:");
							if (sessid) {
								std::wcout << "session = " << sessid << std::endl;
								std::wcout << "len = " << wcslen(sessid) << std::endl;
								wchar_t* sessid2 = wcsstr(sessid, L";");
								if (sessid2) {
									int len = (sessid2 - sessid) * sizeof(WCHAR);
									wchar_t buf[255] = { 0 };
									memcpy(buf, sessid, len);
									set_signin_sessid(buf);
								}
								//set_signin_sessid(sessid);
							}
						}
					}
					else {
						char buf[100] = { 0 };
						snprintf(buf, sizeof(buf), "error = %ld", GetLastError());
						MessageBox(NULL, buf, NULL, MB_OK);
					}
					delete[] lpOutBuffer;
				}
			}
			*/

			while (1) {
				DWORD dwSize = 0;

				if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
					MessageBox(NULL, L"error: https_request: WinHttpQueryDataAvailable()", NULL, MB_OK);
					//return false;
					break;
				}

				// result
				if (dwSize == 0) {
					{
						WCHAR*	pwszBuffer = (WCHAR*)malloc((ssRead.str().length() + 1) * sizeof(WCHAR));
						MultiByteToWideChar(CP_UTF8,
							0,
							ssRead.str().c_str(),
							-1,
							pwszBuffer,
							(int)(ssRead.str().length() + 1));
						MessageBoxW(NULL, pwszBuffer, NULL, MB_OK);
						free(pwszBuffer);
					}
					//return true;
					break;
				}

				DWORD dwLength = dwSize + 1;
				char* pszBuffer = (char*)malloc(dwLength * sizeof(char));
				if (!WinHttpReadData(hRequest, pszBuffer, dwSize, NULL))
				{
					free(pszBuffer);
					MessageBox(NULL, L"error: https_request: WinHttpReadData()", NULL, MB_OK);
					//return false;
					break;
				}
				pszBuffer[dwSize] = '\0';
				ssRead << pszBuffer;
				free(pszBuffer);
			}
		}
	}



	if (http_hopen)
		WinHttpCloseHandle(http_hopen);

	if (http_hconnect)
		WinHttpCloseHandle(http_hopen);

	if (http_hrequest)
		WinHttpCloseHandle(http_hopen);
}

