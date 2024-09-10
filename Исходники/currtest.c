static void TestPrefixSuffix(void) {
    int32_t	pos;
    UErrorCode status;
    double result1 = 0.0, result2 = 0.0;
    UNumberFormat* parser;
    UChar buffer[4];
    static const UChar TEST_NUMBER[] = {0x0024,0x0031,0x0032,0x002E,0x0030,0x0030,0}; /* $12.00 */
    static const UChar NEG_PREFIX[] = {0x005B,0}; /* "[" */
    static const UChar NEG_SUFFIX[] = {0x005D,0}; /* "]" */


	status = U_ZERO_ERROR;
	parser = unum_open(UNUM_CURRENCY, NULL, -1, "en_US", NULL, &status);
    if (U_FAILURE(status)) {
       log_data_err("Error: unum_open returned %s (Are you missing data?)\n", u_errorName(status));
       return;
    }

	pos = 0;
	status = U_ZERO_ERROR;
	result1 = unum_parseDoubleCurrency(parser, TEST_NUMBER, -1, &pos, buffer, &status);

	unum_setTextAttribute(parser, UNUM_NEGATIVE_SUFFIX, NEG_SUFFIX, -1, &status);
	unum_setTextAttribute(parser, UNUM_NEGATIVE_PREFIX, NEG_PREFIX, -1, &status);
    if (U_FAILURE(status)) {
       log_err("Error: unum_setTextAttribute returned %s\n", u_errorName(status));
       return;
    }

	pos = 0;
	result2 = unum_parseDoubleCurrency(parser, TEST_NUMBER, -1, &pos, buffer, &status);
    if (result1 != result2 || U_FAILURE(status)) {
       log_err("Error: unum_parseDoubleCurrency didn't return the same value for same string %f %f %s\n",
           result1, result2, u_errorName(status));
    }
    unum_close(parser);
}