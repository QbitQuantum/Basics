/* Convert session data to a neat hexdump logfile */
static int ncat_hexdump(int logfd, const char *data, int len)
{
    const char *p = data;
    char c;
    int i;
    char bytestr[4] = { 0 };
    char addrstr[10] = { 0 };
    char hexstr[16 * 3 + 5] = { 0 };
    char charstr[16 * 1 + 5] = { 0 };
    char outstr[80] = { 0 };

    /* FIXME: needs to be audited closer */
    for (i = 1; i <= len; i++) {
        if (i % 16 == 1) {
            /* Hex address output */
            Snprintf(addrstr, sizeof(addrstr), "%.4x", (u_int) (p - data));
        }

        c = *p;

        /* If the character isn't printable. Control characters, etc. */
        if (isprint((int) (unsigned char) c) == 0)
            c = '.';

        /* hex for output */
        Snprintf(bytestr, sizeof(bytestr), "%02X ", (unsigned char) *p);
        strncat(hexstr, bytestr, sizeof(hexstr) - strlen(hexstr) - 1);

        /* char for output */
        Snprintf(bytestr, sizeof(bytestr), "%c", c);
        strncat(charstr, bytestr, sizeof(charstr) - strlen(charstr) - 1);

        if (i % 16 == 0) {
            /* neatly formatted output */
            Snprintf(outstr, sizeof(outstr), "[%4.4s]   %-50.50s  %s\n",
                     addrstr, hexstr, charstr);

            Write(logfd, outstr, strlen(outstr));
            zmem(outstr, sizeof(outstr));

            hexstr[0] = 0;
            charstr[0] = 0;
        } else if (i % 8 == 0) {
            /* cat whitespaces where necessary */
            strncat(hexstr, "  ", sizeof(hexstr) - strlen(hexstr) - 1);
            strncat(charstr, " ", sizeof(charstr) - strlen(charstr) - 1);
        }

        /* get the next byte */
        p++;
    }

    /* if there's still data left in the buffer, print it */
    if (strlen(hexstr) > 0) {
        Snprintf(outstr, sizeof(outstr), "[%4.4s]   %-50.50s  %s\n",
                    addrstr, hexstr, charstr);

        Write(logfd, outstr, strlen(outstr));
        zmem(outstr, sizeof(outstr));
    }

    return 1;
}