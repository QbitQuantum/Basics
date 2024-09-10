static int
w32crypto_bytes(unsigned char *outdata, int size)
{
    if (CryptGenRandom(_hc_CryptProvider(), size, outdata))
	return 1;
    return 0;
}