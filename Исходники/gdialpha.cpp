BOOL CGdiAlpha::AlphaBackup(HDC hdc,LPCRECT pRect,ALPHAINFO &alphaInfo)
{
    HBITMAP hBmp=(HBITMAP)GetCurrentObject(hdc,OBJ_BITMAP);
    DUIASSERT(hBmp);
    BITMAP  bm;
    GetObject(hBmp,sizeof(BITMAP),&bm);

    if(bm.bmBitsPixel!=32) return FALSE;
    alphaInfo.rc=*pRect;
    POINT pt;
    GetViewportOrgEx(hdc,&pt);
    RECT rcImg= {0,0,bm.bmWidth,bm.bmHeight};
    OffsetRect(&alphaInfo.rc,pt.x,pt.y);
    IntersectRect(&alphaInfo.rc,&alphaInfo.rc,&rcImg);
    alphaInfo.lpBuf=ALPHABACKUP(&bm,alphaInfo.rc.left,alphaInfo.rc.top,alphaInfo.rc.right - alphaInfo.rc.left, alphaInfo.rc.bottom - alphaInfo.rc.top);
    return TRUE;
}