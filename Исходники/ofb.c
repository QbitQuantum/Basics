void akmos_ofb_encrypt(akmos_cipher_t ctx, const uint8_t *in_blk, size_t in_len, uint8_t *out_blk)
{
    akmos_ofb_t *ptr;
    size_t i, j, n, blklen;

    ptr = &ctx->mctx.ofb;
    blklen = ctx->xalgo->desc.blklen;

    n = (in_len / ctx->xalgo->desc.blklen);

    for(i = 0; i < n; i++, in_blk += blklen, out_blk += blklen) {
        ctx->encrypt(ctx, ptr->iv, ptr->iv);

        ctx->pxor(in_blk, ptr->iv, out_blk);
    }

    n = in_len - (n * blklen);
    if(!n)
        return;

    ctx->encrypt(ctx, ptr->iv, ptr->iv);

    for(j = 0; j < n; j++)
        out_blk[j] = in_blk[j] ^ ptr->iv[j];
}