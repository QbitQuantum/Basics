/**
 * Changes the padding scheme used
 */
PHP_METHOD(Phalcon_Crypt, setPadding) {

	zval *scheme_param = NULL, *_0;
	zend_long scheme;

	zephir_fetch_params(0, 1, 0, &scheme_param);

	if (UNEXPECTED(Z_TYPE_P(scheme_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'scheme' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	scheme = Z_LVAL_P(scheme_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, scheme);
	zephir_update_property_this(getThis(), SL("_padding"), _0 TSRMLS_CC);
	RETURN_THISW();

}