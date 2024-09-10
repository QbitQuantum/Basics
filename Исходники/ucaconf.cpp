void UCAConformanceTest::initRbUCA() 
{
  if(!rbUCA) {
    UParseError parseError;
    UChar      *ucarules = buffer;
    int32_t size = ucol_getRulesEx(UCA, UCOL_FULL_RULES, ucarules, 
                                   BUFFER_SIZE_);
    if (size > BUFFER_SIZE_) {
        ucarules = (UChar *)malloc(size * sizeof(UChar));
        size = ucol_getRulesEx(UCA, UCOL_FULL_RULES, ucarules, size);
    }
    rbUCA = ucol_openRules(ucarules, size, UCOL_DEFAULT, UCOL_TERTIARY, 
                          &parseError, &status);
    if (U_FAILURE(status)) {
        errln("Failure creating UCA rule-based collator.");
        return;
    }
  }
}