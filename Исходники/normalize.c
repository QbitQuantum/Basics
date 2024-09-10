int helper_collation_str(const char *src, char *dest, int dest_size)
{
	HELPER_FN_CALL;
	int32_t size = 0;
	UErrorCode status = 0;
	UChar tmp_result[CTS_SQL_MAX_LEN];
	UCollator *collator;
	const char *region;

	region = vconf_get_str(VCONFKEY_REGIONFORMAT);
	HELPER_DBG("region %s", region);
	collator = ucol_open(region, &status);
	h_retvm_if(U_FAILURE(status), CTS_ERR_ICU_FAILED,
			"ucol_open() Failed(%s)", u_errorName(status));

	if (U_FAILURE(status)){
		ERR("ucol_setAttribute Failed(%s)", u_errorName(status));
		ucol_close(collator);
		return CTS_ERR_ICU_FAILED;
	}

	u_strFromUTF8(tmp_result, array_sizeof(tmp_result), NULL, src, -1, &status);
	if (U_FAILURE(status)){
		ERR("u_strFromUTF8 Failed(%s)", u_errorName(status));
		ucol_close(collator);
		return CTS_ERR_ICU_FAILED;
	}
	size = ucol_getSortKey(collator, tmp_result, -1, (uint8_t *)dest, dest_size);
	ucol_close(collator);
	dest[size]='\0';

	return CTS_SUCCESS;
}