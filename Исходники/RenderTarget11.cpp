RenderTarget11::RenderTarget11(Renderer *renderer, GLsizei width, GLsizei height, GLenum format, GLsizei samples, bool depth)
{
    mRenderer = Renderer11::makeRenderer11(renderer);
    mTexture = NULL;
    mRenderTarget = NULL;
    mDepthStencil = NULL;
    mShaderResource = NULL;

    DXGI_FORMAT requestedFormat = gl_d3d11::ConvertRenderbufferFormat(format);

    int supportedSamples = mRenderer->getNearestSupportedSamples(requestedFormat, samples);
    if (supportedSamples < 0)
    {
        gl::error(GL_OUT_OF_MEMORY);
        return;
    }

    if (width > 0 && height > 0)
    {
        // Create texture resource
        D3D11_TEXTURE2D_DESC desc;
        desc.Width = width; 
        desc.Height = height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = requestedFormat;
        desc.SampleDesc.Count = (supportedSamples == 0) ? 1 : supportedSamples;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.BindFlags = (depth ? D3D11_BIND_DEPTH_STENCIL : (D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE));

        ID3D11Device *device = mRenderer->getDevice();
        HRESULT result = device->CreateTexture2D(&desc, NULL, &mTexture);

        if (result == E_OUTOFMEMORY)
        {
            gl::error(GL_OUT_OF_MEMORY);
            return;
        }
        ASSERT(SUCCEEDED(result));

        if (depth)
        {
            D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
            dsvDesc.Format = requestedFormat;
            dsvDesc.ViewDimension = (supportedSamples == 0) ? D3D11_DSV_DIMENSION_TEXTURE2D : D3D11_DSV_DIMENSION_TEXTURE2DMS;
            dsvDesc.Texture2D.MipSlice = 0;
            dsvDesc.Flags = 0;
            result = device->CreateDepthStencilView(mTexture, &dsvDesc, &mDepthStencil);

            if (result == E_OUTOFMEMORY)
            {
                mTexture->Release();
                mTexture = NULL;
                gl::error(GL_OUT_OF_MEMORY);
            }
            ASSERT(SUCCEEDED(result));
        }
        else
        {
            D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
            rtvDesc.Format = requestedFormat;
            rtvDesc.ViewDimension = (supportedSamples == 0) ? D3D11_RTV_DIMENSION_TEXTURE2D : D3D11_RTV_DIMENSION_TEXTURE2DMS;
            rtvDesc.Texture2D.MipSlice = 0;
            result = device->CreateRenderTargetView(mTexture, &rtvDesc, &mRenderTarget);

            if (result == E_OUTOFMEMORY)
            {
                mTexture->Release();
                mTexture = NULL;
                gl::error(GL_OUT_OF_MEMORY);
                return;
            }
            ASSERT(SUCCEEDED(result));

            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
            srvDesc.Format = requestedFormat;
            srvDesc.ViewDimension = (supportedSamples == 0) ? D3D11_SRV_DIMENSION_TEXTURE2D : D3D11_SRV_DIMENSION_TEXTURE2DMS;
            srvDesc.Texture2D.MostDetailedMip = 0;
            srvDesc.Texture2D.MipLevels = 1;
            result = device->CreateShaderResourceView(mTexture, &srvDesc, &mShaderResource);

            if (result == E_OUTOFMEMORY)
            {
                mTexture->Release();
                mTexture = NULL;
                mRenderTarget->Release();
                mRenderTarget = NULL;
                gl::error(GL_OUT_OF_MEMORY);
                return;
            }
            ASSERT(SUCCEEDED(result));
        }
    }

    mWidth = width;
    mHeight = height;
    mInternalFormat = format;
    mSamples = supportedSamples;
    mActualFormat = d3d11_gl::ConvertTextureInternalFormat(requestedFormat);
    mSubresourceIndex = D3D11CalcSubresource(0, 0, 1);
}