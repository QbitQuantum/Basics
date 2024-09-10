void TextureConverter::EncodeTextureToMemoryYUYV(void* dst_ptr, u32 dst_width, u32 dst_stride,
                                                 u32 dst_height, Texture2D* src_texture,
                                                 const MathUtil::Rectangle<int>& src_rect)
{
  StateTracker::GetInstance()->EndRenderPass();

  // Borrow framebuffer from EFB2RAM encoder.
  VkCommandBuffer command_buffer = g_command_buffer_mgr->GetCurrentCommandBuffer();
  src_texture->TransitionToLayout(command_buffer, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  m_encoding_render_texture->TransitionToLayout(command_buffer,
                                                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

  // Use fragment shader to convert RGBA to YUYV.
  // Use linear sampler for downscaling. This texture is in BGRA order, so the data is already in
  // the order the guest is expecting and we don't have to swap it at readback time. The width
  // is halved because we're using an RGBA8 texture, but the YUYV data is two bytes per pixel.
  u32 output_width = dst_width / 2;
  UtilityShaderDraw draw(command_buffer,
                         g_object_cache->GetPipelineLayout(PIPELINE_LAYOUT_STANDARD),
                         m_encoding_render_pass, g_object_cache->GetPassthroughVertexShader(),
                         VK_NULL_HANDLE, m_rgb_to_yuyv_shader);
  VkRect2D region = {{0, 0}, {output_width, dst_height}};
  draw.BeginRenderPass(m_encoding_render_framebuffer, region);
  draw.SetPSSampler(0, src_texture->GetView(), g_object_cache->GetLinearSampler());
  draw.DrawQuad(0, 0, static_cast<int>(output_width), static_cast<int>(dst_height), src_rect.left,
                src_rect.top, 0, src_rect.GetWidth(), src_rect.GetHeight(),
                static_cast<int>(src_texture->GetWidth()),
                static_cast<int>(src_texture->GetHeight()));
  draw.EndRenderPass();

  // Render pass transitions to TRANSFER_SRC.
  m_encoding_render_texture->TransitionToLayout(g_command_buffer_mgr->GetCurrentCommandBuffer(),
                                                VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);

  // Copy from encoding texture to download buffer.
  m_encoding_download_texture->CopyFromImage(command_buffer, m_encoding_render_texture->GetImage(),
                                             VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, output_width,
                                             dst_height, 0, 0);
  Util::ExecuteCurrentCommandsAndRestoreState(false, true);

  // Finally, copy to guest memory. This may have a different stride.
  m_encoding_download_texture->ReadTexels(0, 0, output_width, dst_height, dst_ptr, dst_stride);
}