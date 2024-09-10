/*
 * Binary logarithm of value (exact if the value is a power of 2,
 * approximate (floored) otherwise)
 */
static matras_id_t
matras_log2(matras_id_t val)
{
	assert(val > 0);
#ifdef WIN32
	unsigned long res = 0;
	unsigned char nonzero = _BitScanReverse(&res, val);
	assert(nonzero); (void)nonzero;
	return (matras_id_t)res;
#else
	return sizeof(unsigned int) * CHAR_BIT -
		__builtin_clz((unsigned int) val) - 1;
#endif
}