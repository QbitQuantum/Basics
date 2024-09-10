int main()
{
    char dst[9];
    char *source = "This is a string";
    setlocale(LC_ALL, "C");
    size_t sz;
    sz = strxfrm(dst, source, 10);
    return 0;
}