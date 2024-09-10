void
failed(const char *s)
{
    FFLUSH(stdout);
    perror(s);
    exit(FAIL);
    /*NOTREACHED */
}