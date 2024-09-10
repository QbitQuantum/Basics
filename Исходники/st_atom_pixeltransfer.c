static void
make_state_key(GLcontext *ctx,  struct state_key *key)
{
   static const GLfloat zero[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
   static const GLfloat one[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

   memset(key, 0, sizeof(*key));

   if (ctx->Pixel.RedBias != 0.0 || ctx->Pixel.RedScale != 1.0 ||
       ctx->Pixel.GreenBias != 0.0 || ctx->Pixel.GreenScale != 1.0 ||
       ctx->Pixel.BlueBias != 0.0 || ctx->Pixel.BlueScale != 1.0 ||
       ctx->Pixel.AlphaBias != 0.0 || ctx->Pixel.AlphaScale != 1.0) {
      key->scaleAndBias = 1;
   }

   if (!is_identity(ctx->ColorMatrixStack.Top->m)) {
      key->colorMatrix = 1;
   }

   if (!TEST_EQ_4V(ctx->Pixel.PostColorMatrixScale, one) ||
       !TEST_EQ_4V(ctx->Pixel.PostColorMatrixBias, zero)) {
      key->colorMatrixPostScaleBias = 1;
   }

   key->pixelMaps = ctx->Pixel.MapColorFlag;
}