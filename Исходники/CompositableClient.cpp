TemporaryRef<DeprecatedTextureClient>
CompositableClient::CreateDeprecatedTextureClient(DeprecatedTextureClientType aDeprecatedTextureClientType,
                                                  gfxContentType aContentType)
{
  MOZ_ASSERT(GetForwarder(), "Can't create a texture client if the compositable is not connected to the compositor.");
  LayersBackend parentBackend = GetForwarder()->GetCompositorBackendType();
  RefPtr<DeprecatedTextureClient> result;

  switch (aDeprecatedTextureClientType) {
  case TEXTURE_SHARED_GL:
    if (parentBackend == LAYERS_OPENGL) {
      result = new DeprecatedTextureClientSharedOGL(GetForwarder(), GetTextureInfo());
    }
     break;
  case TEXTURE_SHARED_GL_EXTERNAL:
    if (parentBackend == LAYERS_OPENGL) {
      result = new DeprecatedTextureClientSharedOGLExternal(GetForwarder(), GetTextureInfo());
    }
    break;
  case TEXTURE_STREAM_GL:
    if (parentBackend == LAYERS_OPENGL) {
      result = new DeprecatedTextureClientStreamOGL(GetForwarder(), GetTextureInfo());
    }
    break;
  case TEXTURE_YCBCR:
    if (parentBackend == LAYERS_OPENGL ||
        parentBackend == LAYERS_D3D9 ||
        parentBackend == LAYERS_D3D11 ||
        parentBackend == LAYERS_BASIC) {
      result = new DeprecatedTextureClientShmemYCbCr(GetForwarder(), GetTextureInfo());
    }
    break;
  case TEXTURE_CONTENT:
#ifdef XP_WIN
    if (parentBackend == LAYERS_D3D11 && gfxWindowsPlatform::GetPlatform()->GetD2DDevice()) {
      result = new DeprecatedTextureClientD3D11(GetForwarder(), GetTextureInfo());
      break;
    }
    if (parentBackend == LAYERS_D3D9 &&
        !GetForwarder()->ForwardsToDifferentProcess()) {
      // We can't use a d3d9 texture for an RGBA surface because we cannot get a DC for
      // for a gfxWindowsSurface.
      // We have to wait for the compositor thread to create a d3d9 device before we
      // can create d3d9 textures on the main thread (because we need to reset on the
      // compositor thread, and the d3d9 device must be reset on the same thread it was
      // created on).
      if (aContentType == GFX_CONTENT_COLOR_ALPHA ||
          !gfxWindowsPlatform::GetPlatform()->GetD3D9Device()) {
        result = new DeprecatedTextureClientDIB(GetForwarder(), GetTextureInfo());
      } else {
        result = new DeprecatedTextureClientD3D9(GetForwarder(), GetTextureInfo());
      }
      break;
    }
#endif
     // fall through to TEXTURE_SHMEM
  case TEXTURE_SHMEM:
    result = new DeprecatedTextureClientShmem(GetForwarder(), GetTextureInfo());
    break;
  case TEXTURE_FALLBACK:
#ifdef XP_WIN
    if (parentBackend == LAYERS_D3D11 ||
        parentBackend == LAYERS_D3D9) {
      result = new DeprecatedTextureClientShmem(GetForwarder(), GetTextureInfo());
    }
#endif
    break;
  default:
    MOZ_ASSERT(false, "Unhandled texture client type");
  }

  // If we couldn't create an appropriate texture client,
  // then return nullptr so the caller can chose another
  // type.
  if (!result) {
    return nullptr;
  }

  MOZ_ASSERT(result->SupportsType(aDeprecatedTextureClientType),
             "Created the wrong texture client?");
  result->SetFlags(GetTextureInfo().mTextureFlags);

  return result.forget();
}