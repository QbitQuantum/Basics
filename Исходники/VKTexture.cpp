void VKTexture::CopyRectangleFromTexture(const AbstractTexture* src,
                                         const MathUtil::Rectangle<int>& src_rect, u32 src_layer,
                                         u32 src_level, const MathUtil::Rectangle<int>& dst_rect,
                                         u32 dst_layer, u32 dst_level)
{
  Texture2D* src_texture = static_cast<const VKTexture*>(src)->GetRawTexIdentifier();

  _assert_msg_(VIDEO, static_cast<u32>(src_rect.GetWidth()) <= src_texture->GetWidth() &&
                          static_cast<u32>(src_rect.GetHeight()) <= src_texture->GetHeight(),
               "Source rect is too large for CopyRectangleFromTexture");

  _assert_msg_(VIDEO, static_cast<u32>(dst_rect.GetWidth()) <= m_config.width &&
                          static_cast<u32>(dst_rect.GetHeight()) <= m_config.height,
               "Dest rect is too large for CopyRectangleFromTexture");

  VkImageCopy image_copy = {
      {VK_IMAGE_ASPECT_COLOR_BIT, src_level, src_layer, src_texture->GetLayers()},
      {src_rect.left, src_rect.top, 0},
      {VK_IMAGE_ASPECT_COLOR_BIT, dst_level, dst_layer, m_config.layers},
      {dst_rect.left, dst_rect.top, 0},
      {static_cast<uint32_t>(src_rect.GetWidth()), static_cast<uint32_t>(src_rect.GetHeight()), 1}};

  // Must be called outside of a render pass.
  StateTracker::GetInstance()->EndRenderPass();

  src_texture->TransitionToLayout(g_command_buffer_mgr->GetCurrentCommandBuffer(),
                                  VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  m_texture->TransitionToLayout(g_command_buffer_mgr->GetCurrentCommandBuffer(),
                                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

  vkCmdCopyImage(g_command_buffer_mgr->GetCurrentCommandBuffer(), src_texture->GetImage(),
                 VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, m_texture->GetImage(),
                 VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &image_copy);

  // Ensure both textures remain in the SHADER_READ_ONLY layout so they can be bound.
  src_texture->TransitionToLayout(g_command_buffer_mgr->GetCurrentCommandBuffer(),
                                  VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  m_texture->TransitionToLayout(g_command_buffer_mgr->GetCurrentCommandBuffer(),
                                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}