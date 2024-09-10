U_CAPI const UChar * U_EXPORT2
u_strTrailingWhiteSpaceStart(const UChar *s, int32_t length) {
    int32_t i = 0, toReturn = 0;
    UChar32 c = 0;
    
    if(s == NULL) {
        return NULL;
    }
    if(length == 0) {
        return s;
    }
    
    if(length < 0) {
        length = u_strlen(s);
    }
    
    i = length;
    for(;;) {
        toReturn = i;
        if(i <= 0) {
            break;
        }
        U16_PREV(s, 0, i, c);
        if(!(c == 0x20 || u_isUWhiteSpace(c))) {
            break;
        }
    }
    
    return s+toReturn;
}