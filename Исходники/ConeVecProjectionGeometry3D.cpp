//----------------------------------------------------------------------------------------
// Get the configuration object
Config* CConeVecProjectionGeometry3D::getConfiguration() const 
{
	Config* cfg = new Config();
	cfg->initialize("ProjectionGeometry3D");

	cfg->self.addAttribute("type", "cone_vec");
	cfg->self.addChildNode("DetectorRowCount", m_iDetectorRowCount);
	cfg->self.addChildNode("DetectorColCount", m_iDetectorColCount);

	std::string vectors = "";
	for (int i = 0; i < m_iProjectionAngleCount; ++i) {
		SConeProjection& p = m_pProjectionAngles[i];
		vectors += boost::lexical_cast<string>(p.fSrcX) + ",";
		vectors += boost::lexical_cast<string>(p.fSrcY) + ",";
		vectors += boost::lexical_cast<string>(p.fSrcZ) + ",";
		vectors += boost::lexical_cast<string>(p.fDetSX + 0.5f*m_iDetectorRowCount*p.fDetVX + 0.5f*m_iDetectorColCount*p.fDetUX) + ",";
		vectors += boost::lexical_cast<string>(p.fDetSY + 0.5f*m_iDetectorRowCount*p.fDetVY + 0.5f*m_iDetectorColCount*p.fDetUY) + ",";
		vectors += boost::lexical_cast<string>(p.fDetSZ + 0.5f*m_iDetectorRowCount*p.fDetVZ + 0.5f*m_iDetectorColCount*p.fDetUZ) + ",";
		vectors += boost::lexical_cast<string>(p.fDetUX) + ",";
		vectors += boost::lexical_cast<string>(p.fDetUY) + ",";
		vectors += boost::lexical_cast<string>(p.fDetUZ) + ",";
		vectors += boost::lexical_cast<string>(p.fDetVX) + ",";
		vectors += boost::lexical_cast<string>(p.fDetVY) + ",";
		vectors += boost::lexical_cast<string>(p.fDetVZ);
		if (i < m_iProjectionAngleCount-1) vectors += ';';
	}
	cfg->self.addChildNode("Vectors", vectors);

	return cfg;
}