/***********************************************************************
 *           IsCharLower    (USER.436)
 *           IsCharLowerA   (USER32.@)
 */
BOOL WINAPI IsCharLowerA(CHAR x)
{
    WCHAR wch;
    MultiByteToWideChar(CP_ACP, 0, &x, 1, &wch, 1);
    return IsCharLowerW(wch);
}