bool CD3DPixelShader::Create(const void* code, size_t codeLength)
{
  ReleaseShader();

  ID3D11Device* pDevice = g_Windowing.Get3D11Device();

  if (!pDevice)
    return false;

  // trick to load bytecode into ID3DBlob
  if (FAILED(D3DStripShader(code, codeLength, D3DCOMPILER_STRIP_REFLECTION_DATA, &m_PSBuffer)))
  {
    CLog::Log(LOGERROR, __FUNCTION__ " - Failed to load the vertex shader.");
    return false;
  }

  m_inited = CreateInternal();

  if (m_inited)
    g_Windowing.Register(this);

  return m_inited;
}