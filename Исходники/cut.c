/*
 * Cut based on byte positions, taking care not to split multibyte characters.
 * Although this function also handles the case where -n is not specified,
 * c_cut() ought to be much faster.
 */
void
b_n_cut(FILE *fp, const char *fname)
{
    size_t col, i, lbuflen;
    static char buf[MAX_LINE_LENGTH];
    char *lbuf;
    int canwrite, clen, warned;

    warned = 0;
    while ((lbuf = fgets(buf, sizeof buf, fp)) != NULL) {
        lbuflen = strlen(lbuf);

        for (col = 0; lbuflen > 0; col += clen) {
            if ((clen = mblen(lbuf, lbuflen)) < 0) {
                if (!warned) {
                    warn("%s", fname);
                    warned = 1;
                }
                clen = 1;
            }
            if (clen == 0 || *lbuf == '\n')
                break;
            if (col < maxval && !positions[1 + col]) {
                /*
                 * Print the character if (1) after an initial
                 * segment of un-selected bytes, the rest of
                 * it is selected, and (2) the last byte is
                 * selected.
                 */
                i = col;
                while (i < col + clen && i < maxval &&
                        !positions[1 + i])
                    i++;
                canwrite = i < col + clen;
                for (; i < col + clen && i < maxval; i++)
                    canwrite &= positions[1 + i];
                if (canwrite)
                    fwrite(lbuf, 1, clen, stdout);
            } else {
                /*
                 * Print the character if all of it has
                 * been selected.
                 */
                canwrite = 1;
                for (i = col; i < col + clen; i++)
                    if ((i >= maxval && !autostop) ||
                            (i < maxval && !positions[1 + i])) {
                        canwrite = 0;
                        break;
                    }
                if (canwrite)
                    fwrite(lbuf, 1, clen, stdout);
            }
            lbuf += clen;
            lbuflen -= clen;
        }
        if (lbuflen > 0)
            putchar('\n');
    }
}