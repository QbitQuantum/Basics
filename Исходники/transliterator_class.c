{
	const UChar           *ustr_id;
	int32_t               ustr_id_len;
	char                  *str_id;
	int                   str_id_len;
	Transliterator_object *to;

	TRANSLITERATOR_METHOD_FETCH_OBJECT_NO_CHECK;

	assert( to->utrans == NULL );
	/* this assignment must happen before any return with failure because the
	 * caller relies on it always being made (so it can just destroy the object
	 * to close the transliterator) */
	to->utrans = utrans;

	ustr_id = utrans_getUnicodeID( utrans, &ustr_id_len );
	intl_convert_utf16_to_utf8( &str_id, &str_id_len, ustr_id, (int ) ustr_id_len, status );
	if( U_FAILURE( *status ) )
	{
		return FAILURE;
	}

	zend_update_property_stringl(Transliterator_ce_ptr, object,
		"id", sizeof( "id" ) - 1, str_id, str_id_len TSRMLS_CC );
	efree( str_id );
	return SUCCESS;
}
/* }}} */

/*
 * Auxiliary functions needed by objects of 'Transliterator' class