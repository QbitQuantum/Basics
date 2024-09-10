static int checkcapital(word *w)
/* Returns 1 if *w is capitalized according to the definition */
/* in par.doc (assuming <cap> is 0), or 0 if not.             */
{
    const wchar_t *p, *end;

    for (p = w->chrs, end = p + w->length;
            p < end && !iswalnum(*p);
            ++p);
    return p < end && !iswlower(*p);
}