targ_ldouble _modulo(targ_ldouble x, targ_ldouble y)
{
#if __DMC__
    short sw;

    __asm
    {
        fld     tbyte ptr y
        fld     tbyte ptr x             // ST = x, ST1 = y
FM1:    // We don't use fprem1 because for some inexplicable
        // reason we get -5 when we do _modulo(15, 10)
        fprem                           // ST = ST % ST1
        fstsw   word ptr sw
        fwait
        mov     AH,byte ptr sw+1        // get msb of status word in AH
        sahf                            // transfer to flags
        jp      FM1                     // continue till ST < ST1
        fstp    ST(1)                   // leave remainder on stack
    }
#elif __FreeBSD__ || __OpenBSD__ || __DragonFly__
    return fmod(x, y);
#else
    return fmodl(x, y);
#endif
}