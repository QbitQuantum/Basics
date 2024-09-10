/**
 * Can delay any new job being reserved for a given time.
 */
PHP_METHOD(Phalcon_Queue_Beanstalk, pauseTube) {

	int delay, ZEPHIR_LAST_CALL_STATUS;
	zval *tube_param = NULL, *delay_param = NULL, *response = NULL, _0, *_2;
	zval *tube = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &tube_param, &delay_param);

	if (UNEXPECTED(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(tube);
		ZVAL_EMPTY_STRING(tube);
	}
	delay = zephir_get_intval(delay_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, delay);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SVSV(_1, "pause-tube ", tube, " ", &_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "write", NULL, 0, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "readstatus", NULL, 409);
	zephir_check_call_status();
	zephir_array_fetch_long(&_2, response, 0, PH_NOISY | PH_READONLY, "phalcon/queue/beanstalk.zep", 289 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(_2, "PAUSED")) {
		RETURN_MM_BOOL(0);
	}
	RETURN_MM_BOOL(1);

}