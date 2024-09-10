bool Compiler::QuickFileParser::parseSpecial (int code, const TokenLoc& loc, Scanner& scanner)
{
    if (code!=Scanner::S_newline)
    {
        SkipParser skip (getErrorHandler(), getContext());
        scanner.scan (skip);
    }

    return true;
}