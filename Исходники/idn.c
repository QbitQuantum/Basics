static void php_intl_idn_to_46(INTERNAL_FUNCTION_PARAMETERS,
		const char *domain, int32_t domain_len, uint32_t option, int mode, zval *idna_info)
{
	UErrorCode	  status = U_ZERO_ERROR;
	UIDNA		  *uts46;
	int32_t		  len;
	int32_t		  buffer_capac = 255; /* no domain name may exceed this */
	zend_string	  *buffer = zend_string_alloc(buffer_capac, 0);
	UIDNAInfo	  info = UIDNA_INFO_INITIALIZER;
	int			  buffer_used = 0;

	uts46 = uidna_openUTS46(option, &status);
	if (php_intl_idn_check_status(status, "failed to open UIDNA instance",
			mode) == FAILURE) {
		zend_string_free(buffer);
		RETURN_FALSE;
	}

	if (mode == INTL_IDN_TO_ASCII) {
		len = uidna_nameToASCII_UTF8(uts46, domain, domain_len,
				ZSTR_VAL(buffer), buffer_capac, &info, &status);
	} else {
		len = uidna_nameToUnicodeUTF8(uts46, domain, domain_len,
				ZSTR_VAL(buffer), buffer_capac, &info, &status);
	}
	if (php_intl_idn_check_status(status, "failed to convert name",
			mode) == FAILURE) {
		uidna_close(uts46);
		zend_string_free(buffer);
		RETURN_FALSE;
	}
	if (len >= 255) {
		php_error_docref(NULL, E_ERROR, "ICU returned an unexpected length");
	}

	ZSTR_VAL(buffer)[len] = '\0';
	ZSTR_LEN(buffer) = len;

	if (info.errors == 0) {
		RETVAL_STR(buffer);
		buffer_used = 1;
	} else {
		RETVAL_FALSE;
	}

	if (idna_info) {
		if (buffer_used) { /* used in return_value then */
			zval_addref_p(return_value);
			add_assoc_zval_ex(idna_info, "result", sizeof("result")-1, return_value);
		} else {
			zval zv;
			ZVAL_NEW_STR(&zv, buffer);
			buffer_used = 1;
			add_assoc_zval_ex(idna_info, "result", sizeof("result")-1, &zv);
		}
		add_assoc_bool_ex(idna_info, "isTransitionalDifferent",
				sizeof("isTransitionalDifferent")-1, info.isTransitionalDifferent);
		add_assoc_long_ex(idna_info, "errors", sizeof("errors")-1, (zend_long)info.errors);
	}

	if (!buffer_used) {
		zend_string_free(buffer);
	}

	uidna_close(uts46);
}