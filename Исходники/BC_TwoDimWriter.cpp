void CBC_TwoDimWriter::RenderBitmapResult(CFX_DIBitmap*& pOutBitmap,
                                          int32_t& e) {
  if (m_bFixedSize) {
    pOutBitmap = CreateDIBitmap(m_Width, m_Height);
  } else {
    pOutBitmap = CreateDIBitmap(m_output->GetWidth(), m_output->GetHeight());
  }
  if (!pOutBitmap) {
    e = BCExceptionFailToCreateBitmap;
    return;
  }
  pOutBitmap->Clear(m_backgroundColor);
  int32_t leftPos = 0;
  int32_t topPos = 0;
  if (m_bFixedSize) {
    leftPos = (m_Width - m_output->GetWidth()) / 2;
    topPos = (m_Height - m_output->GetHeight()) / 2;
  }
  for (int32_t x = 0; x < m_output->GetWidth(); x++) {
    for (int32_t y = 0; y < m_output->GetHeight(); y++) {
      if (m_output->Get(x, y)) {
        pOutBitmap->SetPixel(leftPos + x, topPos + y, m_barColor);
      }
    }
  }
  if (!m_bFixedSize) {
    CFX_DIBitmap* pStretchBitmap = pOutBitmap->StretchTo(m_Width, m_Height);
    delete pOutBitmap;
    pOutBitmap = pStretchBitmap;
  }
}