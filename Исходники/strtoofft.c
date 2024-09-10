/**
 * Emulated version of the strtoll function.  This extracts a long long
 * value from the given input string and returns it.
 */
curl_off_t
curlx_strtoll(const char *nptr, char **endptr, int base)
{
    char       *end;
    int        is_negative = 0;
    int        overflow;
    int        i;
    curl_off_t value = 0;
    curl_off_t newval;

    /* Skip leading whitespace. */
    end = (char*)nptr;

    while (ISSPACE(end[0]))
    {
        end++;
    }

    /* Handle the sign, if any. */
    if (end[0] == '-')
    {
        is_negative = 1;
        end++;
    }
    else if (end[0] == '+')
    {
        end++;
    }
    else if (end[0] == '\0')
    {
        /* We had nothing but perhaps some whitespace -- there was no number. */
        if (endptr)
        {
            *endptr = end;
        }

        return 0;
    }

    /* Handle special beginnings, if present and allowed. */
    if (end[0] == '0' && end[1] == 'x')
    {
        if (base == 16 || base == 0)
        {
            end += 2;
            base = 16;
        }
    }
    else if (end[0] == '0')
    {
        if (base == 8 || base == 0)
        {
            end++;
            base = 8;
        }
    }

    /* Matching strtol, if the base is 0 and it doesn't look like
     * the number is octal or hex, we assume it's base 10.
     */
    if (base == 0)
    {
        base = 10;
    }

    /* Loop handling digits. */
    value    = 0;
    overflow = 0;

    for (i = get_char(end[0], base);
         i != -1;
         end++, i = get_char(end[0], base))
    {
        newval = base * value + i;
        if (newval < value)
        {
            /* We've overflowed. */
            overflow = 1;
            break;
        }
        else
            value = newval;
    }

    if (!overflow)
    {
        if (is_negative)
        {
            /* Fix the sign. */
            value *= -1;
        }
    }
    else
    {
        if (is_negative)
            value = CURL_LLONG_MIN;
        else
            value = CURL_LLONG_MAX;

        SET_ERRNO(ERANGE);
    }

    if (endptr)
        *endptr = end;

    return value;
}