//----------------------------------------------------------------------------------------
// Get the configuration object
Config* CParallelVecProjectionGeometry3D::getConfiguration() const 
{
	Config* cfg = new Config();
	cfg->initialize("ProjectionGeometry3D");

	cfg->self.addAttribute("type", "parallel3d_vec");
	cfg->self.addChildNode("DetectorRowCount", m_iDetectorRowCount);
	cfg->self.addChildNode("DetectorColCount", m_iDetectorColCount);

	std::string vectors = "";
	for (int i = 0; i < m_iProjectionAngleCount; ++i) {
		SPar3DProjection& p = m_pProjectionAngles[i];
		vectors += StringUtil::toString(p.fRayX) + ",";
		vectors += StringUtil::toString(p.fRayY) + ",";
		vectors += StringUtil::toString(p.fRayZ) + ",";
		vectors += StringUtil::toString(p.fDetSX + 0.5f*m_iDetectorRowCount*p.fDetVX + 0.5f*m_iDetectorColCount*p.fDetUX) + ",";
		vectors += StringUtil::toString(p.fDetSY + 0.5f*m_iDetectorRowCount*p.fDetVY + 0.5f*m_iDetectorColCount*p.fDetUY) + ",";
		vectors += StringUtil::toString(p.fDetSZ + 0.5f*m_iDetectorRowCount*p.fDetVZ + 0.5f*m_iDetectorColCount*p.fDetUZ) + ",";
		vectors += StringUtil::toString(p.fDetUX) + ",";
		vectors += StringUtil::toString(p.fDetUY) + ",";
		vectors += StringUtil::toString(p.fDetUZ) + ",";
		vectors += StringUtil::toString(p.fDetVX) + ",";
		vectors += StringUtil::toString(p.fDetVY) + ",";
		vectors += StringUtil::toString(p.fDetVZ);
		if (i < m_iProjectionAngleCount-1) vectors += ';';
	}
	cfg->self.addChildNode("Vectors", vectors);

	return cfg;
}