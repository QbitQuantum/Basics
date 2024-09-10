int recv_block(int sockfd, decoder& dpack)
{
	dpack.reset();

	char* buf = dpack.buffer();

	size_t left = c_header_size;
	while (left)
	{
		int offset = c_header_size - left;
		int n = RECV(sockfd, buf + offset, left, 0);
		if (n <= 0)
		{
			return n;
		}
		left -= n;
		if (0 == left)
		{
			break;
		}
	}
	
	uint8_t version = dpack.version();
	uint8_t headsize = dpack.headsize();
	if (version != c_default_version || headsize != c_header_size)
	{
		printf("packet format error, version:%d, headsize:%d\n", version, headsize);
		return 0;
	}

	size_t bodyleft = dpack.length();
	if (bodyleft > (c_buffer_size - c_header_size))
	{
		printf("packet format error, bodylen:%lu\n", bodyleft);
		return 0;
	}

	size_t bodyoffset = c_header_size;
	while (bodyleft)
	{
		int n = RECV(sockfd, buf + bodyoffset, bodyleft, 0);
		if (n <= 0)
		{
			return n;
		}
		bodyleft -= n;
		bodyoffset += n;
		if (0 == bodyleft)
		{
			break;
		}
	}

	dpack.setsize(dpack.length() + c_header_size);
	return dpack.size();
}