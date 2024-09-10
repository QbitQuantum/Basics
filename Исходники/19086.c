int ftp_command(char *buf,int success,FILE *out,char *fmt,...)
{
    va_list va;
    char line[1200];
    int val;

    va_start(va,fmt);
    vsprintf(line,fmt,va);
    va_end(va);

    if (write(fileno(out),line,strlen(line)) < 0)
        return(-1);

    bzero(buf,200);
    while(1) {
        Fgets(line,sizeof(line),out);
#ifdef DEBUG
        printf("%s",line);
#endif
        if (*(line+3)!='-') break;
    }
    strncpy(buf,line,200);
    val = atoi(line);
    if (success != val) return(-1);
    return(1);
}