static void blowfish_decrypt(word32 xL, word32 xR, word32 * output,
                             BlowfishContext * ctx)
{
    word32 *S0 = ctx->S0;
    word32 *S1 = ctx->S1;
    word32 *S2 = ctx->S2;
    word32 *S3 = ctx->S3;
    word32 *P = ctx->P;
    word32 t;

    ROUND(17);
    ROUND(16);
    ROUND(15);
    ROUND(14);
    ROUND(13);
    ROUND(12);
    ROUND(11);
    ROUND(10);
    ROUND(9);
    ROUND(8);
    ROUND(7);
    ROUND(6);
    ROUND(5);
    ROUND(4);
    ROUND(3);
    ROUND(2);
    xL ^= P[1];
    xR ^= P[0];

    output[0] = xR;
    output[1] = xL;
}