//--------------------------------------------------------------
// constructor
FlatWorld::FlatWorld()
{
  m_mapWidth = 0;
  m_mapHeight = 0;

  m_mapDC = NULL;
  m_mapBitmap = NULL;
  m_mapData = NULL;
  m_mapSpan = 0;
  m_mapDepth = 24;

  m_playerX = 0.0;
  m_playerY = 0.0;
  m_playerAngle = 90.0;
  m_terrainScale = 20.0;

  // build initial terrain view
  m_lastTerrainX = (int) floor(m_playerX / m_terrainScale);
  m_lastTerrainY = (int) floor(m_playerY / m_terrainScale);

  m_mapDC = CreateCompatibleDC(NULL);
  SetGraphicsMode(m_mapDC, GM_ADVANCED);

  m_redBrush = CreateSolidBrush(RGB(255, 0, 0));
  m_redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
}