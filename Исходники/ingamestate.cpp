InGameState::~InGameState()
{
	if (m_factory)
	{
		delete m_factory;
		m_factory = NULL;
	}
	onExit();
}