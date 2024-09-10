void D3D11RenderTarget::captureColorBuffer(ColorImageR8G8B8A8 &result)
{
	auto &context = m_graphics->getContext();
    context.CopyResource(m_captureTexture, m_texture);

	result.allocate(m_width, m_height);

    D3D11_MAPPED_SUBRESOURCE resource;
    UINT subresource = D3D11CalcSubresource(0, 0, 0);
    HRESULT hr = context.Map(m_captureTexture, subresource, D3D11_MAP_READ, 0, &resource);
    const BYTE *data = (BYTE *)resource.pData;

    for (UINT y = 0; y < m_height; y++)
    {
        memcpy(&result(0U, y), data + resource.RowPitch * y, m_width * sizeof(ml::vec4uc));
    }

    context.Unmap(m_captureTexture, subresource);
}