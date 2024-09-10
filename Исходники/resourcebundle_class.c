/* {{{ resourcebundle_array_fetch */
static void resourcebundle_array_fetch(zval *object, zval *offset, zval *return_value, int fallback)
{
	int32_t     meindex = 0;
	char *      mekey = NULL;
    zend_bool    is_numeric = 0;
	char         *pbuf;
	ResourceBundle_object *rb;

	intl_error_reset( NULL );
	RESOURCEBUNDLE_METHOD_FETCH_OBJECT;

	if(Z_TYPE_P(offset) == IS_LONG) {
		is_numeric = 1;
		meindex = (int32_t)Z_LVAL_P(offset);
		rb->child = ures_getByIndex( rb->me, meindex, rb->child, &INTL_DATA_ERROR_CODE(rb) );
	} else if(Z_TYPE_P(offset) == IS_STRING) {
		mekey = Z_STRVAL_P(offset);
		rb->child = ures_getByKey(rb->me, mekey, rb->child, &INTL_DATA_ERROR_CODE(rb) );
	} else {
		intl_errors_set(INTL_DATA_ERROR_P(rb), U_ILLEGAL_ARGUMENT_ERROR,
			"resourcebundle_get: index should be integer or string", 0);
		RETURN_NULL();
	}

	intl_error_set_code( NULL, INTL_DATA_ERROR_CODE(rb) );
	if (U_FAILURE(INTL_DATA_ERROR_CODE(rb))) {
		if (is_numeric) {
			spprintf( &pbuf, 0, "Cannot load resource element %d", meindex );
		} else {
			spprintf( &pbuf, 0, "Cannot load resource element '%s'", mekey );
		}
		intl_errors_set_custom_msg( INTL_DATA_ERROR_P(rb), pbuf, 1 );
		efree(pbuf);
		RETURN_NULL();
	}

	if (!fallback && (INTL_DATA_ERROR_CODE(rb) == U_USING_FALLBACK_WARNING || INTL_DATA_ERROR_CODE(rb) == U_USING_DEFAULT_WARNING)) {
		UErrorCode icuerror;
		const char * locale = ures_getLocaleByType( rb->me, ULOC_ACTUAL_LOCALE, &icuerror );
		if (is_numeric) {
			spprintf( &pbuf, 0, "Cannot load element %d without fallback from to %s", meindex, locale );
		} else {
			spprintf( &pbuf, 0, "Cannot load element '%s' without fallback from to %s", mekey, locale );
		}
		intl_errors_set_custom_msg( INTL_DATA_ERROR_P(rb), pbuf, 1 );
		efree(pbuf);
		RETURN_NULL();
	}

	resourcebundle_extract_value( return_value, rb );
}