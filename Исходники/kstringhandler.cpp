QString KStringHandler::preProcessWrap(const QString &text)
{
    const QChar zwsp(0x200b);

    QString result;
    result.reserve(text.length());

    for (int i = 0; i < text.length(); i++) {
        const QChar c = text[i];
        bool openingParens = (c == QLatin1Char('(') || c == QLatin1Char('{') || c == QLatin1Char('['));
        bool singleQuote = (c == QLatin1Char('\'') );
        bool closingParens = (c == QLatin1Char(')') || c == QLatin1Char('}') || c == QLatin1Char(']'));
        bool breakAfter   = (closingParens || c.isPunct() || c.isSymbol());
        bool nextIsSpace  = (i == (text.length() - 1) || text[i + 1].isSpace());
        bool prevIsSpace  = (i == 0 || text[i - 1].isSpace() || result[result.length() - 1] == zwsp);

        // Provide a breaking opportunity before opening parenthesis
        if (openingParens && !prevIsSpace)
            result += zwsp;
        
        // Provide a word joiner before the single quote
        if (singleQuote && !prevIsSpace)
            result += QChar(0x2060);

        result += c;

        if (breakAfter && !openingParens && !nextIsSpace && !singleQuote) 
            result += zwsp;
    }

    return result;
}