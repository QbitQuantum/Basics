TemporaryRef<CompositingRenderTarget>
CompositorOGL::CreateRenderTargetFromSource(const IntRect &aRect,
                                            const CompositingRenderTarget *aSource)
{
  GLuint tex = 0;
  GLuint fbo = 0;
  const CompositingRenderTargetOGL* sourceSurface
    = static_cast<const CompositingRenderTargetOGL*>(aSource);
  if (aSource) {
    CreateFBOWithTexture(aRect, INIT_MODE_COPY, sourceSurface->GetFBO(),
                         &fbo, &tex);
  } else {
    CreateFBOWithTexture(aRect, INIT_MODE_COPY, 0,
                         &fbo, &tex);
  }

  RefPtr<CompositingRenderTargetOGL> surface
    = new CompositingRenderTargetOGL(this, tex, fbo);
  surface->Initialize(IntSize(aRect.width, aRect.height),
                      mFBOTextureTarget,
                      INIT_MODE_COPY);
  return surface.forget();
}