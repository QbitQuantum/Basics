static int __inline rd_ctz64(u64 x) {
#ifdef _M_X64
	int r = 0;
	if (_BitScanReverse64(&r, x))
		return r;
	else
		return 64;
#else
	int r;
	if ((r = rd_ctz(x & 0xffffffff)) < 32)
		return r;
	return 32 + rd_ctz(x >> 32);
#endif
}