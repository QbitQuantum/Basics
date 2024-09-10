UChar *
make_alphabet(const UChar *source)
{
    UChar *dest;
    int sourcelen = u_strlen(source);
    int x, y;

    dest = safe_calloc(sourcelen + 1, sizeof(UChar));

    u_strcpy(dest, source);

    /* Very simple ripple sort as these are very short strings */
    /* No advantage in using qsort() or similar */
    for (x = 0; x < sourcelen - 1; x++) {
        for (y = x + 1; y < sourcelen ; y++) {
            if (dest[x] > dest[y]) {
                UChar temp;

                temp = dest[x];
                dest[x] = dest[y];
                dest[y] = temp;
            }
        }
    }

    x = y = 0;
    while (dest[x]) {
        if (dest[x] != dest[y])
            dest[++y] = dest[x];
        x++;
    }
    dest[++y] = dest[x];
    return dest;
}