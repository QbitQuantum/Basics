void TextureCache::TCacheEntry::CopyRectangleFromTexture(const TCacheEntryBase* source,
                                                         const MathUtil::Rectangle<int>& src_rect,
                                                         const MathUtil::Rectangle<int>& dst_rect)
{
  const TCacheEntry* srcentry = reinterpret_cast<const TCacheEntry*>(source);
  if (src_rect.GetWidth() == dst_rect.GetWidth() && src_rect.GetHeight() == dst_rect.GetHeight())
  {
    // These assertions should hold true unless the base code is passing us sizes too large, in
    // which case it should be fixed instead.
    _assert_msg_(VIDEO, static_cast<u32>(src_rect.GetWidth()) <= source->config.width &&
                            static_cast<u32>(src_rect.GetHeight()) <= source->config.height,
                 "Source rect is too large for CopyRectangleFromTexture");

    _assert_msg_(VIDEO, static_cast<u32>(dst_rect.GetWidth()) <= config.width &&
                            static_cast<u32>(dst_rect.GetHeight()) <= config.height,
                 "Dest rect is too large for CopyRectangleFromTexture");

    CD3DX12_BOX src_box(src_rect.left, src_rect.top, 0, src_rect.right, src_rect.bottom,
                        srcentry->config.layers);
    D3D12_TEXTURE_COPY_LOCATION dst_location =
        CD3DX12_TEXTURE_COPY_LOCATION(m_texture->GetTex12(), 0);
    D3D12_TEXTURE_COPY_LOCATION src_location =
        CD3DX12_TEXTURE_COPY_LOCATION(srcentry->m_texture->GetTex12(), 0);

    m_texture->TransitionToResourceState(D3D::current_command_list, D3D12_RESOURCE_STATE_COPY_DEST);
    srcentry->m_texture->TransitionToResourceState(D3D::current_command_list,
                                                   D3D12_RESOURCE_STATE_COPY_SOURCE);
    D3D::current_command_list->CopyTextureRegion(&dst_location, dst_rect.left, dst_rect.top, 0,
                                                 &src_location, &src_box);

    m_texture->TransitionToResourceState(D3D::current_command_list,
                                         D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    srcentry->m_texture->TransitionToResourceState(D3D::current_command_list,
                                                   D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

    return;
  }
  else if (!config.rendertarget)
  {
    return;
  }

  D3D::SetViewportAndScissor(dst_rect.left, dst_rect.top, dst_rect.GetWidth(),
                             dst_rect.GetHeight());

  m_texture->TransitionToResourceState(D3D::current_command_list,
                                       D3D12_RESOURCE_STATE_RENDER_TARGET);
  D3D::current_command_list->OMSetRenderTargets(1, &m_texture->GetRTV12(), FALSE, nullptr);

  D3D::SetLinearCopySampler();

  D3D12_RECT src_rc;
  src_rc.left = src_rect.left;
  src_rc.right = src_rect.right;
  src_rc.top = src_rect.top;
  src_rc.bottom = src_rect.bottom;

  D3D::DrawShadedTexQuad(
      srcentry->m_texture, &src_rc, srcentry->config.width, srcentry->config.height,
      StaticShaderCache::GetColorCopyPixelShader(false), StaticShaderCache::GetSimpleVertexShader(),
      StaticShaderCache::GetSimpleVertexShaderInputLayout(), D3D12_SHADER_BYTECODE(), 1.0, 0,
      DXGI_FORMAT_R8G8B8A8_UNORM, false, m_texture->GetMultisampled());

  m_texture->TransitionToResourceState(D3D::current_command_list,
                                       D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

  FramebufferManager::GetEFBColorTexture()->TransitionToResourceState(
      D3D::current_command_list, D3D12_RESOURCE_STATE_RENDER_TARGET);
  FramebufferManager::GetEFBDepthTexture()->TransitionToResourceState(
      D3D::current_command_list, D3D12_RESOURCE_STATE_DEPTH_WRITE);

  g_renderer->RestoreAPIState();
}