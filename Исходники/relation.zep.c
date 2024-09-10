/**
 * Phalcon\Mvc\Model\Relation constructor
 *
 * @param int type
 * @param string|array fields
 * @param string|array referencedFields
 * @param array options
 */
PHP_METHOD(Phalcon_Mvc_Model_Relation, __construct) {

	zval referencedModel;
	zval *type, type_sub, *referencedModel_param = NULL, *fields, fields_sub, *referencedFields, referencedFields_sub, *options = NULL, options_sub, __$null;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&type_sub);
	ZVAL_UNDEF(&fields_sub);
	ZVAL_UNDEF(&referencedFields_sub);
	ZVAL_UNDEF(&options_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&referencedModel);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 1, &type, &referencedModel_param, &fields, &referencedFields, &options);

	if (UNEXPECTED(Z_TYPE_P(referencedModel_param) != IS_STRING && Z_TYPE_P(referencedModel_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'referencedModel' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(referencedModel_param) == IS_STRING)) {
		zephir_get_strval(&referencedModel, referencedModel_param);
	} else {
		ZEPHIR_INIT_VAR(&referencedModel);
		ZVAL_EMPTY_STRING(&referencedModel);
	}
	if (!options) {
		options = &options_sub;
		options = &__$null;
	}


	zephir_update_property_zval(this_ptr, SL("_type"), type);
	zephir_update_property_zval(this_ptr, SL("_referencedModel"), &referencedModel);
	zephir_update_property_zval(this_ptr, SL("_fields"), fields);
	zephir_update_property_zval(this_ptr, SL("_referencedFields"), referencedFields);
	zephir_update_property_zval(this_ptr, SL("_options"), options);
	ZEPHIR_MM_RESTORE();

}