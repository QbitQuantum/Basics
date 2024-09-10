HANDLE WrappedOpenGL::wglDXRegisterObjectNV(HANDLE hDevice, void *dxObject, GLuint name,
                                            GLenum type, GLenum access)
{
  RDCASSERT(IsCaptureMode(m_State));

  ID3D11Resource *real = UnwrapDXResource(dxObject);

  if(real == NULL)
  {
    SetLastError(ERROR_OPEN_FAILED);
    return 0;
  }

  WrappedHANDLE *wrapped = new WrappedHANDLE();

  if(type == eGL_RENDERBUFFER)
    wrapped->res = RenderbufferRes(GetCtx(), name);
  else if(type == eGL_NONE)
    wrapped->res = BufferRes(GetCtx(), name);
  else
    wrapped->res = TextureRes(GetCtx(), name);

  GLResourceRecord *record = GetResourceManager()->GetResourceRecord(wrapped->res);

  if(!record)
  {
    RDCERR("Unrecognised object with type %x and name %u", type, name);
    delete wrapped;
    return NULL;
  }

  SERIALISE_TIME_CALL(wrapped->real =
                          m_Real.wglDXRegisterObjectNV(hDevice, real, name, type, access));

  {
    RDCASSERT(record);

    USE_SCRATCH_SERIALISER();
    SCOPED_SERIALISE_CHUNK(gl_CurChunk);
    Serialise_wglDXRegisterObjectNV(ser, wrapped->res, type, dxObject);

    record->AddChunk(scope.Get());
  }

  if(type != eGL_NONE)
  {
    ResourceFormat fmt;
    uint32_t width = 0, height = 0, depth = 0, mips = 0, layers = 0, samples = 0;
    GetDXTextureProperties(dxObject, fmt, width, height, depth, mips, layers, samples);

    // defined as arrays mostly for Coverity code analysis to stay calm about passing
    // them to the *TexParameter* functions
    GLint maxlevel[4] = {GLint(mips - 1), 0, 0, 0};

    m_Real.glTextureParameteriEXT(wrapped->res.name, type, eGL_TEXTURE_MAX_LEVEL, GLint(mips - 1));

    ResourceId texId = record->GetResourceID();
    m_Textures[texId].resource = wrapped->res;
    m_Textures[texId].curType = type;
    m_Textures[texId].width = width;
    m_Textures[texId].height = height;
    m_Textures[texId].depth = RDCMAX(depth, samples);
    m_Textures[texId].samples = samples;
    m_Textures[texId].dimension = 2;
    if(type == eGL_TEXTURE_1D || type == eGL_TEXTURE_1D_ARRAY)
      m_Textures[texId].dimension = 1;
    else if(type == eGL_TEXTURE_3D)
      m_Textures[texId].dimension = 3;

    m_Textures[texId].internalFormat = MakeGLFormat(fmt);
  }

  return wrapped;
}