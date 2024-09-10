static inline const char *
parse_format(const char *s, char *format, int *len)
{
    grub_bool done = FALSE;
    grub_bool allowminus = FALSE;
    grub_bool dot = FALSE;
    grub_bool err = FALSE;
    char *fmt = format;
    int prec = 0;
    int width = 0;
    int value = 0;

    *len = 0;
    *format++ = '%';
    while (*s != '\0' && !done) {
	switch (*s) {
	case 'c':		/* FALLTHRU */
	case 'd':		/* FALLTHRU */
	case 'o':		/* FALLTHRU */
	case 'x':		/* FALLTHRU */
	case 'X':		/* FALLTHRU */
	case 's':
	    *format++ = *s;
	    done = TRUE;
	    break;
	case '.':
	    *format++ = *s++;
	    if (dot) {
		err = TRUE;
	    } else {
		dot = TRUE;
		prec = value;
	    }
	    value = 0;
	    break;
	case '#':
	    *format++ = *s++;
	    break;
	case ' ':
	    *format++ = *s++;
	    break;
	case ':':
	    s++;
	    allowminus = TRUE;
	    break;
	case '-':
	    if (allowminus) {
		*format++ = *s++;
	    } else {
		done = TRUE;
	    }
	    break;
	default:
	    if (isdigit(*s)) {
		value = (value * 10) + (*s - '0');
		if (value > 10000)
		    err = TRUE;
		*format++ = *s++;
	    } else {
		done = TRUE;
	    }
	}
    }

    /*
     * If we found an error, ignore (and remove) the flags.
     */
    if (err) {
	prec = width = value = 0;
	format = fmt;
	*format++ = '%';
	*format++ = *s;
    }

    if (dot)
	width = value;
    else
	prec = value;

    *format = '\0';
    /* return maximum string length in print */
    *len = (prec > width) ? prec : width;
    return s;
}