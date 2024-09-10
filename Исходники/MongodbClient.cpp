	MongodbClientInternalData()
	{
		connection = new mongo();
		DVASSERT(connection);

		Memset(connection, 0, sizeof(mongo));
		mongo_init(connection);
	}