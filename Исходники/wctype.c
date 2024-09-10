void wctype_check_functions(wint_t i, wctype_t t, wctrans_t tr, locale_t l)
{
    (void)iswalnum(i);
    (void)iswalnum_l(i, l);
    (void)iswalpha(i);
    (void)iswalpha_l(i, l);
    (void)iswblank(i);
    (void)iswblank_l(i, l);
    (void)iswcntrl(i);
    (void)iswcntrl_l(i, l);
    (void)iswctype(i, t);
    (void)iswctype_l(i, t, l);
    (void)iswdigit(i);
    (void)iswdigit_l(i, l);
    (void)iswgraph(i);
    (void)iswgraph_l(i, l);
    (void)iswlower(i);
    (void)iswlower_l(i, l);
    (void)iswprint(i);
    (void)iswprint_l(i, l);
    (void)iswpunct(i);
    (void)iswpunct_l(i, l);
    (void)iswspace(i);
    (void)iswspace_l(i, l);
    (void)iswupper(i);
    (void)iswupper_l(i, l);
    (void)iswxdigit(i);
    (void)iswxdigit_l(i, l);
    (void)towctrans(i, tr);
    (void)towctrans_l(i, tr, l);
    (void)towlower(i);
    (void)towlower_l(i, l);
    (void)towupper(i);
    (void)towupper_l(i, l);
    (void)wctrans((const char *)1234);
    (void)wctrans_l((const char *)1234, l);
    (void)wctype((const char *)1234);
    (void)wctype_l((const char *)1234, l);
}