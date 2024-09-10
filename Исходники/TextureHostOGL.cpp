TemporaryRef<DeprecatedTextureHost>
CreateDeprecatedTextureHostOGL(SurfaceDescriptorType aDescriptorType,
                     uint32_t aDeprecatedTextureHostFlags,
                     uint32_t aTextureFlags)
{
  RefPtr<DeprecatedTextureHost> result = nullptr;

  if (aDescriptorType == SurfaceDescriptor::TYCbCrImage) {
    result = new YCbCrDeprecatedTextureHostOGL();
  } else if (aDescriptorType == SurfaceDescriptor::TSurfaceStreamDescriptor) {
    result = new SurfaceStreamHostOGL();
  } else if (aDescriptorType == SurfaceDescriptor::TSharedTextureDescriptor) {
    result = new SharedDeprecatedTextureHostOGL();
#ifdef MOZ_WIDGET_GONK
  } else if (aDescriptorType == SurfaceDescriptor::TSurfaceDescriptorGralloc) {
    result = new GrallocDeprecatedTextureHostOGL();
#endif
  } else if (aDeprecatedTextureHostFlags & TEXTURE_HOST_TILED) {
    result = new TiledDeprecatedTextureHostOGL();
  } else {
    result = new TextureImageDeprecatedTextureHostOGL();
  }

  NS_ASSERTION(result, "Result should have been created.");

  result->SetFlags(aTextureFlags);
  return result.forget();
}