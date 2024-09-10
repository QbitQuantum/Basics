UBool isEuroAware(UConverter* myConv)
{
    static const UChar euroString[2] = { 0x20AC, 0x0000 };
    char target[20];
    UChar euroBack[2];
    int32_t targetSize, euroBackSize;
    UErrorCode err = U_ZERO_ERROR;
    /*const char* myName =   ucnv_getName(myConv, &err);*/

    targetSize = ucnv_fromUChars(myConv,
            target,
            sizeof(target),
            euroString,
            -1,
            &err);
    if (U_FAILURE(err))
    {
      log_err("Failure Occured in ucnv_fromUChars euro roundtrip test\n");
      return FALSE;
    }
    euroBackSize = ucnv_toUChars(myConv,
            euroBack,
            2,
            target,
            targetSize,
            &err);
    if (U_FAILURE(err))
    {
        log_err("Failure Occured in ucnv_toUChars euro roundtrip test\n");
        return FALSE;
    }
    if (u_strcmp(euroString, euroBack)) 
    {
        /*      log_err("%s FAILED Euro rountrip\n", myName);*/
        return FALSE;
    }
    else 
    {
        /*      log_verbose("%s PASSED Euro rountrip\n", myName);*/
        return TRUE;
    }

}