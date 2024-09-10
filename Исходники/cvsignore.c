inline void append(YYCTYPE *output, size_t & outsize, const YYCTYPE * text, size_t len)
{
    memcpy(output + outsize, text, len);
    outsize += (len / sizeof(YYCTYPE));
}