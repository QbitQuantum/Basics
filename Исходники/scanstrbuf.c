void SB_SkipWhite (StrBuf* B)
/* Skip whitespace in the string buffer */
{
    while (IsBlank (SB_Peek (B))) {
        SB_Skip (B);
    }
}