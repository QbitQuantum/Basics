void APerlinNoise2D::GetValue(float x, float y, float * pvValue, int nNumValue)
{
  int      i, k;
  float    vx, sx, vy, sy;
  int      x1, x2, y1, y2;
  float    value1[3], value2[3];
  float    valueX1[3], valueX2[3];
  float    value[3];
  float    vFinal[3];

  memset(vFinal, 0, sizeof(float) * nNumValue);
  for(i=0; i<m_nOctaveNum; i++)
  {
    if( m_nActiveOctave != -1 && m_nActiveOctave != i )
      continue;

    // Get Horizon interpolated value;
    vx = m_nStartPos[i] % m_nBufferWidth + x / m_nWaveLength[i];
    x1 = int(vx);
    sx = vx - x1;
    sx = S_CURVE(sx);
    x2 = x1 + 1;

    vy = m_nStartPos[i] / m_nBufferWidth + y / m_nWaveLength[i];
    y1 = int(vy);
    sy = vy - y1;
    sy = S_CURVE(sy);
    y2 = y1 + 1;
    
    GetRandValues(x1, y1, value1, nNumValue);
    GetRandValues(x2, y1, value2, nNumValue);
    for(k=0; k<nNumValue; k++)
      valueX1[k] = LERP(sx, value1[k], value2[k]);

    GetRandValues(x1, y2, value1, nNumValue);
    GetRandValues(x2, y2, value2, nNumValue);
    for(k=0; k<nNumValue; k++)
      valueX2[k] = LERP(sx, value1[k], value2[k]);

    if( m_bTurbulence )
    {
      for(k=0; k<nNumValue; k++)
      {
        value[k] = (float)fabs(LERP(sy, valueX1[k], valueX2[k]));
        vFinal[k] += m_vAmplitude[i] * value[k];
      }
    }
    else
    {
      for(k=0; k<nNumValue; k++)
      {
        value[k] = LERP(sy, valueX1[k], valueX2[k]);
        vFinal[k] += m_vAmplitude[i] * value[k];
      }
    }
  }

  for(k=0; k<nNumValue; k++)
    pvValue[k] = vFinal[k];
}