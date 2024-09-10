static intptr_t ReadBE32(intptr_t base, size_t* length, uint32_t* value)
{
	if((!length) | (!value)) throw Exception(E_POINTER);
	if(*length < sizeof(uint32_t)) throw Exception(E_DECOMPRESS_TRUNCATED, COMPRESSION_METHOD);

	*value = _byteswap_ulong(*reinterpret_cast<uint32_t*>(base));

	*length -= sizeof(uint32_t);
	return base + sizeof(uint32_t);
}