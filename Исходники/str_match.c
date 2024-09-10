int str_match(const char *str, const char *format) {

    const char *s   = str;
    const char *fmt = format;
    unsigned int flag = 0;
    int width = 0;

    bit_t bit;
    char c;
    const char *s0;

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;

            while (*fmt >= '0' && *fmt <= '9') 
                width = width * 10 + *fmt++ - '0';

            switch(*fmt) {
                case 'd':
                    if (width) {
                        while (*s && isdigit(*s) && width-- > 0)
                            s++;
                    } else {
                        while (*s && isdigit(*s))
                            s++;
                    }
                    fmt++;
                    break;

                case '[':
                    fmt++;
                    bit_zero(&bit);

                    if (*fmt == '^') {
                        fmt++;
                        flag |= STATUS_CARET;
                    }

                    while (*fmt && *fmt != ']') {
                        if (fmt[1] == '-') {
                            for (c = *fmt; c < fmt[2]; c++) {
                                bit_set(&bit, c);
                            }
                            if (c == fmt[2])
                                fmt += 2;
                        } else {
                            bit_set(&bit, *fmt);
                            fmt++;
                        }
                    }

                    if (flag & STATUS_CARET) {
                        bit_rev(&bit);
                        /* clear STATUS_CARET */
                        flag &= ~STATUS_CARET;
                    }

                    if (width) {
                        while (*s && bit_isset(&bit, *s) && width-- > 0) {
                            s++;
                        }
                    } else {
                        while (*s && bit_isset(&bit, *s)) {
                            s++;
                        }
                    }

                    if (*fmt == ']')
                        fmt++;
                    break;

                case 'f':

                    if (width) {
                        while (*s && isdigit(*s) && width > 0)
                            s++, width--;

                        if (*s == '.' && width > 0)
                            s++, width--;

                        while (*s && isdigit(*s) && width > 0)
                            s++, width--;
                    } else {
                        while (*s && isdigit(*s))
                            s++;

                        if (*s == '.')
                            s++;

                        while (*s && isdigit(*s))
                            s++;
                    }

                    fmt++;
                    break;

                case '{':
                    fmt++;

                    flag &= ~STATUS_OR;
                    while(*fmt && *fmt != '|' && *fmt != '}') {
                        s0 = s;

                        /* match */
                        while (*fmt && *fmt != '|' && *fmt != '}' && (*s0 == *fmt))
                            s0++, fmt++;

                        /* match ok*/
                        if (*fmt == '|' || *fmt == '}') {
                            flag |= STATUS_OR;
                            while (*fmt && *fmt != '}')
                                fmt++;
                            s = s0;
                        } else {
                            /* match no*/
                            while (*fmt && *fmt != '|' && *fmt != '}')
                                fmt++;
                            if (*fmt == '|' || *fmt == '}')
                                fmt++;
                        }
                    }

                    if (!(flag & STATUS_OR))
                        return 0;

                    if (*fmt == '}')
                        fmt++;
                    break;

                default:
                    fmt++;
                    break;
            }

            width = 0;
        } else {

            /*printf("%d:%d:%c:%c\n", *fmt, *s, *fmt, *s);*/
            if (!*fmt && !*s)
                return 1;

            if (*fmt != *s) {
                /* %?*/
                if (*fmt && fmt[1] == '%' && fmt[2] == '?') {
                    fmt++;
                    continue;
                }
                else
                    return 0;
            }

            fmt++;
            s++;
        }
    }

    return !*fmt && !*s;
}