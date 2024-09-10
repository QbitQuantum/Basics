void rpn_exp3(calc_number_t *c)
{
    if (calc.base == IDC_RADIO_DEC) {
        c->f = pow(c->f, 3.);
        if (_finite(c->f) == 0)
            calc.is_nan = TRUE;
    } else
        c->i *= (c->i*c->i);
}