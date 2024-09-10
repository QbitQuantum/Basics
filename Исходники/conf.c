/*
 * load_config_file: loads from `file' all the options that are written in it
 * and stores them in the environment. See parse_config_line() above.
 * If `file' cannot be opened -1 is returned, but if it is read and
 * parse_config_line() detects a corrupted line, fatal() is directly called.
 * On success 0 is returned.
 */
int load_config_file(char *file)
{
    FILE *fd;
    char buf[PATH_MAX+1], *p, *str;
    size_t slen;
    int i=0, e=0;

    if(!(fd=fopen(file, "r"))) {
        fatal("Cannot load the configuration file from %s: %s\n"
              "  Maybe you want to use the -c option ?",
              file, strerror(errno));
        return -1;
    }

    while(!feof(fd) && i < CONF_MAX_LINES) {
        setzero(buf, PATH_MAX+1);
        fgets(buf, PATH_MAX, fd);
        e++;

        if(feof(fd))
            break;

        str=buf;
        while(isspace(*str))
            str++;
        if(*str=='#' || !*str) {
            /* Strip off any comment or null lines */
            continue;
        } else {
            /* Remove the last part of the string where a side
             * comment starts, 	#a comment like this.
             */
            if((p=strrchr(str, '#')))
                *p='\0';

            /* Don't include the newline and spaces of the end of
             * the string */
            slen=strlen(str);
            for(p=&str[slen-1]; isspace(*p); p--)
                *p='\0';


            parse_config_line(file, e, str);
            i++;
        }
    }

    fclose(fd);

    return 0;
}