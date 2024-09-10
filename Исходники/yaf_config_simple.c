/** {{{ proto public Yaf_Config_Simple::offsetUnset($index)
*/
PHP_METHOD(yaf_config_simple, offsetUnset) {
	zval *readonly = zend_read_property(yaf_config_simple_ce,
			getThis(), ZEND_STRL(YAF_CONFIG_PROPERT_NAME_READONLY), 1, NULL);

	if (Z_TYPE_P(readonly) == IS_FALSE) {
		zval *props;
		zend_string *name;
		if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &name) == FAILURE) {
			return;
		}

		props = zend_read_property(yaf_config_simple_ce, getThis(), ZEND_STRL(YAF_CONFIG_PROPERT_NAME), 1, NULL);
		if (UNEXPECTED(Z_TYPE_P(props) != IS_ARRAY)) {
			RETURN_FALSE;
		}
		if (zend_hash_del(Z_ARRVAL_P(props), name) == SUCCESS) {
			RETURN_TRUE;
		}
	}

	RETURN_FALSE;
}