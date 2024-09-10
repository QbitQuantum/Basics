int parse_nameservers(char *path, char **out_str, bool *has_localhost) {
    FILE *fd = NULL;
    char *buf = NULL;
    char *err = NULL;
    size_t buf_len, buf_used, nsl;
    char *p, *realloc_save;
    char line[1024];
    int rc = 0;

    *has_localhost = false;

    if ( !(buf = (char*)malloc(128)) ){
        rc = errno;
        if ( asprintf(out_str, "malloc: %s", strerror(errno)) == -1 ){
            err("asprintf: %s\n", strerror(errno));
            *out_str = NULL;
        }
        goto done;
    }
    buf[0] = '\0';
    buf_used = 1;
    buf_len = 128;

    if ( !(fd = fopen(path, "r")) ){
        rc = errno;
        if ( asprintf(out_str, "fopen(%s): %s", path, strerror(errno)) == -1 ){
            err("asprintf: %s\n", strerror(errno));
            *out_str = NULL;
        }
        goto done;
    }

    while ( fgets(line, 1024, fd) ){
        if ( strnlen(line, 1023) >= 1023 ) {
            rc = EINVAL;
            err = "Parse error, line too long";
            break;
        }
       
        if ( strncmp(line, "nameserver", strlen("nameserver")) )
            continue;

        if ( !( p = strtok(line, "\t ")) 
                || !(p = strtok(NULL, "\t \n"))
                || (nsl = strnlen(p, 31)) >= 31 ) {
            rc = EINVAL;
            err = "Parse error, invalid nameserver";
            break;
        }
       
        if ( buf_len < buf_used + nsl + 1 ){
            realloc_save = realloc(buf, buf_len + 128);
            if ( !realloc_save ){
                rc = errno;
                free(buf);
                if ( asprintf(out_str, "realloc: %s", strerror(errno)) == -1 ){
                    err("asprintf: %s\n", strerror(errno));
                }
                goto done;
            }
            buf = realloc_save;
            buf_len += 128;
        }
        sprintf(buf+buf_used-1, "%s\n", p);
        buf_used += nsl+1;
 
        if ( !strncmp(p, "127.0.0.1", 10) )
            *has_localhost = true;
    }

    if ( err != NULL ){
        if ( asprintf(out_str, "%s\n", err) == -1 ){
            err("asprintf: %s\n", strerror(errno));
            *out_str = NULL;
        }
        goto done;
    } 

    if ( !(*out_str = strdup(buf)) ){
        if ( asprintf(out_str, "strdup: %s", strerror(errno)) == -1 ){
            err("asprintf: %s\n", strerror(errno));
            *out_str = NULL;
        }
        goto done;
    }
    free(buf);
    buf = NULL;
    fclose(fd);
    fd = NULL;

done:
    if ( buf )
        free(buf);
    if ( fd )
        fclose(fd);
    return rc;
} 