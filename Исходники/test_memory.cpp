/* Testing primitives */
void die(const char* msg, ...)
{
    char buffer[512];
    va_list args;

    va_start(args, msg);
    vsprintf_s(buffer, 512, msg, args);
    va_end(args);
    puts(buffer);
    exit(1);
}