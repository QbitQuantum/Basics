long double en_entropy_ld(enctx * ctx)
{
   long double probs[256], acc = 0;
   int i;

   if (!ctx)
      return 0;

   if (ctx->len == 0)
      return 0;

   for (i = 0; i < 256; i++)
      probs[i] = ((long double) ctx->state[i]) / ((long double) ctx->len);

   for (i = 0; i < 256; i++)
      if (probs[i] != 0)
         acc += probs[i] * log2l(probs[i]);

   return -acc;
}