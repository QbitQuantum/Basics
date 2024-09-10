uint32 StreamSource::calcCrc32()
{
	ulong crc = crc32(0L, Z_NULL, 0);

	Ref<StreamReader> r = open();

	uint8 buf[4096];

	while (true)
	{
		size_t bytesRead = r->readRaw(buf, sizeof(buf));
		if (bytesRead == 0) break;
		crc = crc32(crc, buf, bytesRead);
	}

	return crc;
}