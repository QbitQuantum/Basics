PHPAPI int php_setcookie(char *name, int name_len, char *value, int value_len, time_t expires, char *path, int path_len, char *domain, int domain_len, int secure, int url_encode, int httponly TSRMLS_DC)
{
	char *cookie;
	int len=sizeof("Set-Cookie: ");
	zend_string *dt;
	sapi_header_line ctr = {0};
	int result;
	zend_string *encoded_value = NULL;

	if (name && strpbrk(name, "=,; \t\r\n\013\014") != NULL) {   /* man isspace for \013 and \014 */
		zend_error( E_WARNING, "Cookie names cannot contain any of the following '=,; \\t\\r\\n\\013\\014'" );
		return FAILURE;
	}

	if (!url_encode && value && strpbrk(value, ",; \t\r\n\013\014") != NULL) { /* man isspace for \013 and \014 */
		zend_error( E_WARNING, "Cookie values cannot contain any of the following ',; \\t\\r\\n\\013\\014'" );
		return FAILURE;
	}

	len += name_len;
	if (value && url_encode) {
		encoded_value = php_url_encode(value, value_len);
		len += encoded_value->len;
	} else if (value) {
		encoded_value = zend_string_init(value, value_len, 0);
		len += encoded_value->len;
	}

	if (path) {
		len += path_len;
	}
	if (domain) {
		len += domain_len;
	}

	cookie = emalloc(len + 100);

	if (value && value_len == 0) {
		/*
		 * MSIE doesn't delete a cookie when you set it to a null value
		 * so in order to force cookies to be deleted, even on MSIE, we
		 * pick an expiry date in the past
		 */
		dt = php_format_date("D, d-M-Y H:i:s T", sizeof("D, d-M-Y H:i:s T")-1, 1, 0 TSRMLS_CC);
		snprintf(cookie, len + 100, "Set-Cookie: %s=deleted; expires=%s; Max-Age=0", name, dt->val);
		zend_string_free(dt);
	} else {
		snprintf(cookie, len + 100, "Set-Cookie: %s=%s", name, value ? encoded_value->val : "");
		if (expires > 0) {
			const char *p;
			char tsdelta[13];
			strlcat(cookie, COOKIE_EXPIRES, len + 100);
			dt = php_format_date("D, d-M-Y H:i:s T", sizeof("D, d-M-Y H:i:s T")-1, expires, 0 TSRMLS_CC);
			/* check to make sure that the year does not exceed 4 digits in length */
			p = zend_memrchr(dt->val, '-', dt->len);
			if (!p || *(p + 5) != ' ') {
				zend_string_free(dt);
				efree(cookie);
				zend_string_free(encoded_value);
				zend_error(E_WARNING, "Expiry date cannot have a year greater than 9999");
				return FAILURE;
			}
			strlcat(cookie, dt->val, len + 100);
			zend_string_free(dt);

			snprintf(tsdelta, sizeof(tsdelta), ZEND_LONG_FMT, (zend_long) difftime(expires, time(NULL)));
			strlcat(cookie, COOKIE_MAX_AGE, len + 100);
			strlcat(cookie, tsdelta, len + 100);
		}
	}

	if (encoded_value) {
		zend_string_free(encoded_value);
	}

	if (path && path_len > 0) {
		strlcat(cookie, COOKIE_PATH, len + 100);
		strlcat(cookie, path, len + 100);
	}
	if (domain && domain_len > 0) {
		strlcat(cookie, COOKIE_DOMAIN, len + 100);
		strlcat(cookie, domain, len + 100);
	}
	if (secure) {
		strlcat(cookie, COOKIE_SECURE, len + 100);
	}
	if (httponly) {
		strlcat(cookie, COOKIE_HTTPONLY, len + 100);
	}

	ctr.line = cookie;
	ctr.line_len = strlen(cookie);

	result = sapi_header_op(SAPI_HEADER_ADD, &ctr TSRMLS_CC);
	efree(cookie);
	return result;
}