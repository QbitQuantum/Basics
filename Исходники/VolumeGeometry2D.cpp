//----------------------------------------------------------------------------------------
// Get the configuration object
Config* CVolumeGeometry2D::getConfiguration() const 
{
	Config* cfg = new Config();
	cfg->initialize("VolumeGeometry2D");

	cfg->self->addChildNode("GridColCount", m_iGridColCount);
	cfg->self->addChildNode("GridRowCount", m_iGridRowCount);

	cfg->self->addOption("WindowMinX", m_fWindowMinX);
	cfg->self->addOption("WindowMaxX", m_fWindowMaxX);
	cfg->self->addOption("WindowMinY", m_fWindowMinY);
	cfg->self->addOption("WindowMaxY", m_fWindowMaxY);

	return cfg;
}