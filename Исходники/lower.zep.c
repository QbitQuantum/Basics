/**
 * @var mixed input The text to sanitize
 */
PHP_METHOD(Phalcon_Filter_Sanitize_Lower, __invoke) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *input_param = NULL, _0$$3, _1$$3, _2;
	zval input;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&input);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &input_param);

	if (UNEXPECTED(Z_TYPE_P(input_param) != IS_STRING && Z_TYPE_P(input_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'input' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(input_param) == IS_STRING)) {
		zephir_get_strval(&input, input_param);
	} else {
		ZEPHIR_INIT_VAR(&input);
		ZVAL_EMPTY_STRING(&input);
	}


	if (1 == (zephir_function_exists_ex(SL("mb_convert_case") TSRMLS_CC) == SUCCESS)) {
		ZVAL_LONG(&_0$$3, 1);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "UTF-8");
		ZEPHIR_RETURN_CALL_FUNCTION("mb_convert_case", NULL, 189, &input, &_0$$3, &_1$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_CALL_FUNCTION(&_2, "utf8_decode", NULL, 190, &input);
	zephir_check_call_status();
	zephir_fast_strtolower(return_value, &_2);
	RETURN_MM();

}