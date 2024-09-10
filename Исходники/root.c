void error(const dchar *format, ...)
{
    va_list ap;

    va_start(ap, format);
    printf("Error: ");
    vwprintf(format, ap);
    va_end( ap );
    printf("\n");
    fflush(stdout);

    exit(EXIT_FAILURE);
}