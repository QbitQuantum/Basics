void DrawIconExAlpha(HDC hdc, int xLeft, int yTop, HICON hIcon, int cxWidth, int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags, bool bIsSmiley)
{
    bool restore = false;

    if (skin.bNeedLayerUpdate && !bIsSmiley) {
        ICONINFO icon;
        if ( GetIconInfo(hIcon, &icon)) {
            if ( !IsAlphaTransparent(icon.hbmColor)) {
                RECT rc;
                SetRect(&rc, xLeft, yTop, xLeft + cxWidth, yTop + cyWidth);
                SaveAlpha(&rc);
                restore = true;
            }

            DeleteObject(icon.hbmColor);
            DeleteObject(icon.hbmMask);
        }
    }

    DrawIconEx(hdc, xLeft, yTop, hIcon, cxWidth, cyWidth, istepIfAniCur, hbrFlickerFreeDraw, diFlags);

    if (skin.bNeedLayerUpdate && restore) {
        RECT rc;
        SetRect(&rc, xLeft, yTop, xLeft + cxWidth, yTop + cyWidth);
        RestoreAlpha(&rc);
    }
}