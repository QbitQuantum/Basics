static int create_transliterator( char *str_id, int str_id_len, zend_long direction, zval *object )
{
	Transliterator_object *to;
	UChar	              *ustr_id    = NULL;
	int32_t               ustr_id_len = 0;
	UTransliterator       *utrans;
	UParseError           parse_error   = {0, -1};

	intl_error_reset( NULL );

	if( ( direction != TRANSLITERATOR_FORWARD ) && (direction != TRANSLITERATOR_REVERSE ) )
	{
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
			"transliterator_create: invalid direction", 0 );
		return FAILURE;
	}

	object_init_ex( object, Transliterator_ce_ptr );
	TRANSLITERATOR_METHOD_FETCH_OBJECT_NO_CHECK; /* fetch zend object from zval "object" into "to" */

	/* Convert transliterator id to UTF-16 */
	intl_convert_utf8_to_utf16( &ustr_id, &ustr_id_len, str_id, str_id_len, TRANSLITERATOR_ERROR_CODE_P( to ) );
	if( U_FAILURE( TRANSLITERATOR_ERROR_CODE( to ) ) )
	{
		intl_error_set_code( NULL, TRANSLITERATOR_ERROR_CODE( to ) );
		intl_error_set_custom_msg( NULL, "String conversion of id to UTF-16 failed", 0 );
		zval_dtor( object );
		return FAILURE;
	}

	/* Open ICU Transliterator. */
	utrans = utrans_openU( ustr_id, ustr_id_len, (UTransDirection ) direction,
		NULL, -1, &parse_error, TRANSLITERATOR_ERROR_CODE_P( to ) );
	if (ustr_id) {
		efree( ustr_id );
	}
	
	if( U_FAILURE( TRANSLITERATOR_ERROR_CODE( to ) ) )
	{
		char *buf = NULL;
		intl_error_set_code( NULL, TRANSLITERATOR_ERROR_CODE( to ) );
		spprintf( &buf, 0, "transliterator_create: unable to open ICU transliterator"
			" with id \"%s\"", str_id );
		if( buf == NULL ) {
			intl_error_set_custom_msg( NULL,
				"transliterator_create: unable to open ICU transliterator", 0 );
		}
		else
		{
			intl_error_set_custom_msg( NULL, buf, /* copy message */ 1 );
			efree( buf );
		}
		zval_dtor( object );
		return FAILURE;
	}
	
	transliterator_object_construct( object, utrans, TRANSLITERATOR_ERROR_CODE_P( to ) );
	/* no need to close the transliterator manually on construction error */
	if( U_FAILURE( TRANSLITERATOR_ERROR_CODE( to ) ) )
	{
		intl_error_set_code( NULL, TRANSLITERATOR_ERROR_CODE( to ) );
		intl_error_set_custom_msg( NULL,
			"transliterator_create: internal constructor call failed", 0 );
		zval_dtor( object );
		return FAILURE;
	}

	return SUCCESS;
}