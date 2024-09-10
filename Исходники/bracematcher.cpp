bool BraceMatcher::shouldInsertMatchingText(const QChar lookAhead) const
{
    return lookAhead.isSpace()
        || isQuote(lookAhead)
        || isDelimiter(lookAhead)
        || isClosingBrace(lookAhead);
}