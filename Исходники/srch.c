/*
 * expanded search comparison
 * returns 1 if match, 0 if not
 */
static int
srch_cmp(void)
{
    int tq;					/* q-reg name for ^EGq */
    struct qp tqp;				/* pointer to read q reg */

    /* what is search character */
    switch (mapch_l[sm.p->ch[sm.c & 0xFF] & 0xFF]) {

    /* match anything but following construct */
    case CTL('N'):
        /* don't read past end of string */
        if (sm.dot >= sm.z) {
            ERROR(E_ISS);
        }

        /* skip the ^N */
        fwdc(&sm);
        return(!srch_cmp());

    /* match any character */
    case CTL('X'):
        return(1);

    /* take next char literally */
    case CTL('Q'):
    case CTL('R'):

        /* don't read past end of string */
        if (sm.dot >= sm.z) {
            ERROR(E_ISS);
        }

        /* skip the ^Q */
        fwdc(&sm);
        return(*(pmap + sb.p->ch[sb.c]) ==
                *(pmap + sm.p->ch[sm.c]));

    /* match any nonalphanumeric */
    case CTL('S'):
        return(!isalnum(sb.p->ch[sb.c]));

    case CTL('E'):
        /* don't read past end of string */
        if (sm.dot >= sm.z)
                ERROR(E_ISS);

        /* skip the ^E */
        fwdc(&sm);

        switch (mapch_l[sm.p->ch[sm.c & 0xFF] & 0xFF]) {

        /* match any alpha */
        case 'a':
            return(isalpha(sb.p->ch[sb.c]));

        /* match any nonalpha */
        case 'b':
            return(!isalnum(sb.p->ch[sb.c]));

        /* rad50 symbol constituent */
        case 'c':
            return(!isalnum(sb.p->ch[sb.c]) ||
                    (sb.p->ch[sb.c] == '$') ||
                    (sb.p->ch[sb.c] == '.'));

        /* digit */
        case 'd':
            return(isdigit(sb.p->ch[sb.c]));

        /* line terminator LF, VT, FF, CR */
        case 'l':
            return((sb.p->ch[sb.c] == LF) ||
                    (sb.p->ch[sb.c] == FF) ||
                    (sb.p->ch[sb.c] == CR) ||
                    (sb.p->ch[sb.c] == VT));

        /* alphanumeric */
        case 'r':
            return(isalnum(sb.p->ch[sb.c]));

        /* lower case */
        case 'v':
            return(islower(sb.p->ch[sb.c]));

        /* upper case */
        case 'w':
            return(isupper(sb.p->ch[sb.c]));

        /* any non-null string of spaces or tabs */
        case 's':
            /* failure */
            if (((sb.p->ch[sb.c]&0177) != ' ') &&
                    ((sb.p->ch[sb.c]&0177) != TAB)) {
                return(0);
            }

            /* skip remaining spaces or tabs */
            for ( fwdc(&sb);
                    ((sb.p->ch[sb.c]&0177) == ' ') ||
                    ((sb.p->ch[sb.c]&0177) == TAB);
                    fwdc(&sb) ) {
               ;
            }

            /*
             * Back up one char (calling routine will
             * skip it)
             */
            backc(&sb);
            return(1);		/* success */

        /* any char in specified q register */
        case 'g':
            /* don't read past end of string */
            if (sm.dot >= sm.z) {
                ERROR(E_ISS);
            }

            /* get to the next char */
            fwdc(&sm);

            /* read q-reg spec */
            tq = getqspec(1, sm.p->ch[sm.c]);

            for (tqp.dot = tqp.c = 0, tqp.p = qreg[tq].f;
                    tqp.dot < qreg[tq].z;
                    fwdc(&tqp)) {

                /* match */
                if (*(pmap + tqp.p->ch[tqp.c]) ==
                        *(pmap + sb.p->ch[sb.c])) {
                    return(1);
                }

            }
            return(0);		/* fail */

        default:
                ERROR(E_ISS);
        }
    default:
        return(*(pmap + sb.p->ch[sb.c]) == *(pmap + sm.p->ch[sm.c]));
    }
}