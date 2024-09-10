/* Try the longest match first. */
LIB_EXPORT uint32_t CC has_right_approx_match( char *pattern, uint32_t errors, 
                                char *buf, size_t buflen, 
                                uint32_t *bestpos, uint32_t *errcnt )
{
    uint32_t plen = strlen(pattern);
    int32_t *prev = malloc(sizeof(int)*(plen+1));
    int32_t *nxt = malloc(sizeof(int)*(plen+1));
    int32_t *tmp;
    int32_t i, j;
    int32_t allowable;
    char *subpattern, chBackup;
    char *subpattern_r;
    int32_t dist;

    int32_t found = 0;
    int32_t foundpos = 0;
    int32_t founderr = 0;
    int32_t bufj;

    int bound = plen;
    if (buflen < bound) {
        bound = buflen;
    }

    subpattern = malloc(plen + 1);
    subpattern_r = malloc(plen + 1);
    strncpy(subpattern, pattern, plen);

    for (i=bound; i>=8; i--, subpattern[i] = chBackup) {

        /* See if the first i chars of the pattern match the last i
           chars of the text with (errors) errors.
           We match in reverse, so the initial penalty of skipping
           the "first part" of the pattern means skipping the end
        */
        /* making prefix of length i out of pattern
        (subpattern contains full copy of pattern)*/
        chBackup = subpattern[i];
        subpattern[i] = '\0';

        reverse_string(subpattern, i, subpattern_r);
        init_col(subpattern_r, i, nxt);

        for (j=0; j<i; j++) {
            bufj = buflen - j - 1;
            tmp = prev; prev = nxt; nxt = tmp;
            compute_dp_next_col(subpattern_r, i, 0, buf[bufj], j, prev, nxt);
        }
        dist = nxt[i];
        allowable = 1+lroundf((float)i * (float)errors / (float)plen);
        if (found) {
            if (dist <= founderr) {
                foundpos = buflen - i;
                founderr = dist;
            } else {
                goto DONE;
            }
        } else if (dist <= allowable) {
            /* Found a match */
            found = 1;
            foundpos = buflen - i;
            founderr = dist;

            /* Continue a bit to see if something's equally good or better */
        }
    }
    DONE:
    free(subpattern);
    free(subpattern_r);
    free(prev);
    free(nxt);
    if (found) {
        *bestpos = foundpos;
        *errcnt = founderr;
        return 1;
    }
    return 0;
}