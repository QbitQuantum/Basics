// Creates video samples based on a specified media type.
HRESULT D3DPresentEngine::CreateVideoSamples(IMFMediaType *pFormat, VideoSampleList& videoSampleQueue)
{
  if (pFormat == NULL)
  {
    return MF_E_UNEXPECTED;
  }

  HRESULT hr = S_OK;

  D3DFORMAT d3dFormat = D3DFMT_UNKNOWN;

  IMFSample *pVideoSample = NULL;

  AutoLock lock(m_ObjectLock);

  ReleaseResources();

  // Helper object for reading the proposed type.
  VideoType videoType(pFormat);

  // Get some information about the video format.
  hr = videoType.GetFrameDimensions(&m_Width, &m_Height);
  CHECK_HR(hr, "D3DPresentEngine::CreateVideoSamples VideoType::GetFrameDimensions() failed");
  hr = GetAspectRatio(pFormat, m_ArX, m_ArY);
  if (FAILED(hr))
  {
    m_ArX = m_Width;
    m_ArY = m_Height;
  }

  //hr = videoType.GetFourCC((DWORD*)&d3dFormat);
  //CHECK_HR(hr, "D3DPresentEngine::CreateVideoSamples VideoType::GetFourCC() failed");

  // Morpheus_xx, 2016-08-14: we force a format without alpha channel here, because rendering subtitles with MPC-HC engine expects this format. Actually I can't imagine a video format
  // that actually delivers alpha channel information.
  d3dFormat = D3DFMT_X8R8G8B8;

  for (int i = 0; i < NUM_PRESENTER_BUFFERS; i++)
  {
    CComPtr<IDirect3DTexture9> texture;
    hr = m_pDevice->CreateTexture(m_Width, m_Height, 1, D3DUSAGE_RENDERTARGET, d3dFormat, D3DPOOL_DEFAULT, &texture, NULL);
    if (FAILED(hr))
    {
      Log("D3DPresentEngine::CreateVideoSamples Could not create texture %d. Error 0x%x", i, hr);
      break;
    }
    CComPtr<IDirect3DSurface9> surface;
    hr = texture->GetSurfaceLevel(0, &surface);
    if (FAILED(hr))
    {
      Log("D3DPresentEngine::CreateVideoSamples Could not get surface from texture. Error 0x%x", hr);
      break;
    }

    hr = MFCreateVideoSampleFromSurface(surface, &pVideoSample);
    if (FAILED(hr))
    {
      Log("D3DPresentEngine::CreateVideoSamples CreateVideoSampleFromSurface failed: 0x%x", hr);
      break;
    }

    // Add it to the list.
    hr = videoSampleQueue.InsertBack(pVideoSample);
    if (FAILED(hr))
    {
      SAFE_RELEASE(pVideoSample);
      ReleaseResources();
      return hr;
    }
    SAFE_RELEASE(pVideoSample);
  }

  return hr;
}