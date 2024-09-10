// CImgCtx (Public) -----------------------------------------------------------
void CImgCtx::Tile(
                   HDC hdc,
                   POINT* pptOrg,
                   RECT* prc,
                   SIZE* psizePrint,
                   COLORREF crBack,
                   IMGANIMSTATE* pImgAnimState,
                   DWORD dwFlags)
{
    BOOL fOpaque = !!(GetState() & IMGTRANS_OPAQUE);

    // If the source image is 1x1 just let the normal StretchBlt mechanism
    // fill up the destination.
    if(GetImgInfo()->_xWid==1 && GetImgInfo()->_yHei==1)
    {
        if(crBack != CLR_INVALID)
        {
            PatBltBrush(hdc, prc, PATCOPY, crBack);
        }

        if(pImgAnimState)
        {
            GetImgInfo()->DrawFrame(hdc, pImgAnimState, prc, NULL, NULL, dwFlags);
        }
        else
        {
            GetImgInfo()->DrawImage(hdc, prc, NULL, SRCCOPY, dwFlags);
        }

        goto Cleanup;
    }

    // If the image is opaque and we are writing into an offscreen bitmap
    // which is not clipped, just tile directly into it.
    if(psizePrint==NULL && (fOpaque || crBack!=CLR_INVALID) && GetObjectType(hdc)==OBJ_MEMDC)
    {
        RECT rcBox;
        int iRgn = GetClipBox(hdc, &rcBox);

        if(iRgn==NULLREGION
            || (iRgn==SIMPLEREGION
            && prc->left>=rcBox.left
            && prc->top>=rcBox.top
            && prc->right<=rcBox.right
            && prc->bottom<=rcBox.bottom))
        {
            TileFast(hdc, prc, pptOrg->x, pptOrg->y, fOpaque, crBack, pImgAnimState, dwFlags);
            goto Cleanup;
        }
    }

    // Otherwise just tile the slow way (it may still decide to pretile)
    TileSlow(hdc, prc, pptOrg->x, pptOrg->y, psizePrint, fOpaque, crBack, pImgAnimState, dwFlags);

Cleanup:
    ;
}