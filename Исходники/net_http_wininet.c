static int wininetReceive(KSI_RequestHandle *handle) {
	int res;
	KSI_CTX *ctx = NULL;
	wininetNetHandleCtx *wininetHandle = NULL;
	unsigned char *resp = NULL;
	unsigned resp_len = 0;

	if (handle == NULL) {
		res = KSI_INVALID_ARGUMENT;
		goto cleanup;
	}
	ctx = KSI_RequestHandle_getCtx(handle);
	KSI_ERR_clearErrors(ctx);


	wininetHandle = handle->implCtx;

	if (!HttpSendRequestA(wininetHandle->request_handle, NULL, 0, (LPVOID) handle->request, handle->request_length)) {
		WININET_ERROR_1(ctx, ERROR_INTERNET_CANNOT_CONNECT, KSI_NETWORK_ERROR, "WinINet: Unable to resolve host.")
		WININET_ERROR_m(ctx, ERROR_INTERNET_NAME_NOT_RESOLVED, KSI_NETWORK_ERROR, "WinINet: HTTP status code header not found.")
		WININET_ERROR_m(ctx, ERROR_INTERNET_TIMEOUT, KSI_NETWORK_SEND_TIMEOUT, NULL)
		WININET_ERROR_N(ctx, KSI_UNKNOWN_ERROR, "WinINet: Unable to send request.")
	}

	res = winINet_ReadFromHandle(handle, &resp, &resp_len);
	if (res != KSI_OK) {
		KSI_pushError(ctx, res, NULL);
		goto cleanup;
	}

	res = KSI_RequestHandle_setResponse(handle, resp, resp_len);
	if (res != KSI_OK) {
		KSI_pushError(ctx, res, NULL);
		goto cleanup;
	}

	res = KSI_OK;

cleanup:

    KSI_free(resp);

	return res;
}