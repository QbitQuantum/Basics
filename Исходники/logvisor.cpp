 void reportSource(const char* modName, Level severity,
                   const char* file, unsigned linenum,
                   const wchar_t* format, va_list ap)
 {
     char sourceInfo[128];
     snprintf(sourceInfo, 128, "%s:%u", file, linenum);
     _reportHead(modName, sourceInfo, severity);
     vfwprintf(stderr, format, ap);
     fprintf(stderr, "\n");
 }