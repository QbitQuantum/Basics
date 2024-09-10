/*
 * Convert a floating point number in native format to TMS32032
 * floating point single precision (32 bit) format.  Note that the
 * TMS floating point value is returned as an unsigned integer.
 */
static unsigned int
float2tms32(float x)
{
    unsigned int zero = 0x80000000; /* Zero value is special case */
    int nfracbits = 23;    /* Not including hidden bit / sign bit */
    int signbit = 1 << nfracbits;
    int fracmask = ~((~0)<<nfracbits);
    int iexp;
    int sign;
    int ifrac;
    unsigned int rtn;

    if (x == 0){
        rtn = zero;
    }else{
        iexp = ilogb(x);  /* Binary exponent if 1 <= |fraction| < 2 */
        ifrac = (int)scalbn(x, nfracbits-iexp); /* Frac part as integer */
        if (x<0 && (ifrac & signbit)){
            /* Force top bit of negative fraction to be 0 */
            ifrac <<= 1;
            iexp--;
        }
        sign = x<0 ? signbit : 0;
        rtn = (iexp << (nfracbits+1)) | sign | (ifrac & fracmask);
    }
    return rtn;
}