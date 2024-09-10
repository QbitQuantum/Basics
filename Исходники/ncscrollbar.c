static void SCROLL_ThemeDrawPart(PDRAW_CONTEXT pcontext, int iPartId,int iStateId,  SCROLLBARINFO* psbi, int htCurrent, int htDown, int htHot, RECT* r)
{
    if(psbi->rgstate[htCurrent] & STATE_SYSTEM_UNAVAILABLE)
        iStateId += BUTTON_DISABLED - BUTTON_NORMAL;
    else if (htHot == htCurrent)
        iStateId += BUTTON_HOT - BUTTON_NORMAL;
    else if (htDown == htCurrent)
        iStateId += BUTTON_PRESSED - BUTTON_NORMAL;

    DrawThemeBackground(pcontext->scrolltheme, pcontext->hDC, iPartId, iStateId, r, NULL);
}