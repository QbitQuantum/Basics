HRESULT dxReadPixels(IDirect3DDevice9* Device, void* Buffer, bool& Minimised, int& Width, int& Height, D3DFORMAT Format)
{
    IDirect3DSurface9* RenderTarget = nullptr;
    IDirect3DSurface9* DestTarget = nullptr;
    HRESULT result = Device->GetRenderTarget(0, &RenderTarget);

    if (result == S_OK)
    {
        if (Width == 0 || Height == 0 || Format == D3DFMT_UNKNOWN)
        {
            D3DSURFACE_DESC descriptor = {};
            RenderTarget->GetDesc(&descriptor);
            Width = descriptor.Width;
            Height = descriptor.Height;
            Format = descriptor.Format;
        }

        HDC DC = nullptr;
        RenderTarget->GetDC(&DC);
        Minimised = IsIconic(WindowFromDC(DC));
        RenderTarget->ReleaseDC(DC);
        result = Device->CreateOffscreenPlainSurface(Width, Height, Format, D3DPOOL_SYSTEMMEM, &DestTarget, nullptr);
        result = Device->GetRenderTargetData(RenderTarget, DestTarget);

        D3DLOCKED_RECT rect;
        DestTarget->LockRect(&rect, 0, D3DLOCK_READONLY);
        memcpy(Buffer, rect.pBits, Width * Height * 4);
        DestTarget->UnlockRect();
    }

    SafeRelease(RenderTarget);
    SafeRelease(DestTarget);
    return result;
}