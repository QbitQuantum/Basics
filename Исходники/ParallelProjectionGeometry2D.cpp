//----------------------------------------------------------------------------------------
// Get the configuration object
Config* CParallelProjectionGeometry2D::getConfiguration() const 
{
	Config* cfg = new Config();
	cfg->initialize("ProjectionGeometry2D");
	cfg->self.addAttribute("type", "parallel");
	cfg->self.addChildNode("DetectorCount", getDetectorCount());
	cfg->self.addChildNode("DetectorWidth", getDetectorWidth());
	cfg->self.addChildNode("ProjectionAngles", m_pfProjectionAngles, m_iProjectionAngleCount);
	return cfg;
}