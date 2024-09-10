static int ParseSizeString(const char *size, double *res)
{
#define MAX_SUBSTRINGS 30
    int pcre_exec_ret;
    int r;
    int ov[MAX_SUBSTRINGS];
    int retval = 0;
    char str[128];
    char str2[128];

    *res = 0;

    pcre_exec_ret = pcre_exec(parse_regex, parse_regex_study, size, strlen(size), 0, 0,
                    ov, MAX_SUBSTRINGS);
    if (!(pcre_exec_ret == 2 || pcre_exec_ret == 3)) {
        SCLogError(SC_ERR_PCRE_MATCH, "invalid size argument - %s. Valid size "
                   "argument should be in the format - \n"
                   "xxx <- indicates it is just bytes\n"
                   "xxxkb or xxxKb or xxxKB or xxxkB <- indicates kilobytes\n"
                   "xxxmb or xxxMb or xxxMB or xxxmB <- indicates megabytes\n"
                   "xxxgb or xxxGb or xxxGB or xxxgB <- indicates gigabytes.\n",
                   size);
        retval = -2;
        goto end;
    }

    r = pcre_copy_substring((char *)size, ov, MAX_SUBSTRINGS, 1,
                             str, sizeof(str));
    if (r < 0) {
        SCLogError(SC_ERR_PCRE_GET_SUBSTRING, "pcre_copy_substring failed");
        retval = -2;
        goto end;
    }

    char *endptr, *str_ptr = str;
    errno = 0;
    *res = strtod(str_ptr, &endptr);
    if (errno == ERANGE) {
        SCLogError(SC_ERR_NUMERIC_VALUE_ERANGE, "Numeric value out of range");
        retval = -1;
        goto end;
    } else if (endptr == str_ptr) {
        SCLogError(SC_ERR_INVALID_NUMERIC_VALUE, "Invalid numeric value");
        retval = -1;
        goto end;
    }

    if (pcre_exec_ret == 3) {
        r = pcre_copy_substring((char *)size, ov, MAX_SUBSTRINGS, 2,
                                 str2, sizeof(str2));
        if (r < 0) {
            SCLogError(SC_ERR_PCRE_GET_SUBSTRING, "pcre_copy_substring failed");
            retval = -2;
            goto end;
        }

        if (strcasecmp(str2, "kb") == 0) {
            *res *= 1024;
        } else if (strcasecmp(str2, "mb") == 0) {
            *res *= 1024 * 1024;
        } else if (strcasecmp(str2, "gb") == 0) {
            *res *= 1024 * 1024 * 1024;
        } else {
            /* not possible */
            BUG_ON(1);
        }
    }

    retval = 0;
end:
    return retval;
}