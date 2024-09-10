U_DRAFT int32_t U_EXPORT2
udatpg_getBestPattern(UDateTimePatternGenerator *dtpg,
                      const UChar *skeleton, int32_t length,
                      UChar *bestPattern, int32_t capacity,
                      UErrorCode *pErrorCode) {
    return udatpg_getBestPatternWithOptions(dtpg, skeleton, length,
                                            UDATPG_MATCH_NO_OPTIONS,
                                            bestPattern, capacity, pErrorCode);
}