/* {{{ proto BSON\UTCDateTime UTCDateTime::__construct(integer $milliseconds)
   Construct a new UTCDateTime */
PHP_METHOD(UTCDateTime, __construct)
{
	php_phongo_utcdatetime_t    *intern;
	zend_error_handling       error_handling;
	long                      milliseconds;
#if SIZEOF_LONG == 4
	char                        *s_milliseconds;
	int 	                     s_milliseconds_len;
#endif


	zend_replace_error_handling(EH_THROW, phongo_exception_from_phongo_domain(PHONGO_ERROR_INVALID_ARGUMENT), &error_handling TSRMLS_CC);
	intern = (php_phongo_utcdatetime_t *)zend_object_store_get_object(getThis() TSRMLS_CC);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &milliseconds) == FAILURE) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}
#if SIZEOF_LONG == 4
	if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "s", &s_milliseconds, &s_milliseconds_len) == FAILURE) {
		zend_restore_error_handling(&error_handling TSRMLS_CC);
		return;
	}

	intern->milliseconds = STRTOLL(s_milliseconds);
#else
	intern->milliseconds = milliseconds;
#endif

	zend_restore_error_handling(&error_handling TSRMLS_CC);

}