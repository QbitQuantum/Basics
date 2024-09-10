/*
 *   Random numbers 
 */
void os_gen_rand_bytes(unsigned char *buf, size_t len)
{
    /* make sure we have a crypto context */
    init_crypto_ctx();

    /* generate bytes via the system crypto API */
    CryptGenRandom(oswin_hcp, len, buf);
}