static void regexp_ctor(INTERNAL_FUNCTION_PARAMETERS)
{
    zval *object;
    Regexp_object *ro;
    char *pattern;
    int32_t pattern_len;
    UChar *upattern = NULL;
    int32_t upattern_len = 0;
    zval *zflags = NULL;
    uint32_t flags = 0;
    UParseError pe = { -1, -1, {0}, {0} };

    intl_error_reset(NULL TSRMLS_CC);
    object = return_value;
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|z", &pattern, &pattern_len, &zflags)) {
        intl_error_set(NULL, U_ILLEGAL_ARGUMENT_ERROR, "bad arguments", 0 TSRMLS_CC);
        zval_dtor(object);
        RETURN_NULL();
    }
    if (NULL != zflags) {
        switch (Z_TYPE_P(zflags)) {
            case IS_LONG:
                flags = (uint32_t) Z_LVAL_P(zflags);
                break;
            case IS_STRING:
            {
                const char *p;

                for (p = Z_STRVAL_P(zflags); '\0' != *p; p++) {
                    switch (*p) {
                        case 'i': flags |= UREGEX_CASE_INSENSITIVE; break;
                        case 'm': flags |= UREGEX_MULTILINE;        break;
                        case 's': flags |= UREGEX_DOTALL;           break;
                        case 'x': flags |= UREGEX_COMMENTS;         break;
                        case 'w': flags |= UREGEX_UWORD;            break;
                        default:
                            intl_error_set(NULL, U_ILLEGAL_ARGUMENT_ERROR, "invalid modifier", 0 TSRMLS_CC);
                            zval_dtor(object);
                            RETURN_NULL();
                    }
                }
                break;
            }
            default:
                intl_error_set(NULL, U_ILLEGAL_ARGUMENT_ERROR, "bad arguments", 0 TSRMLS_CC);
                zval_dtor(object);
                RETURN_NULL();
        }
    }
    ro = (Regexp_object *) zend_object_store_get_object(object TSRMLS_CC);
    intl_convert_utf8_to_utf16(&upattern, &upattern_len, pattern, pattern_len, REGEXP_ERROR_CODE_P(ro));
    INTL_CTOR_CHECK_STATUS(ro, "string conversion of pattern to UTF-16 failed");
    ro->uregex = uregex_open(upattern, upattern_len, flags, &pe, REGEXP_ERROR_CODE_P(ro));
    efree(upattern);
    if (U_FAILURE(REGEXP_ERROR_CODE(ro))) {
        intl_error_set_code(NULL, REGEXP_ERROR_CODE(ro) TSRMLS_CC);
        if (-1 != pe.line) {
            regexp_parse_error_to_string(pe, pattern, pattern_len);
        } else {
            intl_error_set_custom_msg(NULL, "unable to compile ICU regular expression", 0 TSRMLS_CC);
        }
        zval_dtor(object);
        RETURN_NULL();
    }
}