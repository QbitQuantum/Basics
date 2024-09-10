bool ScriptParser::parseSpecial (int code, const TokenLoc& loc, Scanner& scanner)
{
    if (code==Scanner::S_newline) // empty line
        return true;

    if (code==Scanner::S_open) /// \todo Option to switch this off
    {
        scanner.putbackSpecial (code, loc);
        return parseKeyword (Scanner::K_if, loc, scanner);
    }

    mLineParser.reset();
    if (mLineParser.parseSpecial (code, loc, scanner))
        scanner.scan (mLineParser);

    return true;
}