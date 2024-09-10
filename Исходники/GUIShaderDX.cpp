void CGUIShaderDX::ApplyChanges(void)
{
  ID3D11DeviceContext* pContext = g_Windowing.Get3D11Context();
  D3D11_MAPPED_SUBRESOURCE res;

  if (m_bIsWVPDirty)
  {
    if (SUCCEEDED(pContext->Map(m_pWVPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res)))
    {
      XMMATRIX worldView = XMMatrixMultiply(m_cbWorldViewProj.world, m_cbWorldViewProj.view);
      XMMATRIX worldViewProj = XMMatrixMultiplyTranspose(worldView, m_cbWorldViewProj.projection);

      cbWorld* buffer = (cbWorld*)res.pData;
      buffer->wvp = worldViewProj;
      buffer->blackLevel = (g_Windowing.UseLimitedColor() ? 16.f / 255.f : 0.f);
      buffer->colorRange = (g_Windowing.UseLimitedColor() ? (235.f - 16.f) / 255.f : 1.0f);

      pContext->Unmap(m_pWVPBuffer, 0);
      m_bIsWVPDirty = false;
    }
  }

  // update view port buffer
  if (m_bIsVPDirty)
  {
    if (SUCCEEDED(pContext->Map(m_pVPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res)))
    {
      *(cbViewPort*)res.pData = m_cbViewPort;
      pContext->Unmap(m_pVPBuffer, 0);
      m_bIsVPDirty = false;
    }
  }
}