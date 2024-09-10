gl::Error Image11::createStagingTexture()
{
    if (mStagingTexture)
    {
        return gl::Error(GL_NO_ERROR);
    }

    ASSERT(mWidth > 0 && mHeight > 0 && mDepth > 0);

    const DXGI_FORMAT dxgiFormat = getDXGIFormat();

    ID3D11Device *device = mRenderer->getDevice();
    HRESULT result;

    int lodOffset = 1;
    GLsizei width = mWidth;
    GLsizei height = mHeight;

    // adjust size if needed for compressed textures
    d3d11::MakeValidSize(false, dxgiFormat, &width, &height, &lodOffset);

    if (mTarget == GL_TEXTURE_3D)
    {
        ID3D11Texture3D *newTexture = NULL;

        D3D11_TEXTURE3D_DESC desc;
        desc.Width = width;
        desc.Height = height;
        desc.Depth = mDepth;
        desc.MipLevels = lodOffset + 1;
        desc.Format = dxgiFormat;
        desc.Usage = D3D11_USAGE_STAGING;
        desc.BindFlags = 0;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;

        if (d3d11::GetTextureFormatInfo(mInternalFormat).dataInitializerFunction != NULL)
        {
            std::vector<D3D11_SUBRESOURCE_DATA> initialData;
            std::vector< std::vector<BYTE> > textureData;
            d3d11::GenerateInitialTextureData(mInternalFormat, width, height, mDepth,
                                              lodOffset + 1, &initialData, &textureData);

            result = device->CreateTexture3D(&desc, initialData.data(), &newTexture);
        }
        else
        {
            result = device->CreateTexture3D(&desc, NULL, &newTexture);
        }

        if (FAILED(result))
        {
            ASSERT(result == E_OUTOFMEMORY);
            return gl::Error(GL_OUT_OF_MEMORY, "Failed to create staging texture, result: 0x%X.", result);
        }

        mStagingTexture = newTexture;
        mStagingSubresource = D3D11CalcSubresource(lodOffset, 0, lodOffset + 1);
    }
    else if (mTarget == GL_TEXTURE_2D || mTarget == GL_TEXTURE_2D_ARRAY || mTarget == GL_TEXTURE_CUBE_MAP)
    {
        ID3D11Texture2D *newTexture = NULL;

        D3D11_TEXTURE2D_DESC desc;
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = lodOffset + 1;
        desc.ArraySize = 1;
        desc.Format = dxgiFormat;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_STAGING;
        desc.BindFlags = 0;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;

        if (d3d11::GetTextureFormatInfo(mInternalFormat).dataInitializerFunction != NULL)
        {
            std::vector<D3D11_SUBRESOURCE_DATA> initialData;
            std::vector< std::vector<BYTE> > textureData;
            d3d11::GenerateInitialTextureData(mInternalFormat, width, height, 1,
                                              lodOffset + 1, &initialData, &textureData);

            result = device->CreateTexture2D(&desc, initialData.data(), &newTexture);
        }
        else
        {
            result = device->CreateTexture2D(&desc, NULL, &newTexture);
        }

        if (FAILED(result))
        {
            ASSERT(result == E_OUTOFMEMORY);
            return gl::Error(GL_OUT_OF_MEMORY, "Failed to create staging texture, result: 0x%X.", result);
        }

        mStagingTexture = newTexture;
        mStagingSubresource = D3D11CalcSubresource(lodOffset, 0, lodOffset + 1);
    }
    else
    {
        UNREACHABLE();
    }

    mDirty = false;
    return gl::Error(GL_NO_ERROR);
}