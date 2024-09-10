/**
 * Dumps formatted string to debug console and stdout if such is available
 */
int PRINT_Stdout(Str format, va_list va)
{
    int n = Vfprintf(stdout, format, va);
    fflush(stdout);
    return n;
}