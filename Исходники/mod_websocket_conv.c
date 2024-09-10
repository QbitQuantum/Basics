mod_websocket_bool_t
mod_websocket_conv_isUTF8(const char *data, size_t siz) {
    mod_websocket_bool_t ret = MOD_WEBSOCKET_FALSE;
    UErrorCode err = U_ZERO_ERROR;
    UCharsetDetector *detector = NULL;
    const UCharsetMatch **match;
    int32_t f = 0, i;
    const char *name;

    if (!data || !siz) {
        return MOD_WEBSOCKET_TRUE;
    }
    if (siz > INT32_MAX) {
        return MOD_WEBSOCKET_FALSE;
    }
    detector = ucsdet_open(&err);
    if (U_FAILURE(err)) {
        return MOD_WEBSOCKET_FALSE;
    }
    ucsdet_setText(detector, data, siz, &err);
    if (U_FAILURE(err)) {
        goto go_out;
    }
    match = ucsdet_detectAll(detector, &f, &err);
    if (U_FAILURE(err)) {
        goto go_out;
    }
    for (i = 0; i < f; i++) {
        name = ucsdet_getName(match[i], &err);
        if (strcasecmp(MOD_WEBSOCKET_UTF8_STR, name) == 0) {
            ret = MOD_WEBSOCKET_TRUE;
            break;
        }
    }

 go_out:
    ucsdet_close(detector);
    detector = NULL;
    return ret;
}