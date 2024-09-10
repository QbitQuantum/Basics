//------------------------------------------------------------------
void Verbose::Warn(const char *class_name, const char *func_name,
		   const char *format, ...) {
    
    if(!active[VERBOSE_WARN_LEVEL]) return;

    va_list args;
    va_start(args, format);
    printf("WARNING %s::%s :\n\t", class_name, func_name);
    vprintf(format, args);
    
    FILE *fp;
    char *filename = "phys.warn";
    if( (fp = Fopen(filename, "a")) == NULL ) {
	ERR.FileA("Verbose","Warn", filename);
    }
    Fprintf(fp,"WARNING %s::%s :\n\t", class_name, func_name);
    Vfprintf(fp, format, args);
    Fclose(fp);
    
}