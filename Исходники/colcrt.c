void pflush(int ol)
{
    register int i;
    register wchar_t *cp;
    char lastomit;
    int l, w;

    l = ol;
    lastomit = 0;
    if (l > 266)
        l = 266;
    else
        l |= 1;
    for (i = first | 1; i < l; i++) {
        move(i, i - 1);
        move(i, i + 1);
    }
    for (i = first; i < l; i++) {
        cp = page[i];
        if (printall == 0 && lastomit == 0 && *cp == 0) {
            lastomit = 1;
            continue;
        }
        lastomit = 0;
        while (*cp) {
            if ((w = wcwidth(*cp)) > 0) {
                putwchar(*cp);
                cp += w;
            } else
                cp++;
        }
        putwchar('\n');
    }
    memmove(page, page[ol], (267 - ol) * 132 * sizeof(wchar_t));
    memset(page[267 - ol], '\0', ol * 132 * sizeof(wchar_t));
    outline -= ol;
    outcol = 0;
    first = 1;
}