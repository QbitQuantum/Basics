HFONT   CreFntFix (HDC hDC, WORD usPntSiz, RECT rCltRec)
{

    WORD    usWrkSiz;
    WORD    usLogExt;
    WORD    usDevExt;
    HFONT   hFixFnt;

    /********************************************************************/
    /********************************************************************/
    if (0 == (usDevExt = rCltRec.bottom)) return (NULL); 
    DPtoLP (hDC, (LPPOINT) &rCltRec, 2);
    usLogExt = abs (rCltRec.top - rCltRec.bottom);

    /********************************************************************/
    /* Point size in logical points:                                    */
    /*   = (PntSiz * DevPnt/inch * 1/72 in/pt) * LogPnt/DevPnt          */
    /********************************************************************/
    usWrkSiz = (WORD) (((DWORD) usPntSiz * (DWORD) GetDeviceCaps (hDC, LOGPIXELSY)
        * (DWORD) usLogExt) / (72L * (DWORD) usDevExt));

    /********************************************************************/
    /* Create font using size without descent                           */
    /********************************************************************/
    hFixFnt = CreateFont (- (short) usWrkSiz, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, FF_MODERN,
        (LPSTR) FNTFIXNAM);

    return (hFixFnt);

}