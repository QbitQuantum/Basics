static int
fmm_ascmagic(unsigned char *buf, size_t nbytes, char **mime_type)
{
    int has_escapes = 0;
    unsigned char *s;
    char nbuf[HOWMANY + 1]; /* one extra for terminating '\0' */
    char *token;
    register struct names *p;
    int small_nbytes;
    char *strtok_state;
    unsigned char *tp;

    /* these are easy, do them first */

    /*
     * for troff, look for . + letter + letter or .\"; this must be done to
     * disambiguate tar archives' ./file and other trash from real troff
     * input.
     */
    if (*buf == '.') {
        tp = buf + 1;
        while (isSPACE(*tp))
            ++tp;       /* skip leading whitespace */
        if ((isALNUM(*tp) || *tp == '\\') && (isALNUM(*(tp + 1)) || *tp == '"')) {
            strcpy(*mime_type, "application/x-troff");
            return 0;
        }
    }

    if ((*buf == 'c' || *buf == 'C') && isSPACE(*(buf + 1))) {
        /* Fortran */
        strcpy(*mime_type, "text/plain");
        return 0;
    }

    /* look for tokens from names.h - this is expensive!, so we'll limit
     * ourselves to only SMALL_HOWMANY bytes */
    small_nbytes = (nbytes > SMALL_HOWMANY) ? SMALL_HOWMANY : nbytes;

    /* make a copy of the buffer here because strtok() will destroy it */
    s = (unsigned char *) memcpy(nbuf, buf, small_nbytes);
    s[small_nbytes] = '\0';
    has_escapes = (memchr(s, '\033', small_nbytes) != NULL);
    while ((token = strtok_r((char *) s, " \t\n\r\f", &strtok_state)) != NULL) {
        s = NULL;       /* make strtok() keep on tokin' */
        for (p = names; p < names + NNAMES; p++) {
            if (strEQ(p->name, token)) {
                strcpy(*mime_type, types[p->type]);
                if (has_escapes)
                    strcat(*mime_type, " (with escape sequences)");
                return 0;
            }
        }
    }

    int is_tarball = is_tar(buf, nbytes);
    if ( is_tarball == 1 || is_tarball == 2 ) {
        /* 1: V7 tar archive */
        /* 2: POSIX tar archive */
        strcpy(*mime_type, "application/x-tar");
        return 0;
    }

    /* all else fails, but it is ascii... */
    strcpy(*mime_type, "text/plain");
    return 0;
}