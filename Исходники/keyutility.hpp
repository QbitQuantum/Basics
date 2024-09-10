	static inline uint64_t Translate(std::string key)
	{
		return Hash64(key.c_str(), key.length());
	}