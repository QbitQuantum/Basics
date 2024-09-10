void
telrcv()
{
    register int c;
    static int state = TS_DATA;
#if	defined(CRAY2) && defined(UNICOS5)
    char *opfrontp = pfrontp;
#endif

    while (ncc > 0) {
        if ((&ptyobuf[BUFSIZ] - pfrontp) < 2)
            break;
        c = *netip++ & 0377, ncc--;
        switch (state) {

        case TS_CR:
            state = TS_DATA;
            /* Strip off \n or \0 after a \r */
            if ((c == 0) || (c == '\n')) {
                break;
            }
        /* FALL THROUGH */

        case TS_DATA:
            if (c == IAC) {
                state = TS_IAC;
                break;
            }
            /*
             * We now map \r\n ==> \r for pragmatic reasons.
             * Many client implementations send \r\n when
             * the user hits the CarriageReturn key.
             *
             * We USED to map \r\n ==> \n, since \r\n says
             * that we want to be in column 1 of the next
             * printable line, and \n is the standard
             * unix way of saying that (\r is only good
             * if CRMOD is set, which it normally is).
             */
            if ((c == '\r') && his_state_is_wont(TELOPT_BINARY)) {
                int nc = *netip;
#ifdef	LINEMODE
                /*
                 * If we are operating in linemode,
                 * convert to local end-of-line.
                 */
                if (linemode && (ncc > 0) && (('\n' == nc) ||
                                              ((0 == nc) && tty_iscrnl())) ) {
                    netip++;
                    ncc--;
                    c = '\n';
                } else
#endif
                {
                    state = TS_CR;
                }
            }
            *pfrontp++ = c;
            break;

        case TS_IAC:
gotiac:
            switch (c) {

            /*
             * Send the process on the pty side an
             * interrupt.  Do this with a NULL or
             * interrupt char; depending on the tty mode.
             */
            case IP:
                DIAG(TD_OPTIONS,
                     printoption("td: recv IAC", c));
                interrupt();
                break;

            case BREAK:
                DIAG(TD_OPTIONS,
                     printoption("td: recv IAC", c));
                sendbrk();
                break;

            /*
             * Are You There?
             */
            case AYT:
                DIAG(TD_OPTIONS,
                     printoption("td: recv IAC", c));
                recv_ayt();
                break;

            /*
             * Abort Output
             */
            case AO:
            {
                DIAG(TD_OPTIONS,
                     printoption("td: recv IAC", c));
                ptyflush();	/* half-hearted */
                init_termbuf();

                if (slctab[SLC_AO].sptr &&
                        *slctab[SLC_AO].sptr != (cc_t)(_POSIX_VDISABLE)) {
                    *pfrontp++ =
                        (unsigned char)*slctab[SLC_AO].sptr;
                }

                netclear();	/* clear buffer back */
                *nfrontp++ = IAC;
                *nfrontp++ = DM;
                neturg = nfrontp-1; /* off by one XXX */
                DIAG(TD_OPTIONS,
                     printoption("td: send IAC", DM));
                break;
            }

            /*
             * Erase Character and
             * Erase Line
             */
            case EC:
            case EL:
            {
                cc_t ch;

                DIAG(TD_OPTIONS,
                     printoption("td: recv IAC", c));
                ptyflush();	/* half-hearted */
                init_termbuf();
                if (c == EC)
                    ch = *slctab[SLC_EC].sptr;
                else
                    ch = *slctab[SLC_EL].sptr;
                if (ch != (cc_t)(_POSIX_VDISABLE))
                    *pfrontp++ = (unsigned char)ch;
                break;
            }

            /*
             * Check for urgent data...
             */
            case DM:
                DIAG(TD_OPTIONS,
                     printoption("td: recv IAC", c));
                SYNCHing = stilloob(net);
                settimer(gotDM);
                break;


            /*
             * Begin option subnegotiation...
             */
            case SB:
                state = TS_SB;
                SB_CLEAR();
                continue;

            case WILL:
                state = TS_WILL;
                continue;

            case WONT:
                state = TS_WONT;
                continue;

            case DO:
                state = TS_DO;
                continue;

            case DONT:
                state = TS_DONT;
                continue;
            case EOR:
                if (his_state_is_will(TELOPT_EOR))
                    doeof();
                break;

            /*
             * Handle RFC 10xx Telnet linemode option additions
             * to command stream (EOF, SUSP, ABORT).
             */
            case xEOF:
                doeof();
                break;

            case SUSP:
                sendsusp();
                break;

            case ABORT:
                sendbrk();
                break;

            case IAC:
                *pfrontp++ = c;
                break;
            }
            state = TS_DATA;
            break;

        case TS_SB:
            if (c == IAC) {
                state = TS_SE;
            } else {
                SB_ACCUM(c);
            }
            break;

        case TS_SE:
            if (c != SE) {
                if (c != IAC) {
                    /*
                     * bad form of suboption negotiation.
                     * handle it in such a way as to avoid
                     * damage to local state.  Parse
                     * suboption buffer found so far,
                     * then treat remaining stream as
                     * another command sequence.
                     */

                    /* for DIAGNOSTICS */
                    SB_ACCUM(IAC);
                    SB_ACCUM(c);
                    subpointer -= 2;

                    SB_TERM();
                    suboption();
                    state = TS_IAC;
                    goto gotiac;
                }
                SB_ACCUM(c);
                state = TS_SB;
            } else {
                /* for DIAGNOSTICS */
                SB_ACCUM(IAC);
                SB_ACCUM(SE);
                subpointer -= 2;

                SB_TERM();
                suboption();	/* handle sub-option */
                state = TS_DATA;
            }
            break;

        case TS_WILL:
            willoption(c);
            state = TS_DATA;
            continue;

        case TS_WONT:
            wontoption(c);
            state = TS_DATA;
            continue;

        case TS_DO:
            dooption(c);
            state = TS_DATA;
            continue;

        case TS_DONT:
            dontoption(c);
            state = TS_DATA;
            continue;

        default:
            syslog(LOG_ERR, "telnetd: panic state=%d\n", state);
            printf("telnetd: panic state=%d\n", state);
            exit(1);
        }
    }
#if	defined(CRAY2) && defined(UNICOS5)
    if (!linemode) {
        char	xptyobuf[BUFSIZ+NETSLOP];
        char	xbuf2[BUFSIZ];
        register char *cp;
        int n = pfrontp - opfrontp, oc;
        memmove(xptyobuf, opfrontp, n);
        pfrontp = opfrontp;
        pfrontp += term_input(xptyobuf, pfrontp, n, BUFSIZ+NETSLOP,
                              xbuf2, &oc, BUFSIZ);
        for (cp = xbuf2; oc > 0; --oc)
            if ((*nfrontp++ = *cp++) == IAC)
                *nfrontp++ = IAC;
    }
#endif	/* defined(CRAY2) && defined(UNICOS5) */
}  /* end of telrcv */