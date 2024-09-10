HRESULT CDecD3D11::DeliverD3D11ReadbackDirect(LAVFrame *pFrame)
{
  AVD3D11VADeviceContext *pDeviceContext = (AVD3D11VADeviceContext *)((AVHWDeviceContext *)m_pDevCtx->data)->hwctx;
  AVFrame *src = (AVFrame *)pFrame->priv_data;

  if (m_pD3D11StagingTexture == nullptr)
  {
    D3D11_TEXTURE2D_DESC texDesc = { 0 };
    ((ID3D11Texture2D *)src->data[0])->GetDesc(&texDesc);

    texDesc.ArraySize = 1;
    texDesc.Usage = D3D11_USAGE_STAGING;
    texDesc.BindFlags = 0;
    texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

    HRESULT hr = pDeviceContext->device->CreateTexture2D(&texDesc, nullptr, &m_pD3D11StagingTexture);
    if (FAILED(hr))
    {
      ReleaseFrame(&pFrame);
      return E_FAIL;
    }
  }

  pDeviceContext->lock(pDeviceContext->lock_ctx);
  pDeviceContext->device_context->CopySubresourceRegion(m_pD3D11StagingTexture, 0, 0, 0, 0, (ID3D11Texture2D *)src->data[0], (UINT)(intptr_t)src->data[1], nullptr);
  pDeviceContext->unlock(pDeviceContext->lock_ctx);

  av_frame_free(&src);

  D3D11DirectPrivate *c = new D3D11DirectPrivate;
  c->pDeviceContex = av_buffer_ref(m_pDevCtx);
  c->pStagingTexture = m_pD3D11StagingTexture;
  m_pD3D11StagingTexture->AddRef();

  pFrame->priv_data = c;
  pFrame->destruct = d3d11_direct_free;

  GetPixelFormat(&pFrame->format, &pFrame->bpp);

  pFrame->direct = true;
  pFrame->direct_lock = d3d11_direct_lock;
  pFrame->direct_unlock = d3d11_direct_unlock;

  return Deliver(pFrame);
}