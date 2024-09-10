static int
_lltoa( UITYPE x, char *buf, int prec, unsigned base )
{
    int digits = 0;
    int c;

    if (prec < 0) prec = 1;

    while (x > 0 || digits < prec) {
        c = x % base;
        x = x / base;
        if (c < 10) c += '0';
        else c = (c - 10) + 'a';
        buf[digits++] = c;
    }
    buf[digits] = 0;
    _strrev(buf);
    return digits;
}