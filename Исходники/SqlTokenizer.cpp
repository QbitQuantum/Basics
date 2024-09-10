//-----------------------------------------------------------------------------
bool SqlTokenizer::nextToken()
{
    sqlTokenStartM = sqlTokenEndM;
    if (sqlTokenEndM == 0 || *sqlTokenEndM == 0)
    {
        sqlTokenTypeM = tkEOF;
        return false;
    }
    // use QChar* member to scan
    QChar c = *sqlTokenEndM;
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        keywordIdentifierToken();
    else if (c == '"')
        quotedIdentifierToken();
    else if (c == '\'')
        stringToken();
    else if (c == '(')
        symbolToken(tkPARENOPEN);
    else if (c == ')')
        symbolToken(tkPARENCLOSE);
    else if (c == '=')
        symbolToken(tkEQUALS);
    else if (c == ',')
        symbolToken(tkCOMMA);
    else if (c == '/' && *(sqlTokenEndM + 1) == '*')
        multilineCommentToken();
    else if (c == '-' && *(sqlTokenEndM + 1) == '-')
        singleLineCommentToken();
    else if (c.isSpace())
        whitespaceToken();
    else
        defaultToken();
    return true;
}