/*!
 * \brief Parse RFC date and time string.
 *
 * This routine accepts RFC 850, RFC 1123 and asctime time formats.
 *
 * \param str Pointer to the date and time string.
 *
 * \return Number of seconds since epoch or -1 in case of any error.
 */
time_t RfcTimeParse(CONST char *str)
{
    struct _tm dts = { 0, 0, 0, 1, 0, 0, 0, 0, 0 };

    /* Skip leading whitespace. */
    str = skip_spaces(str);

    /* Skip weekday, optional in RFC 822. */
    if (isalpha((unsigned char)*str)) {
        while (*str && *str != ' ' && *str != '\t')
            str++;
        str = skip_spaces(str);
    }

    if (isalpha((unsigned char)*str)) {
        /* asctime format 'Fri Feb 2 2007 07:30:05'. */
        str = TimeParseMonth(str, &dts.tm_mon);
        str = skip_spaces(str);
        str = parse_digits(str, &dts.tm_mday);
        str = skip_spaces(str);
        str = TimeParseYear(str, &dts.tm_year);
        str = skip_spaces(str);
        str = TimeParseHms(str, &dts.tm_hour, &dts.tm_min, &dts.tm_sec);
    }
    else if (*str) {
        /* RFC 850 'Friday, 02-Feb-2007 07:30:05 GMT'. */
        /* RFC 1123 'Fri, 02 Feb 2007 07:30:05 GMT'. */
        str = TimeParseDmy(str, &dts.tm_mday, &dts.tm_mon, &dts.tm_year);
        str = skip_spaces(str);
        str = TimeParseHms(str, &dts.tm_hour, &dts.tm_min, &dts.tm_sec);
    }
    str = skip_spaces(str);
    if (    (strcmp(str, "GMT") == 0)
         || (strcmp(str, "UTC") == 0)
       )
    {
        return mktime(&dts);
    }
    return _mkgmtime(&dts);
}