	void initializeRepresentation(std::shared_ptr<Fem3DRepresentation> fem)
	{
		fem->initialize(std::make_shared<SurgSim::Framework::Runtime>());
		fem->wakeUp();
		m_physicsManager->executeAdditions(fem);
	}