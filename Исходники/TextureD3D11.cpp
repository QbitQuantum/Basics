TemporaryRef<DeprecatedTextureHost>
CreateDeprecatedTextureHostD3D11(SurfaceDescriptorType aDescriptorType,
                                 uint32_t aDeprecatedTextureHostFlags,
                                 uint32_t aTextureFlags)
{
  RefPtr<DeprecatedTextureHost> result;
  if (aDescriptorType == SurfaceDescriptor::TYCbCrImage) {
    result = new DeprecatedTextureHostYCbCrD3D11();
  } else if (aDescriptorType == SurfaceDescriptor::TSurfaceDescriptorD3D10) {
    result = new DeprecatedTextureHostDXGID3D11();
  } else {
    result = new DeprecatedTextureHostShmemD3D11();
  }

  result->SetFlags(aTextureFlags);

  return result.forget();
}