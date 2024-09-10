/* Test exponential pattern*/
static void TestExponential(void)
{
    int32_t pat_length, val_length, lval_length;
    int32_t ival, ilval, p, v, lneed;
    UNumberFormat *fmt;
    int32_t ppos;
    UChar *upat;
    UChar pattern[20];
    UChar *str=NULL;
    UChar uvalfor[20], ulvalfor[20];
    char tempMsgBug[256];
    double a;
    UErrorCode status = U_ZERO_ERROR;
#if U_PLATFORM == U_PF_OS390
    static const double val[] = { 0.01234, 123456789, 1.23e75, -3.141592653e-78 };
#else
    static const double val[] = { 0.01234, 123456789, 1.23e300, -3.141592653e-271 };
#endif
    static const char* pat[] = { "0.####E0", "00.000E00", "##0.######E000", "0.###E0;[0.###E0]" };
    static const int32_t lval[] = { 0, -1, 1, 123456789 };

    static const char* valFormat[] =
    {
        "1.234E-2", "1.2346E8", "1.23E300", "-3.1416E-271",
        "12.340E-03", "12.346E07", "12.300E299", "-31.416E-272",
        "12.34E-003", "123.4568E006", "1.23E300", "-314.1593E-273",
        "1.234E-2", "1.235E8", "1.23E300", "[3.142E-271]"
    };
    static const char* lvalFormat[] =
    {
        "0E0", "-1E0", "1E0", "1.2346E8",
        "00.000E00", "-10.000E-01", "10.000E-01", "12.346E07",
        "0E000", "-1E000", "1E000", "123.4568E006",
        "0E0", "[1E0]", "1E0", "1.235E8"
    };
    static const double valParse[] =
    {
#if U_PLATFORM == U_PF_OS390
        0.01234, 123460000, 1.23E75, -3.1416E-78,
        0.01234, 123460000, 1.23E75, -3.1416E-78,
        0.01234, 123456800, 1.23E75, -3.141593E-78,
        0.01234, 123500000, 1.23E75, -3.142E-78
#else
        /* We define the whole IEEE 754 number in the 4th column because
        Visual Age 7 has a bug in rounding numbers. */
        0.01234, 123460000, 1.23E300, -3.1415999999999999E-271,
        0.01234, 123460000, 1.23E300, -3.1415999999999999E-271,
        0.01234, 123456800, 1.23E300, -3.1415929999999999E-271,
        0.01234, 123500000, 1.23E300, -3.1420000000000001E-271
#endif
    };
    static const int32_t lvalParse[] =
    {
        0, -1, 1, 123460000,
            0, -1, 1, 123460000,
            0, -1, 1, 123456800,
            0, -1, 1, 123500000
    };


    pat_length = UPRV_LENGTHOF(pat);
    val_length = UPRV_LENGTHOF(val);
    lval_length = UPRV_LENGTHOF(lval);
    ival = 0;
    ilval = 0;
    for (p=0; p < pat_length; ++p)
    {
        upat=(UChar*)malloc(sizeof(UChar) * (strlen(pat[p])+1) );
        u_uastrcpy(upat, pat[p]);
        fmt=unum_open(UNUM_IGNORE,upat, u_strlen(upat), "en_US",NULL, &status);
        if (U_FAILURE(status)) {
            log_err_status(status, "FAIL: Bad status returned by Number format construction with pattern %s -> %s\n", pat[p], u_errorName(status));
            continue;
        }
        lneed= u_strlen(upat) + 1;
        unum_toPattern(fmt, FALSE, pattern, lneed, &status);
        log_verbose("Pattern \" %s \" -toPattern-> \" %s \" \n", upat, u_austrcpy(tempMsgBug, pattern) );
        for (v=0; v<val_length; ++v)
        {
            /*format*/
            lneed=0;
            lneed=unum_formatDouble(fmt, val[v], NULL, lneed, NULL, &status);
            if(status==U_BUFFER_OVERFLOW_ERROR){
                status=U_ZERO_ERROR;
                str=(UChar*)malloc(sizeof(UChar) * (lneed+1) );
                unum_formatDouble(fmt, val[v], str, lneed+1,  NULL, &status);
            }
            if(U_FAILURE(status)) {
                log_err("Error in formatting using unum_format(.....): %s\n", myErrorName(status) );
            }



            u_uastrcpy(uvalfor, valFormat[v+ival]);
            if(u_strcmp(str, uvalfor) != 0)
                log_verbose("FAIL: Expected %s ( %s )\n", valFormat[v+ival], u_austrcpy(tempMsgBug, uvalfor) );

            /*parsing*/
            ppos=0;
            a=unum_parseDouble(fmt, str, u_strlen(str), &ppos, &status);
            if (ppos== u_strlen(str)) {
                if (a != valParse[v+ival])
                    log_err("FAIL: Expected: %e, Got: %g\n", valParse[v+ival], a);
            }
            else
                log_err(" FAIL: Partial parse (  %d  chars ) ->  %e\n",  ppos, a);

            free(str);
        }
        for (v=0; v<lval_length; ++v)
        {
            /*format*/
            lneed=0;
            lneed=unum_formatDouble(fmt, lval[v], NULL, lneed, NULL, &status);
            if(status==U_BUFFER_OVERFLOW_ERROR){
                status=U_ZERO_ERROR;
                str=(UChar*)malloc(sizeof(UChar) * (lneed+1) );
                unum_formatDouble(fmt, lval[v], str, lneed+1,  NULL, &status);
            }
            if(U_FAILURE(status)) {
                log_err("Error in formatting using unum_format(.....): %s\n", myErrorName(status) );
            }
            /*printf(" Format %e -> %s\n",  lval[v], austrdup(str) );*/
            u_uastrcpy(ulvalfor, lvalFormat[v+ilval]);
            if(u_strcmp(str, ulvalfor) != 0)
                log_err("FAIL: Expected %s ( %s )\n", valFormat[v+ilval], austrdup(ulvalfor) );

            /*parsing*/
            ppos=0;
            a=unum_parseDouble(fmt, str, u_strlen(str), &ppos, &status);
            if (ppos== u_strlen(str)) {
                /*printf(" Parse -> %e\n",  a);*/
                if (a != lvalParse[v+ilval])
                    log_err("FAIL: Expected : %e\n", valParse[v+ival]);
            }
            else
                log_err(" FAIL: Partial parse (  %d  chars ) ->  %e\n",  ppos, a);

            free(str);

        }
        ival += val_length;
        ilval += lval_length;
        unum_close(fmt);
        free(upat);
    }
}