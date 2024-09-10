int main( void )
{
    const int bits_per_float = 24;
    const int mantissa_size = 52;
    const int bias = 1023;
    int currentp = -1;          //-1 is 2/pi, -2 would be 1/pi
    int nextp = currentp - 1;
    int offset = 0;
    uint64_t    mantissa = 0;
    int i, bit;
    union
    {
        uint64_t    u;
        double      d;
    }value, exponent, startExp, expstep;
    long double v = 0;
    long double test = 2.0L/3.14159265358979323846264338327950288L;
    
    startExp.u = mantissa_size + currentp - bits_per_float;                 
    expstep.u = bias - bits_per_float;
    startExp.u += bias;
    startExp.u <<= mantissa_size;                                           
    expstep.u <<= mantissa_size;
//    startExp.u &= 0x7ff0000000000000ULL;        
    startExp.u = 5;  // stick a simple constant in there for gdb testing -- jsm
    expstep.u &= 0x7ff0000000000000ULL; /* put a breakpoint here */
    
    while( currentp + bias > 0 )
    {
        //set up exponent
        value.u = 0;
        for( i = 0; i < bits_per_float; i++ )
        {
            bit = get_bit( offset++ );
            if( bit < 0 )
                goto exit;

            value.u = value.u << 1;
            value.u |= bit;
            nextp--;
        }
        value.u |= startExp.u;
        value.d -= startExp.d;
        v += value.d;
        printf( "0x1.%13.13llxp%d, //%17.21g  (%17.21g, %17.21g, %17.21g) %17.21g\n", value.u & 0x000FFFFFFFFFFFFFULL, ilogb(value.d), value.d, (double) test, (double) v, (double) (test - v), expstep.d );

        startExp.d *= expstep.d;
    }

exit:

    return 0;
}