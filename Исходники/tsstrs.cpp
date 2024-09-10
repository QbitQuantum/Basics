bool   str_wrap_text_iequalsa(const char *s1, const char *s2, aint len)
{
	return CSTR_EQUAL == CompareStringA(LOCALE_USER_DEFAULT,NORM_IGNORECASE,s1,len,s2,len);
}