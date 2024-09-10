static inline size_t snprint_int(char *buf, size_t size, int i,
                                 unsigned int base, bool left,
                                 char padding, size_t width)
{
    char str[33];
    size_t len = itoa_s(i, base, str, sizeof(str));

    if (len == 0)
        return 0;

    return copy_with_padding(buf, size, str, len, left, padding, width);
}