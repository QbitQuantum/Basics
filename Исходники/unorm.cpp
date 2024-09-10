U_CAPI UNormalizationCheckResult U_EXPORT2
unorm_quickCheck(const UChar *src,
                 int32_t srcLength, 
                 UNormalizationMode mode,
                 UErrorCode *pErrorCode) {
    const Normalizer2 *n2=Normalizer2Factory::getInstance(mode, *pErrorCode);
    return unorm2_quickCheck((const UNormalizer2 *)n2, src, srcLength, pErrorCode);
}