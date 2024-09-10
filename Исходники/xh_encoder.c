static UConverter *
xh_encoder_uconv_create(xh_char_t *encoding, xh_bool_t toUnicode)
{
    UConverter *uconv;
    UErrorCode  status = U_ZERO_ERROR;

    uconv = ucnv_open((char *) encoding, &status);
    if ( U_FAILURE(status) ) {
        return NULL;
    }

    if (toUnicode) {
        ucnv_setToUCallBack(uconv, UCNV_TO_U_CALLBACK_STOP,
                            NULL, NULL, NULL, &status);
    }
    else {
        ucnv_setFromUCallBack(uconv, UCNV_FROM_U_CALLBACK_STOP,
                              NULL, NULL, NULL, &status);
    }

    return uconv;
}