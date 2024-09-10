	void GBaseEngine::OnStateStackEmpty()
	{
		GTRACE(1, "the state stack is empty... shutting down...");
		shutDown();
	}