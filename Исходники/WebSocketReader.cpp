ByteBuffer WebSocketReader::load(Buffer_Type* buffer, int bytes_transferred)
{
	ByteBuffer b;
	if (!buffer)
	{
		return b;
	}
	Buffer_Type::iterator curIt = buffer->begin();
	Buffer_Type::iterator curEnd = buffer->begin() + bytes_transferred;
	while (curIt != curEnd)
	{
		b.putChar(*curIt);
		curIt++;
	}

	return b;
}