	bool ModuleName::Initialize()
	{
		if (s_moduleReferenceCounter > 0)
		{
			s_moduleReferenceCounter++;
			return true; // Already initialized
		}

		// Initialize module dependencies
		if (!Core::Initialize())
		{
			NazaraError("Failed to initialize core module");
			return false;
		}

		s_moduleReferenceCounter++;

		CallOnExit onExit(ModuleName::Uninitialize);

		// Initialize module here

		onExit.Reset();

		NazaraNotice("Initialized: ModuleName module");
		return true;
	}