// This is only needed for TextDocuments where we might have text nodes
// approaching the default length limit (~64k) and we don't want to
// break a text node in the middle of a combining character.
static unsigned findBreakIndexBetween(const StringBuilder& string, unsigned currentPosition, unsigned proposedBreakIndex)
{
    ASSERT(currentPosition < proposedBreakIndex);
    ASSERT(proposedBreakIndex <= string.length());
    // The end of the string is always a valid break.
    if (proposedBreakIndex == string.length())
        return proposedBreakIndex;

    // Latin-1 does not have breakable boundaries. If we ever moved to a differnet 8-bit encoding this could be wrong.
    if (string.is8Bit())
        return proposedBreakIndex;

    const UChar* breakSearchCharacters = string.characters16() + currentPosition;
    // We need at least two characters look-ahead to account for UTF-16 surrogates, but can't search off the end of the buffer!
    unsigned breakSearchLength = std::min(proposedBreakIndex - currentPosition + 2, string.length() - currentPosition);
    NonSharedCharacterBreakIterator it(breakSearchCharacters, breakSearchLength);

    if (it.isBreak(proposedBreakIndex - currentPosition))
        return proposedBreakIndex;

    int adjustedBreakIndexInSubstring = it.preceding(proposedBreakIndex - currentPosition);
    if (adjustedBreakIndexInSubstring > 0)
        return currentPosition + adjustedBreakIndexInSubstring;
    // We failed to find a breakable point, let the caller figure out what to do.
    return 0;
}