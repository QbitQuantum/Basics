static int berDecodeLoginData(
    struct berval *replyBV,
    int      *serverVersion,
    size_t   *retDataLen,
    void     *retData )
{
    int err = 0;
    BerElement *replyBer = NULL;
    char    *retOctStr = NULL;
    size_t  retOctStrLen = 0;

    if ((replyBer = ber_init(replyBV)) == NULL) {
        err = LDAP_OPERATIONS_ERROR;
        goto Cleanup;
    }

    if (retData) {
        retOctStrLen = *retDataLen + 1;
        retOctStr = SMB_MALLOC_ARRAY(char, retOctStrLen);
        if (!retOctStr) {
            err = LDAP_OPERATIONS_ERROR;
            goto Cleanup;
        }

        if (ber_scanf(replyBer, "{iis}", serverVersion, &err, retOctStr, &retOctStrLen) != -1) {
            if (*retDataLen >= retOctStrLen) {
                memcpy(retData, retOctStr, retOctStrLen);
            } else if (!err) {
                err = LDAP_NO_MEMORY;
            }

            *retDataLen = retOctStrLen;
        } else if (!err) {
            err = LDAP_DECODING_ERROR;
        }
    } else {
        if (ber_scanf(replyBer, "{ii}", serverVersion, &err) == -1) {