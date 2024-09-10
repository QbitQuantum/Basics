bool LayoutRubyRun::canBreakBefore(const LazyLineBreakIterator& iterator) const
{
    // TODO(kojii): It would be nice to improve this so that it isn't just
    // hard-coded, but lookahead in this case is particularly problematic.
    // See crbug.com/522826.

    if (!iterator.priorContextLength())
        return true;
    UChar ch = iterator.lastCharacter();
    ULineBreak lineBreak = static_cast<ULineBreak>(u_getIntPropertyValue(ch, UCHAR_LINE_BREAK));
    // UNICODE LINE BREAKING ALGORITHM
    // http://www.unicode.org/reports/tr14/
    // And Requirements for Japanese Text Layout, 3.1.7 Characters Not Starting a Line
    // http://www.w3.org/TR/2012/NOTE-jlreq-20120403/#characters_not_starting_a_line
    switch (lineBreak) {
    case U_LB_WORD_JOINER:
    case U_LB_GLUE:
    case U_LB_OPEN_PUNCTUATION:
        return false;
    default:
        break;
    }
    return true;
}