void deftounicode(strnumber glyph, strnumber unistr)
{
    char buf[SMALL_BUF_SIZE], *p;
    char buf2[SMALL_BUF_SIZE], *q;
    int valid_unistr;           /* 0: invalid; 1: unicode value; 2: string */
    int i, l;
    glyph_unicode_entry *gu, t;
    void **aa;

    p = makecstring(glyph);
    assert(strlen(p) < SMALL_BUF_SIZE);
    strcpy(buf, p);             /* copy the result to buf before next call of makecstring() */
    p = makecstring(unistr);
    while (*p == ' ')
        p++;                    /* ignore leading spaces */
    l = strlen(p);
    while (l > 0 && p[l - 1] == ' ')
        l--;                    /* ignore traling spaces */
    valid_unistr = 1;           /* a unicode value is the most common case */
    for (i = 0; i < l; i++) {
        if (p[i] == ' ')
            valid_unistr = 2;   /* if a space occurs we treat this entry as a string */
        else if (!isXdigit(p[i])) {
            valid_unistr = 0;
            break;
        }
    }
    if (l == 0 || valid_unistr == 0 || strlen(buf) == 0
        || strcmp(buf, notdef) == 0) {
        pdftex_warn("ToUnicode: invalid parameter(s): `%s' => `%s'", buf, p);
        return;
    }
    if (glyph_unicode_tree == NULL) {
        glyph_unicode_tree =
            avl_create(comp_glyph_unicode_entry, NULL, &avl_xallocator);
        assert(glyph_unicode_tree != NULL);
    }
    t.name = buf;
    /* allow overriding existing entries */
    if ((gu = (glyph_unicode_entry *) avl_find(glyph_unicode_tree, &t)) != NULL) {
        if (gu->code == UNI_STRING) {
            assert(gu->unicode_seq != NULL);
            xfree(gu->unicode_seq);
        }
    } else {                    /* make new entry */
        gu = new_glyph_unicode_entry();
        gu->name = xstrdup(buf);
    }
    if (valid_unistr == 2) {    /* a string with space(s) */
        /* copy p to buf2, ignoring spaces */
        for (q = buf2; *p != 0; p++)
            if (*p != ' ')
                *q++ = *p;
        *q = 0;
        gu->code = UNI_STRING;
        gu->unicode_seq = xstrdup(buf2);
    } else {
        i = sscanf(p, "%lX", &(gu->code));
        assert(i == 1);
    }
    aa = avl_probe(glyph_unicode_tree, gu);
    assert(aa != NULL);
}