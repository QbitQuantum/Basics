void
putstring(FILE *f, char *s)
{
    while (*s != '\0')
    {
        PUTC(*s,f);
        ++s;
    }
}