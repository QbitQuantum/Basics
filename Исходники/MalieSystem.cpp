typedef struct {
	s8 magic[13];		// "MalieScenario"
} mls_header_t;
#pragma pack ()

static int is_libu, is_encryption;

static unsigned int keyTable[CAMELLIA_TABLE_WORD_LEN];

static void rotate16bytes(u32 offset, DWORD *cipher)
{
	BYTE shifts = ((offset >> 4) & 0x0f) + 16;

	cipher[0] = _lrotl(cipher[0], shifts);
	cipher[1] = _lrotr(cipher[1], shifts);
	cipher[2] = _lrotl(cipher[2], shifts);
	cipher[3] = _lrotr(cipher[3], shifts);
}

static void *memstr(void *_dst, int len, char *src)
{
	BYTE *dst = (BYTE *)_dst;
	for (int i = 0; i < len; ++i) {
		for (int k = 0; src[k]; ++k) {
			if (dst[i + k] != src[k])
				break;
		}
		if (!src[k])
			break;
	}