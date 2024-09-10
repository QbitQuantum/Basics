STDMETHODIMP CLAVSubtitleFrame::AddBitmap(CLAVSubRect *subRect)
{
  // Allocate memory for the new block
  void *mem = CoTaskMemRealloc(m_Bitmaps, sizeof(*m_Bitmaps) * (m_NumBitmaps+1));
  if (!mem) {
    return E_OUTOFMEMORY;
  }

  m_Bitmaps = (CLAVSubRect **)mem;
  m_Bitmaps[m_NumBitmaps] = subRect;
  m_NumBitmaps++;

  // Hold reference on the subtitle rect
  subRect->AddRef();

  return S_OK;
}