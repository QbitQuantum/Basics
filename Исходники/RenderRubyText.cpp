bool RenderRubyText::canBreakBefore(const LazyLineBreakIterator& iterator) const
{
    // FIXME: It would be nice to improve this so that it isn't just hard-coded, but lookahead in this
    // case is particularly problematic.

    if (!iterator.priorContextLength())
        return true;
    UChar ch = iterator.lastCharacter();
    ULineBreak lineBreak = (ULineBreak)u_getIntPropertyValue(ch, UCHAR_LINE_BREAK);
    // UNICODE LINE BREAKING ALGORITHM
    // http://www.unicode.org/reports/tr14/
    // And Requirements for Japanese Text Layout, 3.1.7 Characters Not Starting a Line
    // http://www.w3.org/TR/2012/NOTE-jlreq-20120403/#characters_not_starting_a_line
    switch (lineBreak) {
    case U_LB_NONSTARTER:
    case U_LB_CLOSE_PARENTHESIS:
    case U_LB_CLOSE_PUNCTUATION:
    case U_LB_EXCLAMATION:
    case U_LB_BREAK_SYMBOLS:
    case U_LB_INFIX_NUMERIC:
    case U_LB_ZWSPACE:
    case U_LB_WORD_JOINER:
        return false;
    default:
        break;
    }
    // Special care for Requirements for Japanese Text Layout
    switch (ch) {
    case 0x2019: // RIGHT SINGLE QUOTATION MARK
    case 0x201D: // RIGHT DOUBLE QUOTATION MARK
    case 0x00BB: // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
    case 0x2010: // HYPHEN
    case 0x2013: // EN DASH
    case 0x300C: // LEFT CORNER BRACKET
        return false;
    default:
        break;
    }
    return true;
}