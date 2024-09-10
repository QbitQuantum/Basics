U_CAPI const UChar* U_EXPORT2
u_catgets(u_nl_catd catd, int32_t set_num, int32_t msg_num,
          const UChar* s,
          int32_t* len, UErrorCode* ec) {

    char key[MAX_KEY_LEN];
    const UChar* result;

    if (ec == NULL || U_FAILURE(*ec)) {
        goto ERROR;
    }

    result = ures_getStringByKey((const UResourceBundle*) catd,
                                 _catkey(key, set_num, msg_num),
                                 len, ec);
    if (U_FAILURE(*ec)) {
        goto ERROR;
    }

    return result;

 ERROR:
    /* In case of any failure, return s */
    if (len != NULL) {
        *len = u_strlen(s);
    }
    return s;
}