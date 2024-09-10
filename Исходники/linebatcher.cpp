void LineBatcher::DrawEllipsoid(const Vector& Center, const Vector& Extents,
                                unsigned int Color) {
#if BUILD_RELEASE
  if (m_IsDebug) {
    return;
  }
#endif

  STATICHASH(DebugSphereResolution);
  uint Resolution = ConfigManager::GetInt(sDebugSphereResolution, 16);
  uint TwoR = Resolution * 2;

  m_AddPositions.Resize(Resolution * 3);
  m_AddColors.Resize(Resolution * 3);
  m_AddIndices.Resize(Resolution * 6);

  for (uint i = 0; i < Resolution * 3; ++i) {
    m_AddColors[i] = Color;
  }

  float Mult = TWOPI / (float)Resolution;

  for (uint i = 0; i < Resolution; ++i) {
    float u = Cos((float)i * Mult);
    float v = Sin((float)i * Mult);
    m_AddPositions[i] =
        Vector(Center.x + u * Extents.x, Center.y + v * Extents.y, Center.z);
    m_AddPositions[i + Resolution] =
        Vector(Center.x + u * Extents.x, Center.y, Center.z + v * Extents.z);
    m_AddPositions[i + TwoR] =
        Vector(Center.x, Center.y + u * Extents.y, Center.z + v * Extents.z);
    m_AddIndices[i * 2] = (index_t)(i);
    m_AddIndices[i * 2 + 1] = (index_t)((i + 1) % Resolution);
    m_AddIndices[i * 2 + TwoR] = (index_t)(i + Resolution);
    m_AddIndices[i * 2 + TwoR + 1] =
        (index_t)(((i + 1) % Resolution) + Resolution);
    m_AddIndices[i * 2 + TwoR * 2] = (index_t)(i + TwoR);
    m_AddIndices[i * 2 + TwoR * 2 + 1] =
        (index_t)(((i + 1) % Resolution) + TwoR);
  }

  Add(m_AddPositions, m_AddColors, m_AddIndices);
}