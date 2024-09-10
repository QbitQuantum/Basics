//--------------------------------------------------------------
// constructor
BitmapSurface::BitmapSurface()
{
  m_bitmapDC = CreateCompatibleDC(NULL);
  SetGraphicsMode(m_bitmapDC, GM_ADVANCED);

  m_bitmapWidth = 0;
  m_bitmapHeight = 0;
  m_bitmapData = NULL;
  m_bitmap = NULL;
}