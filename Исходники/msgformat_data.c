int msgformat_fix_quotes(UChar **spattern, uint32_t *spattern_len, UErrorCode *ec)
{
	if(*spattern && *spattern_len && u_strchr(*spattern, (UChar)'\'')) {
		UChar *npattern = safe_emalloc(sizeof(UChar)*2, *spattern_len, sizeof(UChar));
		uint32_t npattern_len;
		npattern_len = umsg_autoQuoteApostrophe(*spattern, *spattern_len, npattern, 2*(*spattern_len)+1, ec);
		efree(*spattern);
		if( U_FAILURE(*ec) )
		{
			return FAILURE;
		}
		npattern = erealloc(npattern, sizeof(UChar)*(npattern_len+1));
		*spattern = npattern;
		*spattern_len = npattern_len;
	}
	return SUCCESS;
}