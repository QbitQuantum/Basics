void
ResourceBundleTest::TestExemplar(){

    int32_t locCount = uloc_countAvailable();
    int32_t locIndex=0;
    int num=0;
    UErrorCode status = U_ZERO_ERROR;
    for(;locIndex<locCount;locIndex++){
        const char* locale = uloc_getAvailable(locIndex);
        UResourceBundle *resb =ures_open(NULL,locale,&status);
        if(U_SUCCESS(status) && status!=U_USING_FALLBACK_WARNING && status!=U_USING_DEFAULT_WARNING){
            int32_t len=0;
            const UChar* strSet = ures_getStringByKey(resb,"ExemplarCharacters",&len,&status);
            UnicodeSet set(strSet,status);
            if(U_FAILURE(status)){
                errln("Could not construct UnicodeSet from pattern for ExemplarCharacters in locale : %s. Error: %s",locale,u_errorName(status));
                status=U_ZERO_ERROR;
            }
            num++;
        }
        ures_close(resb);
    }
    logln("Number of installed locales with exemplar characters that could be tested: %d",num);

}