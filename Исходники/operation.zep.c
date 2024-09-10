/**
 * Phalcon\Acl\Operation constructor
 */
PHP_METHOD(Phalcon_Acl_Operation, __construct) {

	zval *name_param = NULL, *description_param = NULL;
	zval name, description;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&description);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &description_param);

	if (UNEXPECTED(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(name_param) == IS_STRING)) {
		zephir_get_strval(&name, name_param);
	} else {
		ZEPHIR_INIT_VAR(&name);
		ZVAL_EMPTY_STRING(&name);
	}
	if (!description_param) {
		ZEPHIR_INIT_VAR(&description);
		ZVAL_STRING(&description, "");
	} else {
		zephir_get_strval(&description, description_param);
	}


	if (ZEPHIR_IS_STRING(&name, "*")) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_acl_exception_ce, "Operation name cannot be '*'", "phalcon/acl/operation.zep", 40);
		return;
	}
	zephir_update_property_zval(this_ptr, SL("name"), &name);
	if (!(Z_TYPE_P(&description) == IS_UNDEF) && Z_STRLEN_P(&description)) {
		zephir_update_property_zval(this_ptr, SL("description"), &description);
	}
	ZEPHIR_MM_RESTORE();

}