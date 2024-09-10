inline uint64_t rot64(uint64_t x, int s)
{
#ifdef _MSC_VER
	return _rotr64(x, s);
#else
	return (x >> s) | (x << (64 - s));
#endif
}