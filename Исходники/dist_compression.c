/**
 * Compress two strings and return the length of the compressed data
 * @param x String x
 * @param y String y
 * @return length of the compressed data.
 */
static float compress_str2(hstring_t x, hstring_t y)
{
    unsigned long tmp, width;
    unsigned char *src, *dst;

    assert(x.type == y.type);

    width = x.type == TYPE_SYM ? sizeof(sym_t) : sizeof(char);
    tmp = compressBound((x.len + y.len) * width);

    dst = malloc(tmp);
    src = malloc(tmp);
    if (!src || !dst) {
        error("Failed to allocate memory for compression");
        return -1;
    }

    /* Concatenate sequences y and x */
    memcpy(src, y.str.s, y.len * width);
    memcpy(src + y.len * width, x.str.s, x.len * width);

    compress2(dst, &tmp, src, (x.len + y.len) * width, level);

    free(dst);
    free(src);
    return (float) tmp;
}