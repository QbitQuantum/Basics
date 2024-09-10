void fft16(FFTComplex *z)
{
    fft8(z);
    fft4(z+8);
    fft4(z+12);

    TRANSFORM_ZERO(z,4);
    z+=2;
    TRANSFORM_EQUAL(z,4);
    z-=1;
    TRANSFORM(z,4,cPI1_8,cPI3_8);
    z+=2;
    TRANSFORM(z,4,cPI3_8,cPI1_8);
}