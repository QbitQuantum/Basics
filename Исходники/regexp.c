char *sed_compile(sed_commands_t *commands, sed_comp_args *compargs,
                  char *ep, char *endbuf, int seof)
{
    int c;
    int eof = seof;
    char *lastep;
    int cclcnt;
    char bracket[NBRA], *bracketp;
    int closed;
    int neg;
    int lc;
    int i, cflg;
    int iflag; /* used for non-ascii characters in brackets */
    int nodelim = 0;
    char *sp = commands->cp;
    int regerrno = 0;

    lastep = 0;
    if ((c = GETC()) == eof || c == '\n') {
        if (c == '\n') {
            UNGETC(c);
            nodelim = 1;
        }
        commands->cp = sp;
        goto out;
    }
    bracketp = bracket;
    compargs->circf = closed = compargs->nbra = 0;
    if (c == '^')
        compargs->circf++;
    else
        UNGETC(c);
    while (1) {
        if (ep >= endbuf)
            SEDCOMPILE_ERROR(50);
        c = GETC();
        if (c != '*' && ((c != '\\') || (PEEKC() != '{')))
            lastep = ep;
        if (c == eof) {
            *ep++ = CCEOF;
            if (bracketp != bracket)
                SEDCOMPILE_ERROR(42);
            commands->cp = sp;
            goto out;
        }
        switch (c) {

        case '.':
            *ep++ = CDOT;
            continue;

        case '\n':
            SEDCOMPILE_ERROR(36);
            commands->cp = sp;
            goto out;
        case '*':
            if (lastep == 0 || *lastep == CBRA || *lastep == CKET)
                goto defchar;
            *lastep |= STAR;
            continue;

        case '$':
            if (PEEKC() != eof && PEEKC() != '\n')
                goto defchar;
            *ep++ = CDOL;
            continue;

        case '[':
            if (&ep[17] >= endbuf)
                SEDCOMPILE_ERROR(50);

            *ep++ = CCL;
            lc = 0;
            for (i = 0; i < 16; i++)
                ep[i] = 0;

            neg = 0;
            if ((c = GETC()) == '^') {
                neg = 1;
                c = GETC();
            }
            iflag = 1;
            do {
                c &= 0377;
                if (c == '\0' || c == '\n')
                    SEDCOMPILE_ERROR(49);
                if ((c & 0200) && iflag) {
                    iflag = 0;
                    if (&ep[32] >= endbuf)
                        SEDCOMPILE_ERROR(50);
                    ep[-1] = CXCL;
                    for (i = 16; i < 32; i++)
                        ep[i] = 0;
                }
                if (c == '-' && lc != 0) {
                    if ((c = GETC()) == ']') {
                        PLACE('-');
                        break;
                    }
                    if ((c & 0200) && iflag) {
                        iflag = 0;
                        if (&ep[32] >= endbuf)
                            SEDCOMPILE_ERROR(50);
                        ep[-1] = CXCL;
                        for (i = 16; i < 32; i++)
                            ep[i] = 0;
                    }
                    while (lc < c) {
                        PLACE(lc);
                        lc++;
                    }
                }
                lc = c;
                PLACE(c);
            } while ((c = GETC()) != ']');

            if (iflag)
                iflag = 16;
            else
                iflag = 32;

            if (neg) {
                if (iflag == 32) {
                    for (cclcnt = 0; cclcnt < iflag;
                        cclcnt++)
                        ep[cclcnt] ^= 0377;
                    ep[0] &= 0376;
                } else {
                    ep[-1] = NCCL;
                    /* make nulls match so test fails */
                    ep[0] |= 01;
                }
            }

            ep += iflag;

            continue;

        case '\\':
            switch (c = GETC()) {

            case '(':
                if (compargs->nbra >= NBRA)
                    SEDCOMPILE_ERROR(43);
                *bracketp++ = compargs->nbra;
                *ep++ = CBRA;
                *ep++ = compargs->nbra++;
                continue;

            case ')':
                if (bracketp <= bracket)
                    SEDCOMPILE_ERROR(42);
                *ep++ = CKET;
                *ep++ = *--bracketp;
                closed++;
                continue;

            case '{':
                if (lastep == (char *) 0)
                    goto defchar;
                *lastep |= RNGE;
                cflg = 0;
            nlim:
                c = GETC();
                i = 0;
                do {
                    if ('0' <= c && c <= '9')
                        i = 10 * i + c - '0';
                    else
                        SEDCOMPILE_ERROR(16);
                } while (((c = GETC()) != '\\') && (c != ','));
                if (i >= 255)
                    SEDCOMPILE_ERROR(11);
                *ep++ = i;
                if (c == ',') {
                    if (cflg++)
                        SEDCOMPILE_ERROR(44);
                    if ((c = GETC()) == '\\')
                        *ep++ = (char) 255;
                    else {
                        UNGETC(c);
                        goto nlim;
                        /* get 2'nd number */
                    }
                }
                if (GETC() != '}')
                    SEDCOMPILE_ERROR(45);
                if (!cflg)    /* one number */
                    *ep++ = i;
                else if ((ep[-1] & 0377) < (ep[-2] & 0377))
                    SEDCOMPILE_ERROR(46);
                continue;

            case '\n':
                SEDCOMPILE_ERROR(36);

            case 'n':
                c = '\n';
                goto defchar;

            default:
                if (c >= '1' && c <= '9') {
                    if ((c -= '1') >= closed)
                        SEDCOMPILE_ERROR(25);
                    *ep++ = CBACK;
                    *ep++ = c;
                    continue;
                }
            }
    /* Drop through to default to use \ to turn off special chars */

        defchar:
        default:
            lastep = ep;
            *ep++ = CCHR;
            *ep++ = c;
        }
    }
out:
    if (regerrno) {
        regerr(commands, regerrno);
        return (char*) NULL;
    }
    /* XXX : Basant : what extra */
    /* int reglength = (int)(ep - expbuf); */
    return ep;
}