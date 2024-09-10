GIT_INLINE(uint32_t) decode32(void *b)
{
	return ntohl(*((uint32_t *)b));
}