//------------------------------------------------------------------------------
//
//  stripRules    Return a rules string without extra spaces.
//                (Comments are removed separately, during rule parsing.)
//
//------------------------------------------------------------------------------
UnicodeString RBBIRuleScanner::stripRules(const UnicodeString &rules) {
    UnicodeString strippedRules;
    int32_t rulesLength = rules.length();
    bool skippingSpaces = false;

    for (int32_t idx=0; idx<rulesLength; idx = rules.moveIndex32(idx, 1)) {
        UChar32 cp = rules.char32At(idx);
        bool whiteSpace = u_hasBinaryProperty(cp, UCHAR_PATTERN_WHITE_SPACE);
        if (skippingSpaces && whiteSpace) {
            continue;
        }
        strippedRules.append(cp);
        skippingSpaces = whiteSpace;
    }
    return strippedRules;
}