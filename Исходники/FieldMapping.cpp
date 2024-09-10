void MatrixFieldMapping::updateTransform() 
{
  typedef MatrixCurve::SampleVec::const_iterator SampleIter;

  // Build the voxel to world space transforms ---
  M44d lsToVs;
  getLocalToVoxelMatrix(lsToVs);
  M44d vsToLs = lsToVs.inverse();
  // Loop over all samples in lsToWs, append vsToLs and create new curve
  // Also handle the special case where lsToWs has no samples. In that
  // case m_vsToWsCurve still has to have one sample.
  const MatrixCurve::SampleVec &lsToWs = m_lsToWsCurve.samples();
  m_vsToWsCurve.clear();
  for (SampleIter i = lsToWs.begin(), end = lsToWs.end(); i != end; i++) {
    m_vsToWsCurve.addSample(i->first, vsToLs * i->second);
  }

  // See if the curve has more than just a single sample
  m_isTimeVarying = m_lsToWsCurve.numSamples() > 1;

  // Sample the time-varying transforms at time=0.0
  m_lsToWs = m_lsToWsCurve.linear(0.0);
  m_wsToLs = m_lsToWs.inverse();
  m_vsToWs = vsToLs * m_lsToWs;
  m_wsToVs = m_vsToWs.inverse();

  // Precompute the voxel size
  V3d voxelOrigin, nextVoxel;
  m_vsToWs.multVecMatrix(V3d(0, 0, 0), voxelOrigin);
  m_vsToWs.multVecMatrix(V3d(1, 0, 0), nextVoxel);
  m_wsVoxelSize.x = (nextVoxel - voxelOrigin).length();
  m_vsToWs.multVecMatrix(V3d(0, 1, 0), nextVoxel);
  m_wsVoxelSize.y = (nextVoxel - voxelOrigin).length();
  m_vsToWs.multVecMatrix(V3d(0, 0, 1), nextVoxel);
  m_wsVoxelSize.z = (nextVoxel - voxelOrigin).length();
}