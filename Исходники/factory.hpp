	Factory(kdb::KeySet config) :
		m_factory()
	{
		config.rewind();
		kdb::Key root = config.next();

		m_factory.insert(std::make_pair("list", new Cnstancer<ListChecker>()));

		kdb::Key k;
		while ((k = config.next()))
		{
			if (!k.isDirectBelow(root)) throw "Factory: key for configuration is not direct below";

			kdb::KeySet cks(config.cut(k));
			m_factory.insert(std::make_pair(k.getBaseName(), new StructInstancer(cks)));
		}
	}