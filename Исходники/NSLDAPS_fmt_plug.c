/*
 * These two were found in john-1.6-nsldaps4.diff.gz and apparently they were
 * supported by that version of they code, but they are not anymore.
 */
  {"{SSHA}/EExmSfmhQSPHDJaTxwQSdb/uPpzYWx0ZXI=", "secret"},
  {"{SSHA}gVK8WC9YyFT1gMsQHTGCgT3sSv5zYWx0", "secret"},
#endif
  {NULL}
};

#ifdef MMX_COEF
/* Cygwin would not guarantee the alignment if these were declared static */
#define buffer NSLDAPS_buffer
#define crypt_key NSLDAPS_crypt_key
#ifdef _MSC_VER
__declspec(align(16)) unsigned char buffer[80*4*MMX_COEF];
__declspec(align(16)) char crypt_key[BINARY_SIZE*MMX_COEF];
#else
unsigned char buffer[80*4*MMX_COEF] __attribute__ ((aligned(16)));
char crypt_key[BINARY_SIZE*MMX_COEF] __attribute__ ((aligned(16)));
#endif
static char saved_key[(PLAINTEXT_LENGTH+SALT_SIZE+4+1)*MMX_COEF];
static unsigned long total_len;
static unsigned char out[PLAINTEXT_LENGTH + 1];
#else
static ARCH_WORD_32 crypt_key[BINARY_SIZE / 4];
static char saved_key[PLAINTEXT_LENGTH + 1];
#endif

#ifdef MMX_COEF
static unsigned long length[MAX_KEYS_PER_CRYPT];