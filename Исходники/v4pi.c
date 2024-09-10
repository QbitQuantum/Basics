void v4pDisplayDebug(char *formatString, ...) {
    va_list args ; char text[0x100] ;
    va_start(args, formatString) ;
    vprintf(formatString, args) ;
    va_end(args);
}