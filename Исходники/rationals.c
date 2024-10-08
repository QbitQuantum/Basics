void
rationalize32 (float f,uint32_t *numerator,uint32_t *denominator)
{
    uint32_t i,j;
    // try x for 32 bit x
    j=1;
    i=nearbyintf(((float)j)*f);
    if (i==0){
        i=nearbyintf(1000000000*f);
        if (i==0){
            *numerator=0;
            *denominator=1;
            return;           
        }
    } else if (fequal(f,(float)i)){
        *numerator=i;
        *denominator=1;
        return;
    }
    // try x/y for 8 bit x,y
    for(j=2;j<256;j++){
        i=nearbyintf(((float)j)*f);
        if (i<=0 || i>=256) continue;
        if (fequal(f,((float)i)/((float)j))){
            *numerator=i;
            *denominator=j;
            return;
        }
    }
    // try 3(4??) digit decimal.
    for(j=1000;j<1000000000;j=j*10){
        i=nearbyintf(((float)j)*f);
        if (i<=100 || i>10000) continue;
        if (fequal(f,((float)i)/((float)j))){
            uint32_t c=gcd32(i,j);
            *numerator=i/c;
            *denominator=j/c;
            return;
        }
    }
    Abort("Attempt to reverse engineer %f failed",f);
}