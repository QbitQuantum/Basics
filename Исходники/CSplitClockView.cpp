Int32 CSplitClockView::GetAmPmPartEndIndex(
    /* [in] */ const String& formatString)
{
    Boolean hasAmPm = FALSE;
    Int32 length = formatString.GetLength();
    for (Int32 i = length - 1; i >= 0; i--) {
        Char32 c = formatString.GetChar(i);
        Boolean isAmPm = c == 'a';
        Boolean isWhitespace = Character::IsWhitespace(c);
        if (isAmPm) {
            hasAmPm = TRUE;
        }
        if (isAmPm || isWhitespace) {
            continue;
        }
        if (i == length - 1) {

            // First character was not AM/PM and not whitespace, so it's not ending with AM/PM.
            return -1;
        } else {

            // If we have AM/PM at all, return last index, or -1 to indicate that it's not
            // ending with AM/PM.
            return hasAmPm ? i + 1 : -1;
        }
    }

    // Only AM/PM and whitespaces? The whole string is AM/PM. Else: Only whitespaces in the
    // string.
    return hasAmPm ? 0 : -1;
}