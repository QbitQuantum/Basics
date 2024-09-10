unsigned int CRC32C(unsigned int length, const unsigned char* value)
{
	unsigned int hash_value = 0;

	if (length == 1)
		return _mm_crc32_u8(hash_value, *value);

	if (length == 2)
		return _mm_crc32_u16(hash_value, *(unsigned short*) value);

	while (length >= 4)
	{
		hash_value = _mm_crc32_u32(hash_value, *(unsigned int*) value);
		value += 4;
		length -= 4;
	}

	if (length >= 2)
	{
		hash_value = _mm_crc32_u16(hash_value, *(unsigned short*) value);
		value += 2;
		length -= 2;
	}

	if (length)
	{
		hash_value = _mm_crc32_u8(hash_value, *value);
	}

	return hash_value;
}