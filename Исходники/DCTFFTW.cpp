void DCTFFTW::Float2Bytes (uint8_t * dstp8, int dst_pitch, float * realdata)
{
    PixelType *dstp = (PixelType *)dstp8;

    dst_pitch /= sizeof(PixelType);

    int pixelMax = (1 << bitsPerSample) - 1;
    int pixelHalf = 1 << (bitsPerSample - 1);

    int floatpitch = sizex;
    int i, j;
    int integ;
    float f = realdata[0]*0.5f; // to be compatible with integer DCTINT8
    /*
       _asm fld f;
       _asm fistp integ;
       */
    // XXX function call to nearbyintf can be avoided by using cvtss2si
    integ = (int)(nearbyintf(f));
    dstp[0] = std::min(pixelMax, std::max(0, (integ>>dctshift0) + pixelHalf)); // DC
    for (i = 1; i < sizex; i+=1) {
        f = realdata[i]*0.707f; // to be compatible with integer DCTINT8
        /*
           _asm fld f;
           _asm fistp integ;
           */
        integ = (int)(nearbyintf(f));
        dstp[i] = std::min(pixelMax, std::max(0, (integ>>dctshift) + pixelHalf));
    }
    dstp += dst_pitch;
    realdata += floatpitch;
    for (j = 1; j < sizey; j++) {
        for (i = 0; i < sizex; i+=1) {
            f = realdata[i]*0.707f; // to be compatible with integer DCTINT8
            /*
               _asm fld f;
               _asm fistp integ;
               */
            integ = (int)(nearbyintf(f));
            dstp[i] = std::min(pixelMax, std::max(0, (integ>>dctshift) + pixelHalf));
        }
        dstp += dst_pitch;
        realdata += floatpitch;
    }
}