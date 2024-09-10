bool isGraphemeBreak(UChar32 prevCodePoint, UChar32 nextCodePoint)
{
    // The following breaking rules come from Unicode Standard Annex #29 on
    // Unicode Text Segmaentation. See http://www.unicode.org/reports/tr29/
    // Note that some of rules are in proposal.
    // Also see http://www.unicode.org/reports/tr29/proposed.html
    int prevProp =
        u_getIntPropertyValue(prevCodePoint, UCHAR_GRAPHEME_CLUSTER_BREAK);
    int nextProp =
        u_getIntPropertyValue(nextCodePoint, UCHAR_GRAPHEME_CLUSTER_BREAK);

    // Rule1 GB1 sot ÷
    // Rule2 GB2 ÷ eot
    // Should be handled by caller.

    // Rule GB3, CR x LF
    if (prevProp == U_GCB_CR && nextProp == U_GCB_LF)
        return false;

    // Rule GB4, (Control | CR | LF) ÷
    if (prevProp == U_GCB_CONTROL || prevProp == U_GCB_CR
        || prevProp == U_GCB_LF)
        return true;

    // Rule GB5, ÷ (Control | CR | LF)
    if (nextProp == U_GCB_CONTROL || nextProp == U_GCB_CR
        || nextProp == U_GCB_LF)
        return true;

    // Rule GB6, L x (L | V | LV | LVT)
    if (prevProp == U_GCB_L
        && (nextProp == U_GCB_L || nextProp == U_GCB_V || nextProp == U_GCB_LV
            || nextProp == U_GCB_LVT))
        return false;

    // Rule GB7, (LV | V) x (V | T)
    if ((prevProp == U_GCB_LV || prevProp == U_GCB_V)
        && (nextProp == U_GCB_V || nextProp == U_GCB_T))
        return false;

    // Rule GB8, (LVT | T) x T
    if ((prevProp == U_GCB_LVT || prevProp == U_GCB_T) && nextProp == U_GCB_T)
        return false;

    // Rule GB8a
    //
    // sot   (RI RI)* RI x RI
    // [^RI] (RI RI)* RI x RI
    //                RI ÷ RI
    if (Character::isRegionalIndicator(prevCodePoint)
        && Character::isRegionalIndicator(nextCodePoint))
        NOTREACHED() << "Do not use this function for regional indicators.";

    // Rule GB9, x (Extend | ZWJ)
    // Rule GB9a, x SpacingMark
    if (nextProp == U_GCB_EXTEND || nextCodePoint == zeroWidthJoinerCharacter
        || nextProp == U_GCB_SPACING_MARK)
        return false;

    // Rule GB9b, Prepend x
    if (prevProp == U_GCB_PREPEND)
        return false;

    // Cluster Indic syllables together.
    if (isIndicSyllabicCategoryVirama(prevCodePoint)
        && u_getIntPropertyValue(nextCodePoint,
            UCHAR_GENERAL_CATEGORY) == U_OTHER_LETTER)
        return false;

    // Proposed Rule GB10, (E_Base | EBG) x E_Modifier
    if ((Character::isEmojiModifierBase(prevCodePoint)
        || isEBaseGAZ(prevCodePoint))
        && Character::isModifier(nextCodePoint))
        return false;

    // Proposed Rule GB11, ZWJ x Emoji
    if (prevCodePoint == zeroWidthJoinerCharacter
        && (Character::isEmoji(nextCodePoint)))
        return false;

    // Rule GB999 any ÷ any
    return true;
}