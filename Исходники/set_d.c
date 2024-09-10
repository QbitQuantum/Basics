choke me
#endif

void
mpq_set_d (mpq_ptr dest, double d)
{
    int negative;
    mp_exp_t exp;
    mp_limb_t tp[LIMBS_PER_DOUBLE];
    mp_ptr np, dp;
    mp_size_t nn, dn;
    int c;

    DOUBLE_NAN_INF_ACTION (d,
                           __gmp_invalid_operation (),
                           __gmp_invalid_operation ());

    negative = d < 0;
    d = ABS (d);

    exp = __gmp_extract_double (tp, d);

    /* There are two main version of the conversion.  The `then' arm handles
       numbers with a fractional part, while the `else' arm handles integers.  */
#if LIMBS_PER_DOUBLE == 4
    if (exp <= 1 || (exp == 2 && (tp[0] | tp[1]) != 0))
#endif
#if LIMBS_PER_DOUBLE == 3
        if (exp <= 1 || (exp == 2 && tp[0] != 0))
#endif
#if LIMBS_PER_DOUBLE == 2
            if (exp <= 1)
#endif
            {
                if (d == 0.0)
                {
                    SIZ(NUM(dest)) = 0;
                    SIZ(DEN(dest)) = 1;
                    PTR(DEN(dest))[0] = 1;
                    return;
                }

                dn = -exp;
                np = MPZ_NEWALLOC (NUM(dest), 3);
#if LIMBS_PER_DOUBLE == 4
                if ((tp[0] | tp[1] | tp[2]) == 0)
                    np[0] = tp[3], nn = 1;
                else if ((tp[0] | tp[1]) == 0)
                    np[1] = tp[3], np[0] = tp[2], nn = 2;
                else if (tp[0] == 0)
                    np[2] = tp[3], np[1] = tp[2], np[0] = tp[1], nn = 3;
                else
                    np[3] = tp[3], np[2] = tp[2], np[1] = tp[1], np[0] = tp[0], nn = 4;
#endif
#if LIMBS_PER_DOUBLE == 3
                if ((tp[0] | tp[1]) == 0)
                    np[0] = tp[2], nn = 1;
                else if (tp[0] == 0)
                    np[1] = tp[2], np[0] = tp[1], nn = 2;
                else
                    np[2] = tp[2], np[1] = tp[1], np[0] = tp[0], nn = 3;
#endif
#if LIMBS_PER_DOUBLE == 2
                if (tp[0] == 0)
                    np[0] = tp[1], nn = 1;
                else
                    np[1] = tp[1], np[0] = tp[0], nn = 2;
#endif
                dn += nn + 1;
                ASSERT_ALWAYS (dn > 0);
                dp = MPZ_NEWALLOC (DEN(dest), dn);
                MPN_ZERO (dp, dn - 1);
                dp[dn - 1] = 1;
                count_trailing_zeros (c, np[0] | dp[0]);
                if (c != 0)
                {
                    mpn_rshift (np, np, nn, c);
                    nn -= np[nn - 1] == 0;
                    mpn_rshift (dp, dp, dn, c);
                    dn -= dp[dn - 1] == 0;
                }
                SIZ(DEN(dest)) = dn;
                SIZ(NUM(dest)) = negative ? -nn : nn;
            }
            else
            {
                nn = exp;
                np = MPZ_NEWALLOC (NUM(dest), nn);
                switch (nn)
                {
                default:
                    MPN_ZERO (np, nn - LIMBS_PER_DOUBLE);
                    np += nn - LIMBS_PER_DOUBLE;
                    /* fall through */
#if LIMBS_PER_DOUBLE == 2
                case 2:
                    np[1] = tp[1], np[0] = tp[0];
                    break;
#endif
#if LIMBS_PER_DOUBLE == 3
                case 3:
                    np[2] = tp[2], np[1] = tp[1], np[0] = tp[0];
                    break;
                case 2:
                    np[1] = tp[2], np[0] = tp[1];
                    break;
#endif
#if LIMBS_PER_DOUBLE == 4
                case 4:
                    np[3] = tp[3], np[2] = tp[2], np[1] = tp[1], np[0] = tp[0];
                    break;
                case 3:
                    np[2] = tp[3], np[1] = tp[2], np[0] = tp[1];
                    break;
                case 2:
                    np[1] = tp[3], np[0] = tp[2];
                    break;
#endif
                }
                dp = PTR(DEN(dest));
                dp[0] = 1;
                SIZ(DEN(dest)) = 1;
                SIZ(NUM(dest)) = negative ? -nn : nn;
            }
}