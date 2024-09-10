	bool BufferHelper::WriteFixUInt64(Buffer& buffer, uint64_t i,
			bool toNetwork)
	{
		if (toNetwork)
		{
			i = htonll(i);
		}
		return sizeof(uint64_t) == buffer.Write(&i, sizeof(uint64_t));
	}