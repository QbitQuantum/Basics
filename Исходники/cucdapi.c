void TestBinaryValues() {
    /*
     * Unicode 5.1 explicitly defines binary property value aliases.
     * Verify that they are all recognized.
     */
    static const char *const falseValues[]={ "N", "No", "F", "False" };
    static const char *const trueValues[]={ "Y", "Yes", "T", "True" };
    int32_t i;
    for(i=0; i<LENGTHOF(falseValues); ++i) {
        if(FALSE!=u_getPropertyValueEnum(UCHAR_ALPHABETIC, falseValues[i])) {
            log_data_err("u_getPropertyValueEnum(UCHAR_ALPHABETIC, \"%s\")!=FALSE (Are you missing data?)\n", falseValues[i]);
        }
    }
    for(i=0; i<LENGTHOF(trueValues); ++i) {
        if(TRUE!=u_getPropertyValueEnum(UCHAR_ALPHABETIC, trueValues[i])) {
            log_data_err("u_getPropertyValueEnum(UCHAR_ALPHABETIC, \"%s\")!=TRUE (Are you missing data?)\n", trueValues[i]);
        }
    }
}