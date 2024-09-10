_internal_handle_float(
    int negative,
    int exp,
    int suppress,
    ULONGLONG d,
    int l_or_L_prefix,
    va_list *ap)
{
    long double cur = 1, expcnt = 10;
    unsigned fpcontrol;
    BOOL negexp;

    fpcontrol = _control87(0, 0);
    _control87(_EM_DENORMAL|_EM_INVALID|_EM_ZERODIVIDE
            |_EM_OVERFLOW|_EM_UNDERFLOW|_EM_INEXACT, 0xffffffff);

    negexp = (exp < 0);
    if(negexp)
        exp = -exp;
    /* update 'cur' with this exponent. */
    while(exp) {
        if(exp & 1)
            cur *= expcnt;
        exp /= 2;
        expcnt = expcnt*expcnt;
    }
    cur = (negexp ? d/cur : d*cur);

    _control87(fpcontrol, 0xffffffff);

    if (!suppress) {
        if (l_or_L_prefix) _SET_NUMBER_(double);
        else _SET_NUMBER_(float);
    }
}