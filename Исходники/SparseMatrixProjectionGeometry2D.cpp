//----------------------------------------------------------------------------------------
// Get the configuration object
Config* CSparseMatrixProjectionGeometry2D::getConfiguration() const 
{
	Config* cfg = new Config();
	cfg->initialize("ProjectionGeometry2D");
	cfg->self.addAttribute("type", "sparse matrix");
	cfg->self.addChildNode("DetectorCount", getDetectorCount());
	cfg->self.addChildNode("DetectorWidth", getDetectorWidth());
	cfg->self.addChildNode("ProjectionAngles", m_pfProjectionAngles, m_iProjectionAngleCount);
	cfg->self.addChildNode("MatrixID", CMatrixManager::getSingleton().getIndex(m_pMatrix));
	return cfg;
}