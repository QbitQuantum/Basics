static void SHA256_Update(SHA256_CTX *ctx,
                          const unsigned char *input,
                          unsigned int inputLen)
{
  CryptHashData(ctx->hHash, (unsigned char *)input, inputLen, 0);
}