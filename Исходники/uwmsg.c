/* Format a message and print it's output to fp */
U_CFUNC int u_wmsg(FILE *fp, const char *tag, ... )
{
    const UChar *msg;
    int32_t      msgLen;
    UErrorCode  err = U_ZERO_ERROR;
#if !UCONFIG_NO_FORMATTING
    va_list ap;
#endif
    UChar   result[4096];
    int32_t resultLength = LENGTHOF(result);

    if(gBundle == NULL)
    {
#if 0
        fprintf(stderr, "u_wmsg: No path set!!\n"); /* FIXME: codepage?? */
#endif
        return -1;
    }

    msg = ures_getStringByKey(gBundle, tag, &msgLen, &err);

    if(U_FAILURE(err))
    {
        return -1;
    }

#if UCONFIG_NO_FORMATTING
    resultLength = sizeof(gNoFormatting) / U_SIZEOF_UCHAR;
    if((msgLen + resultLength) <= LENGTHOF(result)) {
        memcpy(result, msg, msgLen * U_SIZEOF_UCHAR);
        memcpy(result + msgLen, gNoFormatting, resultLength);
        resultLength += msgLen;
        uprint(result, resultLength, fp, &err);
    } else {
        uprint(msg,msgLen, fp, &err);
    }
#else
    va_start(ap, tag);

    resultLength = u_vformatMessage(uloc_getDefault(), msg, msgLen, result, resultLength, ap, &err);

    va_end(ap);

    if(U_FAILURE(err))
    {
#if 0
        fprintf(stderr, "u_wmsg: failed to format %s:%s, err %s\n",
            uloc_getDefault(),
            tag,
            u_errorName(err));
#endif
        err = U_ZERO_ERROR;
        uprint(msg,msgLen, fp, &err);
        return -1;
    }

    uprint(result, resultLength, fp, &err);
#endif

    if(U_FAILURE(err))
    {
#if 0
        fprintf(stderr, "u_wmsg: failed to print %s: %s, err %s\n",
            uloc_getDefault(),
            tag,
            u_errorName(err));
#endif
        return -1;
    }

    return 0;
}