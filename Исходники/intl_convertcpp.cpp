/* {{{ intl_stringFromChar */
int intl_stringFromChar(UnicodeString &ret, char *str, size_t str_len, UErrorCode *status)
{
	if(str_len > INT32_MAX) {
		*status = U_BUFFER_OVERFLOW_ERROR;
		ret.setToBogus();
		return FAILURE;
	}
	//the number of UTF-16 code units is not larger than that of UTF-8 code
	//units, + 1 for the terminator
	int32_t capacity = (int32_t)str_len + 1;

	//no check necessary -- if NULL will fail ahead
	UChar	*utf16 = ret.getBuffer(capacity);
	int32_t utf16_len = 0;
	*status = U_ZERO_ERROR;
	u_strFromUTF8WithSub(utf16, ret.getCapacity(), &utf16_len,
		str, str_len, U_SENTINEL /* no substitution */, NULL,
		status);
	ret.releaseBuffer(utf16_len);
	if (U_FAILURE(*status)) {
		ret.setToBogus();
		return FAILURE;
	}
	return SUCCESS;
}