// Use LocalXyzPointer types that are not covered elsewhere in the intltest suite.
void LocalPointerTest::TestLocalXyzPointer() {
    IcuTestErrorCode errorCode(*this, "TestLocalXyzPointer");

    static const char *const encoding="ISO-8859-1";
    LocalUConverterSelectorPointer sel(
        ucnvsel_open(&encoding, 1, NULL, UCNV_ROUNDTRIP_SET, errorCode));
    if(errorCode.logIfFailureAndReset("ucnvsel_open()")) {
        return;
    }
    if(sel.isNull()) {
        errln("LocalUConverterSelectorPointer failure");
        return;
    }

#if !UCONFIG_NO_FORMATTING
    LocalUCalendarPointer cal(ucal_open(NULL, 0, "root", UCAL_GREGORIAN, errorCode));
    if(errorCode.logDataIfFailureAndReset("ucal_open()")) {
        return;
    }
    if(cal.isNull()) {
        errln("LocalUCalendarPointer failure");
        return;
    }

    LocalUDateTimePatternGeneratorPointer patgen(udatpg_open("root", errorCode));
    if(errorCode.logDataIfFailureAndReset("udatpg_open()")) {
        return;
    }
    if(patgen.isNull()) {
        errln("LocalUDateTimePatternGeneratorPointer failure");
        return;
    }

    LocalULocaleDisplayNamesPointer ldn(uldn_open("de-CH", ULDN_STANDARD_NAMES, errorCode));
    if(errorCode.logIfFailureAndReset("uldn_open()")) {
        return;
    }
    if(ldn.isNull()) {
        errln("LocalULocaleDisplayNamesPointer failure");
        return;
    }

    UnicodeString hello=UNICODE_STRING_SIMPLE("Hello {0}!");
    LocalUMessageFormatPointer msg(
        umsg_open(hello.getBuffer(), hello.length(), "root", NULL, errorCode));
    if(errorCode.logIfFailureAndReset("umsg_open()")) {
        return;
    }
    if(msg.isNull()) {
        errln("LocalUMessageFormatPointer failure");
        return;
    }
#endif  /* UCONFIG_NO_FORMATTING  */

#if !UCONFIG_NO_NORMALIZATION
    const UNormalizer2 *nfc=unorm2_getNFCInstance(errorCode);
    UnicodeSet emptySet;
    LocalUNormalizer2Pointer fn2(unorm2_openFiltered(nfc, emptySet.toUSet(), errorCode));
    if(errorCode.logIfFailureAndReset("unorm2_openFiltered()")) {
        return;
    }
    if(fn2.isNull()) {
        errln("LocalUNormalizer2Pointer failure");
        return;
    }
#endif /* !UCONFIG_NO_NORMALIZATION */

#if !UCONFIG_NO_IDNA
    LocalUIDNAPointer idna(uidna_openUTS46(0, errorCode));
    if(errorCode.logIfFailureAndReset("uidna_openUTS46()")) {
        return;
    }
    if(idna.isNull()) {
        errln("LocalUIDNAPointer failure");
        return;
    }
#endif  /* !UCONFIG_NO_IDNA */

#if !UCONFIG_NO_REGULAR_EXPRESSIONS
    UnicodeString pattern=UNICODE_STRING_SIMPLE("abc|xy+z");
    LocalURegularExpressionPointer regex(
        uregex_open(pattern.getBuffer(), pattern.length(), 0, NULL, errorCode));
    if(errorCode.logIfFailureAndReset("uregex_open()")) {
        return;
    }
    if(regex.isNull()) {
        errln("LocalURegularExpressionPointer failure");
        return;
    }
#endif /* UCONFIG_NO_REGULAR_EXPRESSIONS */

#if !UCONFIG_NO_TRANSLITERATION
    UnicodeString id=UNICODE_STRING_SIMPLE("Grek-Latn");
    LocalUTransliteratorPointer trans(
        utrans_openU(id.getBuffer(), id.length(), UTRANS_FORWARD, NULL, 0, NULL, errorCode));
    if(errorCode.logIfFailureAndReset("utrans_open()")) {
        return;
    }
    if(trans.isNull()) {
        errln("LocalUTransliteratorPointer failure");
        return;
    }
#endif /* !UCONFIG_NO_TRANSLITERATION */

    // destructors
}