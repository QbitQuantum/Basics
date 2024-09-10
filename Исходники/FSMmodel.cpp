	static bool createImage(string fileName, string extension) {
		extension = "-T" + extension;
		auto rv = _spawnlp(P_WAIT, "dot", "dot", extension.c_str(), "-O", fileName.c_str(), NULL);
		return (rv == 0);
	}