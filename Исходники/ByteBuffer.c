/* Get the long long in the correct byte order */
static long long byteSwapLongLong(PBYTE_BUFFER buff, long long l) {
	if (buff->byteOrder == BYTE_ORDER_BIG) {
		return HTONLL(l);
	}
	else {
		return l;
	}
}