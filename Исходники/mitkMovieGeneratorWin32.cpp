bool mitk::MovieGeneratorWin32::AddFrame(void *data)
{
  HRESULT hr = AVIStreamWrite(m_pStreamCompressed, // stream pointer
                              m_lFrame,            // time of this frame
                              1,                   // number to write
                              (BYTE *)data,        // image buffer
                              m_bih.biSizeImage,   // size of this frame
                              AVIIF_KEYFRAME,      // flags....
                              NULL,
                              NULL);
  // updating frame counter
  m_lFrame++;

  if (hr == AVIERR_OK)
    return true;
  else
    return false;
}