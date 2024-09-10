void Texture::SaveToSystemMemory()
{
    if (isRenderTarget)
    {
        /*
            Do not save texture if autosave flag is false
         */
        if (!renderTargetAutosave)
            return;

        HRESULT hr = RenderManager::Instance()->GetD3DDevice()->TestCooperativeLevel();
        if (hr == D3DERR_DEVICELOST)
        {
            //if (!saveTexture)
            //Logger::FrameworkDebug("Trying to save to system memory rendertarget that was not saved before");
            return;
        }

        //	Render manager set this flag  when you set sprite as render target.
        if (!renderTargetModified)
            return;
        // Release should be after check that renderTargetModified.
        D3DSafeRelease(saveTexture);

        LPDIRECT3DDEVICE9 device = RenderManager::Instance()->GetD3DDevice();

        D3DSURFACE_DESC desc;
        id->GetLevelDesc(0, &desc);
        //Logger::FrameworkDebug("Saving render target to system memory: %s size: %d x %d format:%d", relativePathname.c_str(), width, height, desc.Format);
        /*
        HRESULT hr = device->CreateOffscreenPlainSurface(width, height, desc.Format, D3DPOOL_SYSTEMMEM, &saveSurface, NULL);
        DX_VERIFY(hr);
        */

        hr = device->CreateTexture(width, height,
                                   1/*means we create texture with 1 mipmap level*/,
                                   0,  desc.Format, D3DPOOL_SYSTEMMEM, &saveTexture, 0);
        RENDER_VERIFY(hr);

        LPDIRECT3DSURFACE9 renderTargetMainSurface;
        hr = id->GetSurfaceLevel(0, &renderTargetMainSurface);
        RENDER_VERIFY(hr);

        LPDIRECT3DSURFACE9 saveTextureMainSurface;
        hr = saveTexture->GetSurfaceLevel(0, &saveTextureMainSurface);
        RENDER_VERIFY(hr);

        hr = device->GetRenderTargetData(renderTargetMainSurface, saveTextureMainSurface);
        RENDER_VERIFY(hr);

        renderTargetModified = false;

#if 0
        //Image * image = new Image();
        Image * image = image->Create(width, height, FORMAT_RGBA8888);
        D3DLOCKED_RECT rect;
        hr = saveTexture->LockRect(0, &rect, 0, 0);
        if (FAILED(hr))
        {
            Logger::Error("[TextureDX9] Could not lock DirectX9 Texture.");
            return;
        }
        int32 pixelSizeInBits = GetPixelFormatSize(format);
        if (format ==  FORMAT_RGBA8888)
        {
            //int32 pitchInBytes =

            uint8 * destBits = (uint8*)image->GetData();
            uint8 * sourceBits = (uint8*)rect.pBits;
            for (uint32 h = 0; h < height * width; ++h)
            {
                uint32 b = sourceBits[0];
                uint32 g = sourceBits[1];
                uint32 r = sourceBits[2];
                uint32 a = sourceBits[3];

                destBits[0] = (uint8)r; //sourceBits[3];
                destBits[1] = (uint8)g; //sourceBits[0];
                destBits[2] = (uint8)b;//sourceBits[1];
                destBits[3] = (uint8)a;

                destBits += 4;
                sourceBits += 4;
            }
        }

        saveTexture->UnlockRect(0);
        image->Save(Format("FBO\\%s.png", relativePathname.c_str()));

        SafeRelease(image);
#endif



        D3DSafeRelease(renderTargetMainSurface);
        D3DSafeRelease(saveTextureMainSurface);
    }
}