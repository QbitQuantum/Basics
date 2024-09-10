/**
 * Returns an element added to the form by its name
 */
PHP_METHOD(Phalcon_Forms_Form, get) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *element = NULL, *_0, *_1;
	zval *name = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (UNEXPECTED(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(name, name_param);
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_OBS_VAR(element);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_elements"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&element, _0, name, 0 TSRMLS_CC)) {
		RETURN_CCTOR(element);
	}
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, phalcon_forms_exception_ce);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SVS(_2, "Element with ID=", name, " is not part of the form");
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 9, _2);
	zephir_check_call_status();
	zephir_throw_exception_debug(_1, "phalcon/forms/form.zep", 482 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}