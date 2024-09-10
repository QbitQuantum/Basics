HRESULT send_email(UINT8 *jpeg_data, DWORD sz)
{
	CURL *curl = curl_easy_init();
	if (!curl) {
		aslog::error(L"curl_easy_init failed");
		return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0xFF00);
	}
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	CComPtr<IStream> stream = SHCreateMemStream(NULL, 0);
	build_msg(stream, jpeg_data, sz);

	curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
	curl_easy_setopt(curl, CURLOPT_READDATA, stream.p);
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

	curl_easy_setopt(curl, CURLOPT_URL, g_smtpURL);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

	curl_easy_setopt(curl, CURLOPT_USERNAME, g_smtpUser);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, g_smtpPass);
	curl_easy_setopt(curl, CURLOPT_MAIL_FROM, g_smtpFrom);

	struct curl_slist *recipients = NULL;
	recipients = curl_slist_append(recipients, g_smtpTo);
	curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

	char errbufA[CURL_ERROR_SIZE];
	errbufA[0] = 0;
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbufA);

	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		wchar_t errbufW[CURL_ERROR_SIZE];
		MultiByteToWideChar(CP_UTF8, 0, errbufA, CURL_ERROR_SIZE, errbufW, CURL_ERROR_SIZE);
		aslog::error(L"Mail sending failed: %s", errbufW);
	}
	curl_slist_free_all(recipients);
	curl_easy_cleanup(curl);
	return S_OK;
}