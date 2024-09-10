static void dump(const char *name, const void *ptr, size_t siz)
{
    char buf[256], sz[16];

    StringCbCopyA(buf, sizeof(buf), name);
    StringCbCatA(buf, sizeof(buf), ": ");

    const BYTE *pb = reinterpret_cast<const BYTE *>(ptr);
    while (siz--)
    {
        StringCbPrintfA(sz, sizeof(sz), "%02X ", *pb++);
        StringCbCatA(buf, sizeof(buf), sz);
    }

    trace("%s\n", buf);
}