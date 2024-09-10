UINT AviConverter::run() {
  try {
    CPicture picture;
    picture.load(m_nameArray[0]);
    const CSize imageSize = picture.getSize();

    HDC screenDC = getScreenDC();
    m_dc     = CreateCompatibleDC(screenDC);
    m_bitmap = CreateCompatibleBitmap(screenDC, imageSize.cx, imageSize.cy);
    DeleteDC(screenDC);
    DWORD codec = 0; // mmioFOURCC('w','m','v',' ');

    if(ACCESS(m_outFileName, 0) == 0) {
      UNLINK(m_outFileName);
    }
    CAviFile aviFile(m_outFileName, true, codec, m_framesPerSecond);

    for(m_index = 0; m_index < (int)m_nameArray.size(); m_index += m_useEvery) {
      if(isInterrupted()) {
        throwException(_T("Interrupted by user"));
      }
      picture.load(m_nameArray[m_index]);
      HGDIOBJ oldGDI = SelectObject(m_dc, m_bitmap);
      picture.show(m_dc);
      SelectObject(m_dc, oldGDI);
      aviFile.appendNewFrame(m_bitmap);
    }
  } catch(Exception e) {
    m_ok  = false;
    m_msg = e.what();
  }
  return 0;
}