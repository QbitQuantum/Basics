static void _get_host(SG_context* pCtx, const char* szRepoSpec, SG_string** ppstrHost)
{
	LPWSTR pwszRepoSpec = NULL;
	SG_uint32 len = 0;
	URL_COMPONENTSW UrlComponents;
	SG_string* pstrHost = NULL;
	WCHAR buf[260];

	SG_zero(UrlComponents);
	UrlComponents.dwStructSize = sizeof(URL_COMPONENTS);
	UrlComponents.dwHostNameLength = sizeof(buf);
	UrlComponents.lpszHostName = buf;

	SG_ERR_CHECK(  SG_utf8__extern_to_os_buffer__wchar(pCtx, szRepoSpec, &pwszRepoSpec, &len)  );

	if ( !InternetCrackUrlW(pwszRepoSpec, len, ICU_DECODE, &UrlComponents) )
		SG_ERR_THROW2(  SG_ERR_GETLASTERROR(GetLastError()), (pCtx, "unable to parse host from URL")  );

	SG_ERR_CHECK(  SG_STRING__ALLOC(pCtx, &pstrHost)  );
	SG_ERR_CHECK(  SG_utf8__intern_from_os_buffer__wchar(pCtx, pstrHost, UrlComponents.lpszHostName)  );

	SG_RETURN_AND_NULL(pstrHost, ppstrHost);

	/* fall through */
fail:
	SG_NULLFREE(pCtx, pwszRepoSpec);
	SG_STRING_NULLFREE(pCtx, pstrHost);
}