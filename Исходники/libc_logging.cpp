static void out_vformat(Out& o, const char* format, va_list args) {
    int nn = 0;

    for (;;) {
        int mm;
        int padZero = 0;
        int padLeft = 0;
        char sign = '\0';
        int width = -1;
        int prec  = -1;
        size_t bytelen = sizeof(int);
        int slen;
        char buffer[32];  /* temporary buffer used to format numbers */

        char  c;

        /* first, find all characters that are not 0 or '%' */
        /* then send them to the output directly */
        mm = nn;
        do {
            c = format[mm];
            if (c == '\0' || c == '%')
                break;
            mm++;
        } while (1);

        if (mm > nn) {
            o.Send(format+nn, mm-nn);
            nn = mm;
        }

        /* is this it ? then exit */
        if (c == '\0')
            break;

        /* nope, we are at a '%' modifier */
        nn++;  // skip it

        /* parse flags */
        for (;;) {
            c = format[nn++];
            if (c == '\0') {  /* single trailing '%' ? */
                c = '%';
                o.Send(&c, 1);
                return;
            }
            else if (c == '0') {
                padZero = 1;
                continue;
            }
            else if (c == '-') {
                padLeft = 1;
                continue;
            }
            else if (c == ' ' || c == '+') {
                sign = c;
                continue;
            }
            break;
        }

        /* parse field width */
        if ((c >= '0' && c <= '9')) {
            nn --;
            width = (int)parse_decimal(format, &nn);
            c = format[nn++];
        }

        /* parse precision */
        if (c == '.') {
            prec = (int)parse_decimal(format, &nn);
            c = format[nn++];
        }

        /* length modifier */
        switch (c) {
        case 'h':
            bytelen = sizeof(short);
            if (format[nn] == 'h') {
                bytelen = sizeof(char);
                nn += 1;
            }
            c = format[nn++];
            break;
        case 'l':
            bytelen = sizeof(long);
            if (format[nn] == 'l') {
                bytelen = sizeof(long long);
                nn += 1;
            }
            c = format[nn++];
            break;
        case 'z':
            bytelen = sizeof(size_t);
            c = format[nn++];
            break;
        case 't':
            bytelen = sizeof(ptrdiff_t);
            c = format[nn++];
            break;
        default:
            ;
        }

        /* conversion specifier */
        const char* str = buffer;
        if (c == 's') {
            /* string */
            str = va_arg(args, const char*);
            if (str == NULL) {
                str = "(null)";
            }
        } else if (c == 'c') {