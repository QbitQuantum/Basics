	std::vector<uint8_t> decompress(const std::vector<uint8_t>& data)
	{
		return decompress(&data[0], data.size());
	}