	EnvironmentCoreApplication::~EnvironmentCoreApplication() {
		delete m_pCameraManager;
		delete m_pScene;
		delete m_pChSystem;
		closeWindow();
	}