GifPixRect *GifPixRect::clone(double scaleFactor) const {
  const CSize   rawSize = getSize();
  const CSize   scaledSize((int)(scaleFactor * rawSize.cx), (int)(scaleFactor * rawSize.cy));
  GifPixRect   *copy = new GifPixRect(scaledSize);
  if(scaleFactor == 1) {
    copy->copyImage(this);
  } else {
    HDC dc = copy->getDC();
    bool highQuality = true;
    SetStretchBltMode(dc, highQuality?HALFTONE:COLORONCOLOR);
    PixRect::stretchBlt(dc, copy->getRect(), SRCCOPY, this, getRect());
    copy->releaseDC(dc);
  }
  copy->m_topLeft = CPoint((int)(scaleFactor * m_topLeft.x), (int)(scaleFactor * m_topLeft.y));
  copy->m_gcb     = m_gcb;
  return copy;
}