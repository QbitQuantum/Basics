bool CInputField::ValidChar(wchar_t *ch)
{
    if (IsTAB(*ch) || !iswprint(*ch))
        return false;
    
    if ((m_eInputType == INT) || (m_eInputType == FLOAT))
    {
        lconv *lc = localeconv();
        if (strchr(lc->decimal_point, ','))
        {
            if (*ch == L'.')
                *ch = L',';
        }
        
        std::string legal = LegalNrTokens((m_eInputType == FLOAT), m_Text, GetStrPosition());
        char mb[MB_CUR_MAX];
        
        int ret = wctomb(mb, *ch);
        mb[ret] = 0;

        if (legal.find(mb) == std::string::npos)
            return false; // Illegal char
    }
    
    return true;
}