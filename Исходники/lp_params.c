MYBOOL __WINAPI write_params(lprec *lp, char *filename, char *options)
{
    int k, ret, params_written;
    FILE *fp, *fp0;
    int state = 0, looping, newline;
    char buf[4096], *filename0, *ptr1, *ptr2, *header = NULL;

    readoptions(options, &header);

    k = strlen(filename);
    filename0 = (char *) malloc(k + 1 + 1);
    strcpy(filename0, filename);
    ptr1 = strrchr(filename0, '.');
    ptr2 = strrchr(filename0, '\\');
    if((ptr1 == NULL) || ((ptr2 != NULL) && (ptr1 < ptr2)))
        ptr1 = filename0 + k;
    memmove(ptr1 + 1, ptr1, k + 1 - (int) (ptr1 - filename0));
    ptr1[0] = '_';
    if(rename(filename, filename0)) {
        switch(errno) {
        case ENOENT: /* File or path specified by oldname not found */
            FREE(filename0);
            filename0 = NULL;
            break;
        case EACCES: /* File or directory specified by newname already exists or could not be created (invalid path); or oldname is a directory and newname specifies a different path. */
            FREE(filename0);
            FREE(header);
            return(FALSE);
            break;
        }
    }

    if((fp = ini_create(filename)) == NULL)
        ret = FALSE;
    else {
        params_written = FALSE;
        newline = TRUE;
        if(filename0 != NULL) {
            fp0 = ini_open(filename0);
            if(fp0 == NULL) {
                rename(filename0, filename);
                FREE(filename0);
                FREE(header);
                return(FALSE);
            }
            looping = TRUE;
            while(looping) {
                switch(ini_readdata(fp0, buf, sizeof(buf), TRUE)) {
                case 0: /* End of file */
                    looping = FALSE;
                    break;
                case 1: /* header */
                    ptr1 = strdup(buf);
                    STRUPR(buf);
                    ptr2 = strdup(header);
                    STRUPR(ptr2);
                    if(strcmp(buf, ptr2) == 0) {
                        write_params1(lp, fp, ptr1, newline);
                        params_written = TRUE;
                        newline = TRUE;
                        state = 1;
                    }
                    else {
                        state = 0;
                        ini_writeheader(fp, ptr1, newline);
                        newline = TRUE;
                    }
                    FREE(ptr2);
                    FREE(ptr1);
                    break;
                case 2: /* data */
                    if(state == 0) {
                        ini_writedata(fp, NULL, buf);
                        newline = (*buf != 0);
                    }
                    break;
                }
            }
            ini_close(fp0);
        }

        if(!params_written)
            write_params1(lp, fp, header, newline);

        ini_close(fp);
        ret = TRUE;
    }

    if(filename0 != NULL) {
        remove(filename0);
        FREE(filename0);
    }

    FREE(header);

    return( (MYBOOL) ret );
}