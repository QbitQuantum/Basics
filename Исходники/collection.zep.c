/**
 * Sets if the main handler must be lazy loaded
 */
PHP_METHOD(Phalcon_Mvc_Micro_Collection, setLazy) {

	zval *lazy_param = NULL;
	zend_bool lazy;

	zephir_fetch_params(0, 1, 0, &lazy_param);

	if (UNEXPECTED(Z_TYPE_P(lazy_param) != IS_BOOL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'lazy' must be a bool") TSRMLS_CC);
		RETURN_NULL();
	}
	lazy = Z_BVAL_P(lazy_param);


	if (lazy) {
		zephir_update_property_this(getThis(), SL("_lazy"), ZEPHIR_GLOBAL(global_true) TSRMLS_CC);
	} else {
		zephir_update_property_this(getThis(), SL("_lazy"), ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	}
	RETURN_THISW();

}