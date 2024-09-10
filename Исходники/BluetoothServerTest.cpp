	void accept()
	{
		printf("WAITING for connection...");
		mCurrentConnectionListener = new ClientConnectionListener(mNextId++);
		mServer->accept(mCurrentConnectionListener); // TODO: try with NULL or use dummy listener.
	}