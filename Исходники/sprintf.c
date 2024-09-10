int32_t
u_sprintf_time_handler(u_localized_string *output,
                       const u_sprintf_spec_info     *info,
                       const ufmt_args         *args)
{
    UDate            num         = (UDate) (args[0].dateValue);
    UDateFormat        *format;
    UChar            result        [USPRINTF_BUFFER_SIZE];
    UErrorCode        status        = U_ZERO_ERROR;


    /* get the formatter */
    format = u_locbund_getTimeFormat(output->fBundle);

    /* handle error */
    if(format == 0)
        return 0;

    /* format the time */
    udat_format(format, num, result, USPRINTF_BUFFER_SIZE, 0, &status);

    return u_sprintf_pad_and_justify(output, info, result, u_strlen(result));
}