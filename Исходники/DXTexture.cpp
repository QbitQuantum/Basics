void DXStagingTexture::CopyFromTexture(const AbstractTexture* src,
                                       const MathUtil::Rectangle<int>& src_rect, u32 src_layer,
                                       u32 src_level, const MathUtil::Rectangle<int>& dst_rect)
{
  _assert_(m_type == StagingTextureType::Readback);
  _assert_(src_rect.GetWidth() == dst_rect.GetWidth() &&
           src_rect.GetHeight() == dst_rect.GetHeight());
  _assert_(src_rect.left >= 0 && static_cast<u32>(src_rect.right) <= src->GetConfig().width &&
           src_rect.top >= 0 && static_cast<u32>(src_rect.bottom) <= src->GetConfig().height);
  _assert_(dst_rect.left >= 0 && static_cast<u32>(dst_rect.right) <= m_config.width &&
           dst_rect.top >= 0 && static_cast<u32>(dst_rect.bottom) <= m_config.height);

  if (IsMapped())
    DXStagingTexture::Unmap();

  CD3D11_BOX src_box(src_rect.left, src_rect.top, 0, src_rect.right, src_rect.bottom, 1);
  D3D::context->CopySubresourceRegion(
      m_tex, 0, static_cast<u32>(dst_rect.left), static_cast<u32>(dst_rect.top), 0,
      static_cast<const DXTexture*>(src)->GetRawTexIdentifier()->GetTex(),
      D3D11CalcSubresource(src_level, src_layer, src->GetConfig().levels), &src_box);

  m_needs_flush = true;
}