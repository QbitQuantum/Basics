static HRESULT WINAPI IWineD3DClipperImpl_GetClipList(IWineD3DClipper *iface, const RECT *Rect,
        RGNDATA *ClipList, DWORD *Size)
{
    IWineD3DClipperImpl *This = (IWineD3DClipperImpl *)iface;
    TRACE("(%p,%p,%p,%p)\n", This, Rect, ClipList, Size);

    if (This->hWnd)
    {
        HDC hDC = GetDCEx(This->hWnd, NULL, DCX_WINDOW);
        if (hDC)
        {
            HRGN hRgn = CreateRectRgn(0,0,0,0);
            if (GetRandomRgn(hDC, hRgn, SYSRGN))
            {
                if (GetVersion() & 0x80000000)
                {
                    /* map region to screen coordinates */
                    POINT org;
                    GetDCOrgEx( hDC, &org );
                    OffsetRgn( hRgn, org.x, org.y );
                }
                if (Rect)
                {
                    HRGN hRgnClip = CreateRectRgn(Rect->left, Rect->top,
                        Rect->right, Rect->bottom);
                    CombineRgn(hRgn, hRgn, hRgnClip, RGN_AND);
                    DeleteObject(hRgnClip);
                }
                *Size = GetRegionData(hRgn, *Size, ClipList);
            }
            DeleteObject(hRgn);
            ReleaseDC(This->hWnd, hDC);
        }
        return WINED3D_OK;
    }
    else
    {
        static int warned = 0;
        if (warned++ < 10)
            FIXME("(%p,%p,%p,%p),stub!\n",This,Rect,ClipList,Size);
        if (Size) *Size=0;
        return WINEDDERR_NOCLIPLIST;
    }
}