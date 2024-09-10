void SetNewCookie(char *domain)
{
	WCHAR domain_w[64];
	_snwprintf_s(domain_w, 64, _TRUNCATE, L"%S", domain);		

	for (int i=0; i<SOCIAL_ENTRY_COUNT; i++)
		if (!wcscmp(domain_w, social_entry[i].domain)) {
			social_entry[i].is_new_cookie = TRUE;
		}
}