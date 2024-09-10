/*!
 * @brief Wrapper around WinINET-specific request response validation.
 * @param hReq HTTP request handle.
 * @param ctx The HTTP transport context.
 * @return An indication of the result of getting a response.
 */
static DWORD validate_response_wininet(HANDLE hReq, HttpTransportContext* ctx)
{
	DWORD statusCode;
	DWORD statusCodeSize = sizeof(statusCode);
	vdprintf("[PACKET RECEIVE WININET] Getting the result code...");
	if (HttpQueryInfoW(hReq, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &statusCodeSize, 0))
	{
		vdprintf("[PACKET RECEIVE WININET] Returned status code is %d", statusCode);

		// did the request succeed?
		if (statusCode != 200)
		{
			// bomb out
			return ERROR_BAD_CONFIGURATION;
		}
	}

	return ERROR_SUCCESS;
}