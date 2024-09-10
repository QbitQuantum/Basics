QStringList KShell::splitArgs( const QString &args, Options flags, Errors *err)
{
    QStringList ret;
    bool firstword = flags & AbortOnMeta;

    for (int pos = 0; ; ) {
        QChar c;
        do {
            if (pos >= args.length())
                goto okret;
            c = args.unicode()[pos++];
        } while (c.isSpace());
        QString cret;
        if ((flags & TildeExpand) && c == QLatin1Char('~')) {
            int opos = pos;
            for (; ; pos++) {
                if (pos >= args.length())
                    break;
                c = args.unicode()[pos];
                if (c == QLatin1Char('/') || c.isSpace())
                    break;
                if (isQuoteMeta( c )) {
                    pos = opos;
                    c = QLatin1Char('~');
                    goto notilde;
                }
                if ((flags & AbortOnMeta) && isMeta( c ))
                    goto metaerr;
            }
            QString ccret = homeDir( args.mid(opos, pos-opos) );
            if (ccret.isEmpty()) {
                pos = opos;
                c = QLatin1Char('~');
                goto notilde;
            }
            if (pos >= args.length()) {
                ret += ccret;
                goto okret;
            }
            pos++;
            if (c.isSpace()) {
                ret += ccret;
                firstword = false;
                continue;
            }
            cret = ccret;
        }
        // before the notilde label, as a tilde does not match anyway
        if (firstword) {
            if (c == QLatin1Char('_') ||
                (c >= QLatin1Char('A') && c <= QLatin1Char('Z')) ||
                (c >= QLatin1Char('a') && c <= QLatin1Char('z')))
            {
                int pos2 = pos;
                QChar cc;
                do {
                    if (pos2 >= args.length()) {
                        // Exactly one word
                        ret += args.mid(pos - 1);
                        goto okret;
                    }
                    cc = args.unicode()[pos2++];
                } while (cc == QLatin1Char('_') ||
                       (cc >= QLatin1Char('A') && cc <= QLatin1Char('Z')) ||
                       (cc >= QLatin1Char('a') && cc <= QLatin1Char('z')) ||
                       (cc >= QLatin1Char('0') && cc <= QLatin1Char('9')));
                if (cc == QLatin1Char('='))
                    goto metaerr;
            }
        }
      notilde:
        do {
            if (c == QLatin1Char('\'')) {
                int spos = pos;
                do {
                    if (pos >= args.length())
                        goto quoteerr;
                    c = args.unicode()[pos++];
                } while (c != QLatin1Char('\''));
                cret += args.mid(spos, pos-spos-1);
            } else if (c == QLatin1Char('"')) {
                for (;;) {
                    if (pos >= args.length())
                        goto quoteerr;
                    c = args.unicode()[pos++];
                    if (c == QLatin1Char('"'))
                        break;
                    if (c == QLatin1Char('\\')) {
                        if (pos >= args.length())
                            goto quoteerr;
                        c = args.unicode()[pos++];
                        if (c != QLatin1Char('"') &&
                            c != QLatin1Char('\\') &&
                            !((flags & AbortOnMeta) &&
                              (c == QLatin1Char('$') ||
                               c == QLatin1Char('`'))))
                            cret += QLatin1Char('\\');
                    } else if ((flags & AbortOnMeta) &&
                                (c == QLatin1Char('$') ||
                                 c == QLatin1Char('`')))
                        goto metaerr;
                    cret += c;
                }
            } else if (c == QLatin1Char('$') && pos < args.length() &&
                       args.unicode()[pos] == QLatin1Char('\'')) {
                pos++;
                for (;;) {
                    if (pos >= args.length())
                        goto quoteerr;
                    c = args.unicode()[pos++];
                    if (c == QLatin1Char('\''))
                        break;
                    if (c == QLatin1Char('\\')) {
                        if (pos >= args.length())
                            goto quoteerr;
                        c = args.unicode()[pos++];
                        switch (c.toAscii()) {
                        case 'a': cret += QLatin1Char('\a'); break;
                        case 'b': cret += QLatin1Char('\b'); break;
                        case 'e': cret += QLatin1Char('\033'); break;
                        case 'f': cret += QLatin1Char('\f'); break;
                        case 'n': cret += QLatin1Char('\n'); break;
                        case 'r': cret += QLatin1Char('\r'); break;
                        case 't': cret += QLatin1Char('\t'); break;
                        case '\\': cret += QLatin1Char('\\'); break;
                        case '\'': cret += QLatin1Char('\''); break;
                        case 'c':
                            if (pos >= args.length())
                                goto quoteerr;
                            cret += args.unicode()[pos++].toAscii() & 31;
                            break;
                        case 'x':
                          {
                            if (pos >= args.length())
                                goto quoteerr;
                            int hv = fromHex( args.unicode()[pos++] );
                            if (hv < 0)
                                goto quoteerr;
                            if (pos < args.length()) {
                                int hhv = fromHex( args.unicode()[pos] );
                                if (hhv > 0) {
                                    hv = hv * 16 + hhv;
                                    pos++;
                                }
                                cret += QChar( hv );
                            }
                            break;
                          }
                        default:
                            if (c.toAscii() >= '0' && c.toAscii() <= '7') {
                                char cAscii = c.toAscii();
                                int hv = cAscii - '0';
                                for (int i = 0; i < 2; i++) {
                                    if (pos >= args.length())
                                        break;
                                    c = args.unicode()[pos];
                                    if (c.toAscii() < '0' || c.toAscii() > '7')
                                        break;
                                    hv = hv * 8 + (c.toAscii() - '0');
                                    pos++;
                                }
                                cret += QChar( hv );
                            } else {
                                cret += QLatin1Char('\\');
                                cret += c;
                            }
                            break;
                        }
                    } else
                        cret += c;
                }
            } else {
                if (c == QLatin1Char('\\')) {
                    if (pos >= args.length())
                        goto quoteerr;
                    c = args.unicode()[pos++];
                } else if ((flags & AbortOnMeta) && isMeta( c ))
                    goto metaerr;
                cret += c;
            }
            if (pos >= args.length())
                break;
            c = args.unicode()[pos++];
        } while (!c.isSpace());
        ret += cret;
        firstword = false;
    }

  okret:
    if (err)
        *err = NoError;
    return ret;

  quoteerr:
    if (err)
        *err = BadQuoting;
    return QStringList();

  metaerr:
    if (err)
        *err = FoundMeta;
    return QStringList();
}