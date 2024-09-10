void akmos_cbc_encrypt(akmos_cipher_t ctx, const uint8_t *in_blk, size_t in_len, uint8_t *out_blk)
{
    akmos_cbc_t *ptr;
    size_t i, nb, blklen;

    ptr = &ctx->mctx.cbc;
    blklen = ctx->xalgo->desc.blklen;

    nb = in_len / blklen;

    for(i = 0; i < nb; i++, in_blk += blklen, out_blk += blklen) {
        ctx->pxor(ptr->iv, in_blk, ptr->iv);

        ctx->encrypt(ctx, ptr->iv, out_blk);

        memcpy(ptr->iv, out_blk, blklen);
    }
}