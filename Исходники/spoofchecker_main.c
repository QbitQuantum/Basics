/* {{{ proto bool Spoofchecker::areConfusable( string str1, string str2[, int &error_code ] )
 * Checks if a given text contains any confusable characters
 */
PHP_METHOD(Spoofchecker, areConfusable)
{
	int ret;
	char *s1, *s2;
	int s1_len, s2_len;
	zval *error_code = NULL;
	SPOOFCHECKER_METHOD_INIT_VARS;
	
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|z", &s1, &s1_len,
										 &s2, &s2_len, &error_code)) {
		return;
	}

	SPOOFCHECKER_METHOD_FETCH_OBJECT;

	ret = uspoof_areConfusableUTF8(co->uspoof, s1, s1_len, s2, s2_len, SPOOFCHECKER_ERROR_CODE_P(co));

	if (U_FAILURE(SPOOFCHECKER_ERROR_CODE(co))) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "(%d) %s", SPOOFCHECKER_ERROR_CODE(co), u_errorName(SPOOFCHECKER_ERROR_CODE(co)));
		RETURN_TRUE;
	}
	
	if (error_code) {
		zval_dtor(error_code);
		ZVAL_LONG(error_code, ret);
	}
	RETVAL_BOOL(ret != 0);
}