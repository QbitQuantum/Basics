int32_t SpoofImpl::findHiddenOverlay(const UnicodeString& input, UErrorCode&) const {
    bool sawLeadCharacter = false;
    for (int32_t i=0; i<input.length();) {
        UChar32 cp = input.char32At(i);
        if (sawLeadCharacter && cp == 0x0307) {
            return i;
        }
        uint8_t combiningClass = u_getCombiningClass(cp);
        // Skip over characters except for those with combining class 0 (non-combining characters) or with
        // combining class 230 (same class as U+0307)
        U_ASSERT(u_getCombiningClass(0x0307) == 230);
        if (combiningClass == 0 || combiningClass == 230) {
            sawLeadCharacter = isIllegalCombiningDotLeadCharacter(cp);
        }
        i += U16_LENGTH(cp);
    }
    return -1;
}