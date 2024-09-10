static void fft16(FFTComplex *z)
{
    FFTSample t1, t2, t3, t4, t5, t6;

    fft8(z);
    fft4(z+8);
    fft4(z+12);

    TRANSFORM_ZERO(z[0],z[4],z[8],z[12]);
    TRANSFORM(z[2],z[6],z[10],z[14],sqrthalf,sqrthalf);
    TRANSFORM(z[1],z[5],z[9],z[13],ff_cos_16[1],ff_cos_16[3]);
    TRANSFORM(z[3],z[7],z[11],z[15],ff_cos_16[3],ff_cos_16[1]);
}