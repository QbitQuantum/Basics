static int32_t
u_scanf_scientific_handler(UFILE        *input,
                           u_scanf_spec_info *info,
                           ufmt_args    *args,
                           const UChar  *fmt,
                           int32_t      *fmtConsumed,
                           int32_t      *argConverted)
{
    int32_t         len;
    double          num;
    UNumberFormat   *format;
    int32_t         parsePos    = 0;
    int32_t         skipped;
    UErrorCode      status      = U_ZERO_ERROR;
    UChar srcExpBuf[UPRINTF_SYMBOL_BUFFER_SIZE];
    int32_t srcLen, expLen;
    UChar expBuf[UPRINTF_SYMBOL_BUFFER_SIZE];


    /* skip all ws in the input */
    skipped = u_scanf_skip_leading_ws(input, info->fPadChar);

    /* fill the input's internal buffer */
    ufile_fill_uchar_buffer(input);

    /* determine the size of the input's buffer */
    len = (int32_t)(input->str.fLimit - input->str.fPos);

    /* truncate to the width, if specified */
    if(info->fWidth != -1)
        len = ufmt_min(len, info->fWidth);

    /* get the formatter */
    format = u_locbund_getNumberFormat(&input->str.fBundle, UNUM_SCIENTIFIC);

    /* handle error */
    if(format == 0)
        return 0;

    /* set the appropriate flags on the formatter */

    srcLen = unum_getSymbol(format,
        UNUM_EXPONENTIAL_SYMBOL,
        srcExpBuf,
        sizeof(srcExpBuf),
        &status);

    /* Upper/lower case the e */
    if (info->fSpec == (UChar)0x65 /* e */) {
        expLen = u_strToLower(expBuf, (int32_t)sizeof(expBuf),
            srcExpBuf, srcLen,
            input->str.fBundle.fLocale,
            &status);
    }
    else {
        expLen = u_strToUpper(expBuf, (int32_t)sizeof(expBuf),
            srcExpBuf, srcLen,
            input->str.fBundle.fLocale,
            &status);
    }

    unum_setSymbol(format,
        UNUM_EXPONENTIAL_SYMBOL,
        expBuf,
        expLen,
        &status);




    /* Skip the positive prefix. ICU normally can't handle this due to strict parsing. */
    skipped += u_scanf_skip_leading_positive_sign(input, format, &status);

    /* parse the number */
    num = unum_parseDouble(format, input->str.fPos, len, &parsePos, &status);

    if (!info->fSkipArg) {
        if (info->fIsLong)
            *(double*)(args[0].ptrValue) = num;
        else if (info->fIsLongDouble)
            *(long double*)(args[0].ptrValue) = num;
        else
            *(float*)(args[0].ptrValue) = (float)num;
    }

    /* mask off any necessary bits */
    /*  if(! info->fIsLong_double)
    num &= DBL_MAX;*/

    /* update the input's position to reflect consumed data */
    input->str.fPos += parsePos;

    /* we converted 1 arg */
    *argConverted = !info->fSkipArg;
    return parsePos + skipped;
}