/**
 * Phalcon\Db\Index constructor
 */
PHP_METHOD(Phalcon_Db_Index, __construct) {

	zval columns;
	zval *name_param = NULL, *columns_param = NULL, *type_param = NULL;
	zval name, type;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&columns);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &name_param, &columns_param, &type_param);

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
	ZEPHIR_OBS_COPY_OR_DUP(&columns, columns_param);
	if (!type_param) {
		ZEPHIR_INIT_VAR(&type);
		ZVAL_STRING(&type, "");
	} else {
		zephir_get_strval(&type, type_param);
	}


	zephir_update_property_zval(this_ptr, SL("_name"), &name);
	zephir_update_property_zval(this_ptr, SL("_columns"), &columns);
	zephir_update_property_zval(this_ptr, SL("_type"), &type);
	ZEPHIR_MM_RESTORE();

}