void
setlinebuf(FILE * file)
{
    setbuf(file, NULL);
}