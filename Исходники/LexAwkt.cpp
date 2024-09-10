// Get digits from input stream.
// This outputs characters to buffer with range checking, but no NULL termination.
// TODO: range checking
wchar_t* GisLexAwkt::getdigits(wchar_t* pstr)
{
    while (iswdigit(m_ch))
    {
        *pstr = m_ch;
        pstr++;
        m_ch = if_getch();
    }
    return pstr;
}