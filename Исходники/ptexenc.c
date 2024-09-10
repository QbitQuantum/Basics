/* putc() with code conversion */
int putc2(int c, FILE *fp)
{
    static int num[NOFILE];
        /* 0    : not in Kanji
           1..4 : in JIS Kanji and num[] bytes are in store[][]
           -1   : in JIS Kanji and store[][] is empty */
    static unsigned char store[NOFILE][4];
    const int fd = fileno(fp);
    int ret = c, output_enc;

#ifdef WIN32
    if ((fp == stdout || fp == stderr) && (_isatty(fd) || !prior_file_enc)) {
        if (sjisterminal) {
            if (is_internalUPTEX())
                output_enc = ENC_UTF8;
            else
                output_enc = ENC_SJIS;
        } else
#else
    if ((fp == stdout || fp == stderr) && !prior_file_enc) {
#endif

        output_enc = get_terminal_enc();
    } else
        output_enc = get_file_enc();

    if (num[fd] > 0) {        /* multi-byte char */
        if (is_internalUPTEX() && iskanji1(c)) { /* error */
            ret = flush(store[fd], num[fd], fp);
            num[fd] = 0;
        }
        store[fd][num[fd]] = c;
        num[fd]++;
        if (multistrlen(store[fd], num[fd], 0) == num[fd]) {
            long i = fromBUFF(store[fd], num[fd], 0);
            ret = put_multibyte(toENC(i, output_enc), fp);
            num[fd] = -1;
        } else if ((is_internalUPTEX() && num[fd] == 4) ||
                   (!is_internalUPTEX() && num[fd] == 2)) { /* error */
            ret = flush(store[fd], num[fd], fp);
            num[fd] = -1;
        }
    } else if (iskanji1(c)) { /* first multi-byte char */
        if (num[fd] == 0 && output_enc == ENC_JIS) {
            ret = put_multibyte(KANJI_IN, fp);
        }
        store[fd][0] = c;
        num[fd] = 1;
    } else {                  /* ASCII */
        if (num[fd] < 0 && output_enc == ENC_JIS) {
            put_multibyte(KANJI_OUT, fp);
        }
        ret = putc(c, fp);
        num[fd] = 0;
    }
    return ret;
}

/* fputs() with code conversion */
int fputs2(const char *s, FILE *fp)
{
    while (*s != '\0') {
        int ret = putc2((unsigned char)*s, fp);
        if (ret == EOF) return EOF;
        s++;
    }
    return 1;
}


static struct unget_st {
    int size;
    int buff[4];
} ungetbuff[NOFILE];

static int getc4(FILE *fp)
{
    struct unget_st *p = &ungetbuff[fileno(fp)];

    if (p->size == 0)
#ifdef WIN32
    {
        const int fd = fileno(fp);
        HANDLE hStdin;
        DWORD ret;
        wchar_t wc[2];
        long c;
        static wchar_t wcbuf = L'\0';

        if (!(fd == fileno(stdin) && _isatty(fd) && is_internalUPTEX()))
            return getc(fp);

        hStdin = GetStdHandle(STD_INPUT_HANDLE);
        if (wcbuf) {
            wc[0] = wcbuf;
            wcbuf = L'\0';
        }
        else if (ReadConsoleW(hStdin, wc, 1, &ret, NULL) == 0)
            return EOF;
        if (0xd800<=wc[0] && wc[0]<0xdc00) {
            if (ReadConsoleW(hStdin, wc+1, 1, &ret, NULL) == 0)
                return EOF;
            if (0xdc00<=wc[1] && wc[1]<0xe000) {
                c = UTF16StoUTF32(wc[0], wc[1]);
            } else {
                wcbuf = wc[1];
                c = U_REPLACEMENT_CHARACTER;  /* illegal upper surrogate pair */
            }
        } else if (0xdc00<=wc[0] && wc[0]<0xe000) {
            c = U_REPLACEMENT_CHARACTER;      /* illegal lower surrogate pair */
        } else {
            c = wc[0];
        }
        c = UCStoUTF8(c);
        /* always */       p->buff[p->size++]=BYTE4(c);
        if (BYTE3(c) != 0) p->buff[p->size++]=BYTE3(c);
        if (BYTE2(c) != 0) p->buff[p->size++]=BYTE2(c);
        if (BYTE1(c) != 0) p->buff[p->size++]=BYTE1(c);
    }
#else
        return getc(fp);
#endif
    return p->buff[--p->size];
}

static int ungetc4(int c, FILE *fp)
{
    struct unget_st *p = &ungetbuff[fileno(fp)];

    if (p->size >= 4) return EOF;
    return p->buff[p->size++] = c;
}


static unsigned char *buffer;
static long first, last;
static boolean combin_voiced_sound(boolean semi)
{
    int i, mblen;

    mblen = is_internalUPTEX() ? 3 : 2;
    if (last-mblen < first) return false;
    if (multistrlen(buffer,last,last-mblen) != mblen) return false;
    i = toUCS(fromBUFF(buffer,last,last-mblen));
    i = get_voiced_sound(i, semi);
    if (i == 0) return false;
    i = toBUFF(fromUCS(i));
    if (BYTE2(i) != 0) buffer[last-3] = BYTE2(i);
    /* always */       buffer[last-2] = BYTE3(i);
    /* always */       buffer[last-1] = BYTE4(i);
    return true;
}