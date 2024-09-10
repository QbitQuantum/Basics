longdouble strtold_dm(const char *p,char **endp)
{
        longdouble ldval;
        int exp;
        long long msdec,lsdec;
        unsigned long msscale;
        char dot,sign;
        int pow;
        int ndigits;
        const char *pinit = p;
        static char infinity[] = "infinity";
        static char nans[] = "nans";
        unsigned int old_cw;
        unsigned int old_status;

#if _WIN32 && __DMC__
        fenv_t flagp;
        fegetenv(&flagp);  /* Store all exceptions, and current status word */
        if (_8087)
        {
            // disable exceptions from occurring, set max precision, and round to nearest
#if __DMC__
            __asm
            {
                fstcw   word ptr old_cw
                mov     EAX,old_cw
                mov     ECX,EAX
                and     EAX,0xf0c0
                or      EAX,033fh
                mov     old_cw,EAX
                fldcw   word ptr old_cw
                mov     old_cw,ECX
            }
#else
            old_cw = _control87(_MCW_EM | _PC_64  | _RC_NEAR,
                                _MCW_EM | _MCW_PC | _MCW_RC);
#endif
        }
#endif

        while (isspace(*p))
            p++;
        sign = 0;                       /* indicating +                 */
        switch (*p)
        {       case '-':
                        sign++;
                        /* FALL-THROUGH */
                case '+':
                        p++;
        }
        ldval = 0.0;
        dot = 0;                        /* if decimal point has been seen */
        exp = 0;
        msdec = lsdec = 0;
        msscale = 1;
        ndigits = 0;

#if __DMC__
        switch (*p)
        {   case 'i':
            case 'I':
                if (memicmp(p,infinity,8) == 0)
                {   p += 8;
                    goto L4;
                }
                if (memicmp(p,infinity,3) == 0)         /* is it "inf"? */
                {   p += 3;
                L4:
                    ldval = HUGE_VAL;
                    goto L3;
                }
                break;
            case 'n':
            case 'N':
                if (memicmp(p,nans,4) == 0)             /* "nans"?      */
                {   p += 4;
                    ldval = NANS;
                    goto L5;
                }
                if (memicmp(p,nans,3) == 0)             /* "nan"?       */
                {   p += 3;
                    ldval = NAN;
                L5:
                    if (*p == '(')              /* if (n-char-sequence) */
                        goto Lerr;              /* invalid input        */
                    goto L3;
                }
        }
#endif

        if (*p == '0' && (p[1] == 'x' || p[1] == 'X'))
        {   int guard = 0;
            int anydigits = 0;

            p += 2;
            while (1)
            {   int i = *p;

                while (isxdigit(i))
                {
                    anydigits = 1;
                    i = isalpha(i) ? ((i & ~0x20) - ('A' - 10)) : i - '0';
                    if (ndigits < 16)
                    {
                        msdec = msdec * 16 + i;
                        if (msdec)
                            ndigits++;
                    }
                    else if (ndigits == 16)
                    {
                        while (msdec >= 0)
                        {
                            exp--;
                            msdec <<= 1;
                            i <<= 1;
                            if (i & 0x10)
                                msdec |= 1;
                        }
                        guard = i << 4;
                        ndigits++;
                        exp += 4;
                    }
                    else
                    {
                        guard |= i;
                        exp += 4;
                    }
                    exp -= dot;
                    i = *++p;
                }
#if _WIN32 && __DMC__
                if (i == *__locale_decpoint && !dot)
#else
                if (i == '.' && !dot)
#endif
                {       p++;
                        dot = 4;
                }
                else
                        break;
            }

            // Round up if (guard && (sticky || odd))
            if (guard & 0x80 && (guard & 0x7F || msdec & 1))
            {
                msdec++;
                if (msdec == 0)                 // overflow
                {   msdec = 0x8000000000000000LL;
                    exp++;
                }
            }

            if (anydigits == 0)         // if error (no digits seen)
                goto Lerr;
            if (*p == 'p' || *p == 'P')
            {
                char sexp;
                int e;

                sexp = 0;
                switch (*++p)
                {   case '-':    sexp++;
                    case '+':    p++;
                }
                ndigits = 0;
                e = 0;
                while (isdigit(*p))
                {
                    if (e < 0x7FFFFFFF / 10 - 10) // prevent integer overflow
                    {
                        e = e * 10 + *p - '0';
                    }
                    p++;
                    ndigits = 1;
                }
                exp += (sexp) ? -e : e;
                if (!ndigits)           // if no digits in exponent
                    goto Lerr;

                if (msdec)
                {
#if __DMC__
                    // The 8087 has no instruction to load an
                    // unsigned long long
                    if (msdec < 0)
                    {
                        *(long long *)&ldval = msdec;
                        ((unsigned short *)&ldval)[4] = 0x3FFF + 63;
                    }
                    else
                    {   // But does for a signed one
                        __asm
                        {
                            fild        qword ptr msdec
                            fstp        tbyte ptr ldval
                        }
                    }
#else
                    int e2 = 0x3FFF + 63;

                    // left justify mantissa
                    while (msdec >= 0)
                    {   msdec <<= 1;
                        e2--;
                    }

                    // Stuff mantissa directly into long double
                    *(long long *)&ldval = msdec;
                    ((unsigned short *)&ldval)[4] = e2;
#endif

#if 0
                    if (0)
                    {   int i;
                        printf("msdec = x%llx, ldval = %Lg\n", msdec, ldval);
                        for (i = 0; i < 5; i++)
                            printf("%04x ",((unsigned short *)&ldval)[i]);
                        printf("\n");
                        printf("%llx\n",ldval);
                    }
#endif
                    // Exponent is power of 2, not power of 10
#if _WIN32 && __DMC__
                    __asm
                    {
                        fild    dword ptr exp
                        fld     tbyte ptr ldval
                        fscale                  // ST(0) = ST(0) * (2**ST(1))
                        fstp    ST(1)
                        fstp    tbyte ptr ldval
                    }
#else
                    ldval = ldexpl(ldval,exp);
#endif
                }
                goto L6;
            }