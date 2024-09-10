BOOL
GetOpenStatusByCodepage(
    HIMC hIMC,
    PCONSOLE_TABLE ConTbl
)
{
    switch ( HKL_TO_LANGID(ConTbl->hklActive))
    {
    case    LANG_ID_JAPAN:
        return ImmGetOpenStatus(hIMC);
        break;
    case    LANG_ID_TAIWAN:
    case    LANG_ID_PRC:
    case    LANG_ID_KOREA:
        if (ImmGetOpenStatus(hIMC)) {
            return ImmIsIME(ConTbl->hklActive);
        }
        break;
    default:
        return FALSE;
    }
    return FALSE;
}