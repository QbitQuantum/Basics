static BOOL 
CaptureTextOut(HDC hdc, int nXStart, int nYStart, LPCSTR lpszString, int cbString, BOOL bWChr)
{
    SIZE  tSize;
    POINT ptTextPos;
    RECT  Rect;
    BOOL  bInsideRect = FALSE;
    POINT pMouse = g_pMouse;
    
    GetTextExtentPoint32X(hdc, lpszString, cbString, &tSize, bWChr);

    ptTextPos.x = nXStart;
    ptTextPos.y = nYStart;
    LPtoDP(hdc, &ptTextPos, 1);

    Rect.left = ptTextPos.x;
    Rect.right = ptTextPos.x + tSize.cx;
    Rect.top = ptTextPos.y;
    Rect.bottom = ptTextPos.y + tSize.cy;
     /*	
      * On some situation, RECT will be [0,4,-100,-83] or [36,114,-9,8],
      * while mouse point be [47, 100]. It seems 'ptTexPos.y' being wrong.
      */
#if 0
    DWORD  ret;
    SendMessageTimeoutA(g_hHookServer, WM_CW_DEBUG, -1, cbString, SMTO_ABORTIFHUNG, 50, &ret);
    SendMessageTimeoutA(g_hHookServer, WM_CW_DEBUG, Rect.left, Rect.right, SMTO_ABORTIFHUNG, 50, &ret);
    SendMessageTimeoutA(g_hHookServer, WM_CW_DEBUG, Rect.top,  Rect.bottom, SMTO_ABORTIFHUNG, 50, &ret);
#endif
    
    if (Rect.top < 0) {
        if (Rect.left <= pMouse.x && Rect.right >= pMouse.x)
            bInsideRect = TRUE;
    } else {
        if (PtInRect(&Rect, pMouse)) 
            bInsideRect = TRUE;
    }

    if (bInsideRect) {
        int pos;
        SIZE  iterSize;
        pos =(int)((pMouse.x - Rect.left) * cbString /((float)tSize.cx)+0.5);   
        GetTextExtentPoint32X(hdc, lpszString, pos+1, &iterSize, bWChr);
        if(iterSize.cx < pMouse.x - ptTextPos.x) {
            do {
                pos++;
                GetTextExtentPoint32X(hdc, lpszString, pos+1, &iterSize, bWChr);
            }while((iterSize.cx < pMouse.x - ptTextPos.x) && (pos < cbString-1));
        } else if (iterSize.cx > pMouse.x - ptTextPos.x) {
            do {
                pos--;
                GetTextExtentPoint32X(hdc, lpszString, pos+1, &iterSize, bWChr);
            }while((iterSize.cx > pMouse.x - ptTextPos.x) && (pos > 0));
        }
        g_tPos = pos;
        int size = cbString;
        if (bWChr)
            size = size * sizeof(WCHAR);

        size =  size > 253 ?  253 : size;  // ending with '/0'
        CopyMemory(g_strbuf, lpszString, size);
        g_strbuf[size] = '\0';
        g_strbuf[size+1] = '\0';
        return TRUE;
    }
    return FALSE;
}