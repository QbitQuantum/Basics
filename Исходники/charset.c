static ULONG readLine(struct Library *DOSBase, BPTR fh, char *buf,
    ULONG size)
{
    char *c;

    if ((c = FGets(fh, buf, size)) == NULL)
        return FALSE;

    for (; *c; c++)
    {
        if (*c == '\n' || *c == '\r')
        {
            *c = '\0';
            break;
        }
    }

    return TRUE;
}