	void check(kdb::KeySet &ks) override
	{
		config.rewind();

		kdb::Key confRoot = config.next();
		if (!confRoot) throw "StructChecker: No confRoot found";

		kdb::Key cur;
		kdb::Key root = ks.next();
		if (!root) throw "StructChecker: No root key found";


		while ((cur = ks.next()))
		{
			kdb::Key searchKey = config.next();
			if (!searchKey) throw "StructChecker: More keys found than structure should have";
			if (!cur.isDirectBelow(root)) throw "StructChecker: key is not direct below";

			if (searchKey.getBaseName() != cur.getBaseName())
				throw "StructChecker: did not find expected subkey";

			cur.copyAllMeta (searchKey);
		}

		if (config.next()) throw "StructChecker: There should be more elements in the structure";
	}