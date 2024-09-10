void *CTsPacket::ReAllocate(void *pBuffer, size_t Size)
{
	return _aligned_offset_realloc(pBuffer, Size, 16, 4);
}