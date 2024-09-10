//----------------------------------------------------------------------------------------
// Get the configuration object
Config* CFanFlatVecProjectionGeometry2D::getConfiguration() const 
{
	Config* cfg = new Config();
	cfg->initialize("ProjectionGeometry2D");
	cfg->self.addAttribute("type", "fanflat_vec");
	cfg->self.addChildNode("DetectorCount", getDetectorCount());
	std::string vectors = "";
	for (int i = 0; i < m_iProjectionAngleCount; ++i) {
		SFanProjection& p = m_pProjectionAngles[i];
		vectors += StringUtil::toString(p.fSrcX) + ",";
		vectors += StringUtil::toString(p.fSrcY) + ",";
		vectors += StringUtil::toString(p.fDetSX + 0.5f * m_iDetectorCount * p.fDetUX) + ",";
		vectors += StringUtil::toString(p.fDetSY + 0.5f * m_iDetectorCount * p.fDetUY) + ",";
		vectors += StringUtil::toString(p.fDetUX) + ",";
		vectors += StringUtil::toString(p.fDetUY);
		if (i < m_iProjectionAngleCount-1) vectors += ';';
	}
	cfg->self.addChildNode("Vectors", vectors);
	return cfg;
}