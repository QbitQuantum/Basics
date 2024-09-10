int xcrush_compute_chunks(XCRUSH_CONTEXT* xcrush, BYTE* data, UINT32 size, UINT32* pIndex)
{
	UINT32 i = 0;
	UINT32 offset = 0;
	UINT32 rotation = 0;
	UINT32 accumulator = 0;

	*pIndex = 0;
	xcrush->SignatureIndex = 0;

	if (size < 128)
		return 0;

	for (i = 0; i < 32; i++)
	{
		rotation = _rotl(accumulator, 1);
		accumulator = data[i] ^ rotation;
	}

	for (i = 0; i < size - 64; i++)
	{
		rotation = _rotl(accumulator, 1);
		accumulator = data[i + 32] ^ data[i] ^ rotation;

		if (!(accumulator & 0x7F))
		{
			if (!xcrush_append_chunk(xcrush, data, &offset, i + 32))
				return 0;
		}
		i++;

		rotation = _rotl(accumulator, 1);
		accumulator = data[i + 32] ^ data[i] ^ rotation;

		if (!(accumulator & 0x7F))
		{
			if (!xcrush_append_chunk(xcrush, data, &offset, i + 32))
				return 0;
		}
		i++;

		rotation = _rotl(accumulator, 1);
		accumulator = data[i + 32] ^ data[i] ^ rotation;

		if (!(accumulator & 0x7F))
		{
			if (!xcrush_append_chunk(xcrush, data, &offset, i + 32))
				return 0;
		}
		i++;

		rotation = _rotl(accumulator, 1);
		accumulator = data[i + 32] ^ data[i] ^ rotation;

		if (!(accumulator & 0x7F))
		{
			if (!xcrush_append_chunk(xcrush, data, &offset, i + 32))
				return 0;
		}
	}

	if ((size == offset) || xcrush_append_chunk(xcrush, data, &offset, size))
	{
		*pIndex = xcrush->SignatureIndex;
		return 1;
	}

	return 0;
}