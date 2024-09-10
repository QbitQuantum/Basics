BOOL RichEditBkImg::StrPos2ItemPos(const SStringW &strPos, POSITION_ITEM & pos)
{
    if(strPos.IsEmpty()) return FALSE;

    LPCWSTR pszPos = strPos;
    switch(pszPos[0])
    {
    //case POSFLAG_REFCENTER: pos.pit=PIT_CENTER,pszPos++;break;
    //case POSFLAG_PERCENT: pos.pit=PIT_PERCENT,pszPos++;break;
    case POSFLAG_REFPREV_NEAR: pos.pit=PIT_PREV_NEAR,pszPos++;break;
    case POSFLAG_REFNEXT_NEAR: pos.pit=PIT_NEXT_NEAR,pszPos++;break;
    case POSFLAG_REFPREV_FAR: pos.pit=PIT_PREV_FAR,pszPos++;break;
    case POSFLAG_REFNEXT_FAR: pos.pit=PIT_NEXT_FAR,pszPos++;break;
    case POSFLAG_SIZE:pos.pit=PIT_SIZE,pszPos++;break;
    default: pos.pit=PIT_NORMAL;break;
    }

    pos.nRefID = -1;//not ref sibling using id
    if(pszPos [0] == L'-')
    {
        pos.cMinus = -1;
        pszPos ++;
    }else
    {
        pos.cMinus = 1;
    }
    pos.nPos=(float)_wtof(pszPos);

    return TRUE;
}