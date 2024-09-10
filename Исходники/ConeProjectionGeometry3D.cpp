//----------------------------------------------------------------------------------------
// Get the configuration object
Config* CConeProjectionGeometry3D::getConfiguration() const 
{
	Config* cfg = new Config();
	cfg->initialize("ProjectionGeometry3D");
	cfg->self.addAttribute("type", "cone");
	cfg->self.addChildNode("DetectorSpacingX", m_fDetectorSpacingX);
	cfg->self.addChildNode("DetectorSpacingY", m_fDetectorSpacingY);
	cfg->self.addChildNode("DetectorRowCount", m_iDetectorRowCount);
	cfg->self.addChildNode("DetectorColCount", m_iDetectorColCount);
	cfg->self.addChildNode("DistanceOriginDetector", m_fOriginDetectorDistance);
	cfg->self.addChildNode("DistanceOriginSource", m_fOriginSourceDistance);
	cfg->self.addChildNode("ProjectionAngles", m_pfProjectionAngles, m_iProjectionAngleCount);
	return cfg;
}