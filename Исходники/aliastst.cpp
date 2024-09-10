UBool LocaleAliasTest::isLocaleAvailable(const char* loc){
    if(resIndex==NULL){
        return FALSE;
    }
    UErrorCode status = U_ZERO_ERROR;
    int32_t len = 0;
    ures_getStringByKey(resIndex, loc,&len, &status);
    if(U_FAILURE(status)){
        return FALSE; 
    }
    return TRUE;
}