xbool_t ctype_iswxdigit(xwchar_t c)
{
    return c < 0x100 ? isxdigit((char)c) : XFALSE;
}