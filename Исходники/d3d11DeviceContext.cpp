void myD3D11DeviceContext::readTexture(ID3D11Texture2D *inputTexture, Bitmap &result)
{
    ID3D11Texture2D *captureTexture;

    D3D11_TEXTURE2D_DESC renderDesc;
    inputTexture->GetDesc(&renderDesc);

    renderDesc.MipLevels = 1;
    renderDesc.ArraySize = 1;
    renderDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    renderDesc.SampleDesc.Count = 1;
    renderDesc.SampleDesc.Quality = 0;
    renderDesc.BindFlags = 0;
    renderDesc.MiscFlags = 0;
    renderDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
    renderDesc.Usage = D3D11_USAGE_STAGING;
    assets->device->base->CreateTexture2D(&renderDesc, nullptr, &captureTexture);

    assets->context->base->CopyResource(captureTexture, inputTexture);

    result.allocate(renderDesc.Width, renderDesc.Height);

    D3D11_MAPPED_SUBRESOURCE resource;
    UINT subresource = D3D11CalcSubresource(0, 0, 0);
    HRESULT hr = assets->context->base->Map(captureTexture, subresource, D3D11_MAP_READ, 0, &resource);
    const BYTE *data = (BYTE *)resource.pData;

    for (UINT y = 0; y < renderDesc.Height; y++)
    {
        memcpy(&result(0U, y), data + resource.RowPitch * y, renderDesc.Width * sizeof(ml::vec4uc));
    }

    assets->context->base->Unmap(captureTexture, subresource);

    captureTexture->Release();
}