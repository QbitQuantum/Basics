/***********************************************************************
 *      GetThemeSysColorBrush                               (UXTHEME.@)
 */
HBRUSH WINAPI GetThemeSysColorBrush(HTHEME hTheme, int iColorID)
{
    TRACE("(%p, %d)\n", hTheme, iColorID);
    return CreateSolidBrush(GetThemeSysColor(hTheme, iColorID));
}