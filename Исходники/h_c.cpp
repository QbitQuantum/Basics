int LookAt(EBuffer *B, int Row, unsigned int Pos, const char *What, hsState State, int NoWord, int CaseInsensitive) {
    STARTFUNC("LookAt{h_c.cpp}");

    int Len = strlen(What);

    if (Row < 0 || Row >= B->RCount) {
        LOG << "Row out of range: " << Row << " vs " << B->RCount << ENDLINE;
        ENDFUNCRC(0);
    }
    char*        pLine       = B->RLine(Row)->Chars;
    unsigned int uLineLength = B->RLine(Row)->Count;
    Pos = B->CharOffset(B->RLine(Row), Pos);
    if (Pos + strlen(What) > uLineLength) { ENDFUNCRC(0); }
    if (NoWord && uLineLength > Pos + Len && ISNAME(pLine[Pos + Len]))
    {
        ENDFUNCRC(0);
    }
    LOG << "Check against [" << What << ']' << ENDLINE;
    if (
        (CaseInsensitive && memicmp(pLine + Pos, What, Len) == 0) ||
        (!CaseInsensitive && memcmp(pLine + Pos, What, Len) == 0)
       )
    {
        ENDFUNCRC(1);
    }
    else
    {
        ENDFUNCRC(0);
    }
}