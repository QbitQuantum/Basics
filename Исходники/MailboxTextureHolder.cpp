MailboxTextureHolder::MailboxTextureHolder(
    std::unique_ptr<TextureHolder> textureHolder) {
  DCHECK(textureHolder->isSkiaTextureHolder());
  sk_sp<SkImage> image = textureHolder->skImage();
  DCHECK(image);

  gpu::gles2::GLES2Interface* sharedGL = SharedGpuContext::gl();
  GrContext* sharedGrContext = SharedGpuContext::gr();
  if (!sharedGrContext) {
    // Can happen if the context is lost. The SkImage won't be any good now
    // anyway.
    return;
  }
  GLuint imageTextureId =
      skia::GrBackendObjectToGrGLTextureInfo(image->getTextureHandle(true))
          ->fID;
  sharedGL->BindTexture(GL_TEXTURE_2D, imageTextureId);

  sharedGL->GenMailboxCHROMIUM(m_mailbox.name);
  sharedGL->ProduceTextureCHROMIUM(GL_TEXTURE_2D, m_mailbox.name);
  const GLuint64 fenceSync = sharedGL->InsertFenceSyncCHROMIUM();
  sharedGL->Flush();
  sharedGL->GenSyncTokenCHROMIUM(fenceSync, m_syncToken.GetData());

  sharedGL->BindTexture(GL_TEXTURE_2D, 0);
  // We changed bound textures in this function, so reset the GrContext.
  sharedGrContext->resetContext(kTextureBinding_GrGLBackendState);
  m_size = IntSize(image->width(), image->height());
  m_textureId = imageTextureId;
  m_isConvertedFromSkiaTexture = true;
}