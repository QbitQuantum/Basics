PHP_METHOD(jz_data, offsetUnset) {
	zval *readonly = zend_read_property(jz_data_class_entry, getThis(), ZEND_STRL(JZ_DATA_PROPERT_NAME_READONLY), 1, NULL);

	if (Z_TYPE_P(readonly) == IS_FALSE) {
		zval *props;
		zend_string *name;
		if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &name) == FAILURE) {
			return;
		}

		props = zend_read_property(jz_data_class_entry, getThis(), ZEND_STRL(JZ_DATA_PROPERT_NAME), 1, NULL);
		if (UNEXPECTED(Z_TYPE_P(props) != IS_ARRAY)) {
			RETURN_FALSE;
		}
		if (zend_hash_del(Z_ARRVAL_P(props), name) == SUCCESS) {
			RETURN_TRUE;
		}
	}

	RETURN_FALSE;
}