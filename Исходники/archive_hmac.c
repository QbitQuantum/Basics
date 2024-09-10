static void
__hmac_sha1_final(archive_hmac_sha1_ctx *ctx, uint8_t *out, size_t *out_len)
{
	BCryptFinishHash(ctx->hHash, ctx->hash, ctx->hash_len, 0);
	if (ctx->hash_len == *out_len)
		memcpy(out, ctx->hash, *out_len);
}