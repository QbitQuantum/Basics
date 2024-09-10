static apr_size_t win32_strftime_extra(char *s, size_t max, const char *format,
                                       const struct tm *tm) 
{
   /* If the new format string is bigger than max, the result string won't fit
    * anyway. If format strings are added, made sure the padding below is
    * enough */
    char *new_format = (char *) malloc(max + 11);
    size_t i, j, format_length = strlen(format);
    apr_size_t return_value;
    int length_written;

    for (i = 0, j = 0; (i < format_length && j < max);) {
        if (format[i] != '%') {
            new_format[j++] = format[i++];
            continue;
        }
        switch (format[i+1]) {
            case 'C':
                length_written = apr_snprintf(new_format + j, max - j, "%2d",
                    (tm->tm_year + 1970)/100);
                j = (length_written == -1) ? max : (j + length_written);
                i += 2;
                break;
            case 'D':
                /* Is this locale dependent? Shouldn't be...
                   Also note the year 2000 exposure here */
                memcpy(new_format + j, "%m/%d/%y", 8);
                i += 2;
                j += 8;
                break;
            case 'r':
                memcpy(new_format + j, "%I:%M:%S %p", 11);
                i += 2;
                j += 11;
                break;
            case 'R':
                memcpy(new_format + j, "%H:%M", 5);
                i += 2;
                j += 5;
                break;
            case 'T':
                memcpy(new_format + j, "%H:%M:%S", 8);
                i += 2;
                j += 8;
                break;
            case 'e':
                length_written = apr_snprintf(new_format + j, max - j, "%2d",
                    tm->tm_mday);
                j = (length_written == -1) ? max : (j + length_written);
                i += 2;
                break;
            default:
                /* We know we can advance two characters forward here. Also
                 * makes sure that %% is preserved. */
                new_format[j++] = format[i++];
                new_format[j++] = format[i++];
        }
    }
    if (j >= max) {
        *s = '\0';  /* Defensive programming, okay since output is undefined*/
        return_value = 0;
    } else {
        new_format[j] = '\0';
        return_value = strftime(s, max, new_format, tm);
    }
    free(new_format);
    return return_value;
}