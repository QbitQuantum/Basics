GIT_INLINE(int) hash_cryptoapi_init(git_hash_ctx *ctx)
{
    if (ctx->ctx.cryptoapi.valid)
        CryptDestroyHash(ctx->ctx.cryptoapi.hash_handle);

    if (!CryptCreateHash(ctx->prov->prov.cryptoapi.handle, CALG_SHA1, 0, 0, &ctx->ctx.cryptoapi.hash_handle)) {
        ctx->ctx.cryptoapi.valid = 0;
        return -1;
    }

    ctx->ctx.cryptoapi.valid = 1;
    return 0;
}