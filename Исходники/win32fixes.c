double wstrtod(const char *nptr, char **eptr) {
    double d;
    char *leptr;
#if 0
    if (clocale == NULL)
        clocale = _create_locale(LC_ALL, "C");
#endif
    d = _strtod_l(nptr, &leptr, clocale);
    /* if 0, check if input was inf */
    if (d == 0 && nptr == leptr) {
        int neg = 0;
        while (isspace(*nptr))
            nptr++;
        if (*nptr == '+')
            nptr++;
        else if (*nptr == '-') {
            nptr++;
            neg = 1;
        }

        if (strnicmp("INF", nptr, 3) == 0) {
            if (eptr != NULL) {
                if (strnicmp("INFINITE", nptr, 8) == 0)
                    *eptr = (char*)(nptr + 8);
                else
                    *eptr = (char*)(nptr + 3);
            }
            if (neg == 1)
                return -HUGE_VAL;
            else
                return HUGE_VAL;
        } else if (strnicmp("NAN", nptr, 3) == 0) {
            if (eptr != NULL)
                *eptr = (char*)(nptr + 3);
            /* create a NaN : 0 * infinity*/
            d = HUGE_VAL;
            return d * 0;
        }
    }
    if (eptr != NULL)
        *eptr = leptr;
    return d;
}