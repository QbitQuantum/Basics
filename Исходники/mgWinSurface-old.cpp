//--------------------------------------------------------------
// common init
void mgXPSurface::init(
  BOOL singleTile,
  BOOL inworld)
{
  m_singleTile = singleTile;
  m_inworld = inworld;

  // create the DC so we can measure text before setting size
  m_surfaceDC = CreateCompatibleDC(NULL);
  m_alphaDC = CreateCompatibleDC(NULL);
  SetGraphicsMode(m_surfaceDC, GM_ADVANCED);
  SetStretchBltMode(m_surfaceDC, COLORONCOLOR);

  m_logPixelsY = GetDeviceCaps(m_surfaceDC, LOGPIXELSY);

  m_surfaceBitmap = NULL;
  m_alphaBitmap = NULL;
  m_tiles = NULL;
  m_vertTiles = 0;
  m_horzTiles = 0;
  m_isDamaged = false;

  m_imageWidth = 0;
  m_imageHeight = 0;
}