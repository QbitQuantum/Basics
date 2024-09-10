bool AVIWrite::Open(const char *filename)
{
  // create the AVI file
  if(FAILED(AVIFileOpen(&m_file,
                        filename,
                        OF_WRITE | OF_CREATE,
                        NULL))) {
    m_failed = true;
    return false;
  }
  // setup the video stream information
  ZeroMemory(&m_header, sizeof(AVISTREAMINFO));
  m_header.fccType = streamtypeVIDEO;
  m_header.dwScale = 1;
  m_header.dwRate = m_fps;
  m_header.dwSuggestedBufferSize  = m_bitmap.biSizeImage;

  // create the video stream
  if(FAILED(AVIFileCreateStream(m_file,
                                &m_stream,
                                &m_header))) {
    m_failed = true;
    return false;
  }
      
  ZeroMemory(&m_options, sizeof(AVICOMPRESSOPTIONS));
  m_arrayOptions[0] = &m_options;

  // call the dialog to setup the compress options to be used
  if(!AVISaveOptions(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), 0, 1, &m_stream, m_arrayOptions)) {
    m_failed = true;
    return false;
  }
  
  // create the compressed stream
  if(FAILED(AVIMakeCompressedStream(&m_streamCompressed, m_stream, &m_options, NULL))) {
    m_failed = true;
    return false;
  }
  
  // setup the video stream format
  if(FAILED( AVIStreamSetFormat(m_streamCompressed, 0,
                                &m_bitmap,
                                m_bitmap.biSize +
                                m_bitmap.biClrUsed * sizeof(RGBQUAD)))) {
    m_failed = true;
    return false;
  }

  return true;
}