//---------------------------------------------------------------------
void D3D11RenderWindowBase::copyContentsToMemory(const PixelBox &dst, FrameBuffer buffer)
{
    if(mpBackBuffer == NULL)
        return;

    // get the backbuffer desc
    D3D11_TEXTURE2D_DESC BBDesc;
    mpBackBuffer->GetDesc( &BBDesc );

    ID3D11Texture2D *backbuffer = NULL;

    if(BBDesc.SampleDesc.Quality > 0)
    {
        D3D11_TEXTURE2D_DESC desc = BBDesc;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.CPUAccessFlags = 0;
        desc.BindFlags = 0;
        desc.SampleDesc.Quality = 0;
        desc.SampleDesc.Count = 1;

        HRESULT hr = mDevice->CreateTexture2D(
                         &desc,
                         NULL,
                         &backbuffer);

        if (FAILED(hr) || mDevice.isError())
        {
            String errorDescription = mDevice.getErrorDescription(hr);
            OGRE_EXCEPT_EX(Exception::ERR_RENDERINGAPI_ERROR, hr,
                           "Error creating texture\nError Description:" + errorDescription,
                           "D3D11RenderWindow::copyContentsToMemory" );
        }

        mDevice.GetImmediateContext()->ResolveSubresource(backbuffer, D3D11CalcSubresource(0, 0, 1), mpBackBuffer, D3D11CalcSubresource(0, 0, 1), desc.Format);
    }


    // change the parameters of the texture so we can read it
    BBDesc.Usage = D3D11_USAGE_STAGING;
    BBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    BBDesc.BindFlags = 0;
    BBDesc.SampleDesc.Quality = 0;
    BBDesc.SampleDesc.Count = 1;

    // create a temp buffer to copy to
    ID3D11Texture2D * pTempTexture2D;
    HRESULT hr = mDevice->CreateTexture2D(
                     &BBDesc,
                     NULL,
                     &pTempTexture2D);

    if (FAILED(hr) || mDevice.isError())
    {
        String errorDescription = mDevice.getErrorDescription(hr);
        OGRE_EXCEPT_EX(Exception::ERR_RENDERINGAPI_ERROR, hr,
                       "Error creating texture\nError Description:" + errorDescription,
                       "D3D11RenderWindow::copyContentsToMemory" );
    }
    // copy the back buffer
    mDevice.GetImmediateContext()->CopyResource(pTempTexture2D, backbuffer != NULL ? backbuffer : mpBackBuffer);

    // map the copied texture
    D3D11_MAPPED_SUBRESOURCE mappedTex2D;
    mDevice.GetImmediateContext()->Map(pTempTexture2D, 0,D3D11_MAP_READ, 0, &mappedTex2D);

    // copy the the texture to the dest
    PixelUtil::bulkPixelConversion(
        PixelBox(mWidth, mHeight, 1, D3D11Mappings::_getPF(BBDesc.Format), mappedTex2D.pData),
        dst);

    // unmap the temp buffer
    mDevice.GetImmediateContext()->Unmap(pTempTexture2D, 0);

    // Release the temp buffer
    SAFE_RELEASE(pTempTexture2D);
    SAFE_RELEASE(backbuffer);
}