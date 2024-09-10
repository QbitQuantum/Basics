struct mesa_sha1 *
_mesa_sha1_init(void)
{
    HCRYPTHASH *ctx = malloc(sizeof(*ctx));

    if (!ctx)
        return NULL;

    CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
    CryptCreateHash(hProv, CALG_SHA1, 0, 0, ctx);
    return (struct mesa_sha1 *) ctx;
}