GeometryService::InOut TiltedCylinderIF::InsideOutside(const RealVect& lo,
                                                       const RealVect& hi) const
{

  // Fast Sphere-Box intersection from "Graphics Gems" pp 335-338, 1990

  Real dmin = 0; //distance from cylinder axis to nearest  point in box (squared)
  Real dmax = 0; //distance from cylinder axis to farthest point in box (squared)
  Real ai, bi, a, b;

  Tuple<int,CH_SPACEDIM-1> tanDirs = PolyGeom::computeTanDirs(m_coordDir);
  for (int i=0; i<CH_SPACEDIM-1; ++i)
    {
      ai = m_point[tanDirs[i]] - lo[tanDirs[i]];
      bi = m_point[tanDirs[i]] - hi[tanDirs[i]];
      a = ai * ai;
      b = bi * bi;
      dmax = dmax + Max(a,b);
      if (m_point[tanDirs[i]] < lo[tanDirs[i]] || m_point[tanDirs[i]] > hi[tanDirs[i]]) dmin = dmin + Min(a,b);
    }

  if (m_inside)
    {
      if (dmin >= m_radius2) return GeometryService::Covered;
      if (dmax <  m_radius2) return GeometryService::Regular;
    }
  else
    {
      if (dmin >  m_radius2) return GeometryService::Regular;
      if (dmax <= m_radius2) return GeometryService::Covered;
    }
  return GeometryService::Irregular;
}