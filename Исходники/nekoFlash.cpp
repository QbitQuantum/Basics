void nekoFlashInstance::Update(float32 frameTime)
{
    if(!flashInterface)
    {
        SetValid(false);
        return;
    }

    if(!mTexture)
        return;

    if(mSkipAbleTime > 0.0f)
    {
        mSkipAbleTime = max(mSkipAbleTime - frameTime, 0);
    }

    int32 dirtyWidth = mDirtyBounds.right - mDirtyBounds.left;
    int32 dirtyHeight = mDirtyBounds.bottom - mDirtyBounds.top;
    int32 dirtyBufSize = dirtyWidth * dirtyHeight;

    flashInterface->QueryInterface(IID_IViewObject, (void**)&mCurView);
    if(!mCurView || !dirtyBufSize)
        return;

    IDirect3DSurface9 *pSurface;
    D3DLOCKED_RECT lockedRect;

    if(mTexture->GetHandle() == NULL)
        return;

    if(SUCCEEDED(mTexture->GetHandle()->LockRect(0, &lockedRect, 0, D3DLOCK_DISCARD|D3DLOCK_NOOVERWRITE)))
    {
        lockedRect.Pitch /= 4;

        if(mMainBitmap == NULL)
        {
            HDC hdc = GetDC(0);
            BITMAPINFOHEADER bih = {0};
            bih.biSize = sizeof(BITMAPINFOHEADER);
            bih.biBitCount = 32;
            bih.biCompression = BI_RGB;
            bih.biPlanes = 1;
            bih.biWidth = 800;
            bih.biHeight = -600;
            mMainDC = CreateCompatibleDC(hdc);
            mMainBitmap = CreateDIBSection(hdc, (BITMAPINFO*)&bih, DIB_RGB_COLORS, (void**)&mMainBuffer, 0, 0);
            SelectObject(mMainDC, mMainBitmap);

            mAlphaDC = CreateCompatibleDC(hdc);
            mAlphaBitmap = CreateDIBSection(hdc, (BITMAPINFO*)&bih, DIB_RGB_COLORS, (void**)&mAlphaBuffer, 0, 0);
            SelectObject(mAlphaDC, mAlphaBitmap);
        }

        RECT local = {-mDirtyBounds.left, -mDirtyBounds.top,
                      -mDirtyBounds.left + mDirtyBounds.right, -mDirtyBounds.top + mDirtyBounds.bottom
                     };

        //memset(mMainBuffer, 0, dirtyBufSize * 4);
        //memset(mAlphaBuffer, 255, dirtyBufSize * 4);

        OleDraw(mCurView, DVASPECT_TRANSPARENT, mMainDC, &local);
        OleDraw(mCurView, DVASPECT_TRANSPARENT, mAlphaDC, &local);

        DWORD *blackBuffer, *whiteBuffer;
        DWORD *ptr;

        int32 ay = mDirtyBounds.top;
        int32 x, y;

        for(y = 0; y < dirtyHeight; ++y, ++ay)
        {
            blackBuffer = (mMainBuffer + y * 800);
            whiteBuffer = (mAlphaBuffer + y * 800);
            ptr = (DWORD *)lockedRect.pBits + ay * lockedRect.Pitch + mDirtyBounds.left;

            for(x = 0; x < dirtyWidth; ++x)
            {
                //blackBuffer[3] = 255 - (*blackBuffer - *whiteBuffer);
                *ptr++ = ((*blackBuffer) & 0xffffff) | ((255 - (((*blackBuffer++) & 0xff) - ((*whiteBuffer++) & 0xff))) << 24);
            }
        }

        mTexture->GetHandle()->UnlockRect(0);

        mDirtyBounds.left = mDirtyBounds.right = 400;
        mDirtyBounds.top = mDirtyBounds.bottom = 400;
    }

    mCurView->Release();
    mCurView = 0;
}