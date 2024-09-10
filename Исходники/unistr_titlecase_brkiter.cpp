static int32_t U_CALLCONV
unistr_case_internalToTitle(const UCaseMap *csm,
                            UChar *dest, int32_t destCapacity,
                            const UChar *src, int32_t srcLength,
                            UErrorCode *pErrorCode) {
  ubrk_setText(csm->iter, src, srcLength, pErrorCode);
  return ustrcase_internalToTitle(csm, dest, destCapacity, src, srcLength, pErrorCode);
}