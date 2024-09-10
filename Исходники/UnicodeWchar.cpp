int u_memcasecmp(const UChar* a, const UChar* b, int length, unsigned options)
{
    for (int i = 0; i < length; ++i) {
        UChar c1 = u_foldCase(a[i], options);
        UChar c2 = u_foldCase(b[i], options);
        if (c1 != c2)
            return c1 - c2;
    }

    return 0;
}