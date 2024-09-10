double
wcstod (const wchar_t * str, wchar_t ** end)
{
    double val;
    double mantissa;
    unsigned long divisor;
    unsigned long power;
    int sign;
    int sign_power;
    wchar_t *pend;
    wchar_t ch;
    // skip blank
    for (; iswblank (*str); str ++) {
    }
    for (ch = *str; (ch == '-') || (ch == '+'); str ++) {
    }
    // the sign
    sign = 0;
    if ('-' == ch) {
        sign = 1;
        str ++;
    }
    // skip leading zero
    for (; '0' == (*str); str ++) {
    }
    val = 0.0;
    mantissa = 0.0;
    divisor = 0;
    power = 0.0;
    // integer part
    for (ch = *str; ('0' <= ch) && (ch <= '9'); str ++) {
        ch -= '0';
        val *= 10;
        val += ch;
    }
    // floating point & mantissa
    if ('.' == *str) {
        str ++;
        for (ch = *str; ('0' <= ch) && (ch <= '9'); str ++) {
            ch -= '0';
            mantissa *= 10.0;
            mantissa += ch;
            divisor ++;
        }
    }
    for (; divisor > 0; divisor --) {
        mantissa /= 10.0;
    }
    val += mantissa;
    sign_power = 0;
    if (('e' == *str) || ('E' == *str)) {
        str ++;
        if ('-' == ch) {
            sign_power = 1;
            str ++;
        }
        pend = NULL;
        power = wcstoul (str, &pend, 10);
        if (NULL != pend) {
            str = pend;
        }
    }
    if (power > 0) {
        if (sign_power) {
            for (; power > 0; power --) {
                val /= 10.0;
            }
        } else {
            for (; power > 0; power --) {
                val *= 10.0;
            }
        }
    }
    if (sign) {
        val = - val;
    }
    if (end) {
        *end = (wchar_t *)str;
    }
    return val;
}