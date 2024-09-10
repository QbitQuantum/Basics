char *pdf_parse_string(struct pdf_struct *pdf, struct pdf_obj *obj, const char *objstart, size_t objsize, const char *str, char **endchar, struct pdf_stats_metadata *meta)
{
    const char *q = objstart;
    char *p1, *p2;
    size_t len, checklen;
    char *res = NULL;
    uint32_t objid;
    size_t i;

    /*
     * Yes, all of this is required to find the start and end of a potentially UTF-* string
     *
     * First, find the key of the key/value pair we're looking for in this object.
     * Second, determine whether the value points to another object (NOTE: this is sketchy behavior)
     * Third, attempt to determine if we're ASCII or UTF-*
     * If we're ASCII, just copy the ASCII string into a new heap-allocated string and return that
     * Fourth, Attempt to decode from UTF-* to UTF-8
     */

    if (str) {
        checklen = strlen(str);

        if (objsize < strlen(str) + 3)
            return NULL;

        for (p1=(char *)q; (size_t)(p1 - q) < objsize-checklen; p1++)
            if (!strncmp(p1, str, checklen))
                break;

        if ((size_t)(p1 - q) == objsize - checklen)
            return NULL;

        p1 += checklen;
    } else {
        p1 = (char *)q;
    }

    while ((size_t)(p1 - q) < objsize && isspace(p1[0]))
        p1++;

    if ((size_t)(p1 - q) == objsize)
        return NULL;

    /*
     * If str is non-null:
     *     We should be at the start of the string, minus 1
     * Else:
     *     We should be at the start of the string
     */

    p2 = (char *)(q + objsize);
    if (is_object_reference(p1, &p2, &objid)) {
        struct pdf_obj *newobj;
        char *begin, *p3;
        STATBUF sb;
        uint32_t objflags;
        int fd;
        size_t objsize2;

        newobj = find_obj(pdf, obj, objid);
        if (!(newobj))
            return NULL;

        if (newobj == obj)
            return NULL;

        /* 
         * If pdf_handlename hasn't been called for this object,
         * then parse the object prior to extracting it
         */
        if (!(newobj->statsflags & OBJ_FLAG_PDFNAME_DONE))
            pdf_parseobj(pdf, newobj);

        /* Extract the object. Force pdf_extract_obj() to dump this object. */
        objflags = newobj->flags;
        newobj->flags |= (1 << OBJ_FORCEDUMP);

        if (pdf_extract_obj(pdf, newobj, PDF_EXTRACT_OBJ_NONE) != CL_SUCCESS)
            return NULL;

        newobj->flags = objflags;

        if (!(newobj->path))
            return NULL;

        fd = open(newobj->path, O_RDONLY);
        if (fd == -1) {
            cli_unlink(newobj->path);
            free(newobj->path);
            newobj->path = NULL;
            return NULL;
        }

        if (FSTAT(fd, &sb)) {
            close(fd);
            cli_unlink(newobj->path);
            free(newobj->path);
            newobj->path = NULL;
            return NULL;
        }

        if (sb.st_size) {
            begin = calloc(1, sb.st_size+1);
            if (!(begin)) {
                close(fd);
                cli_unlink(newobj->path);
                free(newobj->path);
                newobj->path = NULL;
                return NULL;
            }

            if (read(fd, begin, sb.st_size) != sb.st_size) {
                close(fd);
                cli_unlink(newobj->path);
                free(newobj->path);
                newobj->path = NULL;
                free(begin);
                return NULL;
            }

            p3 = begin;
            objsize2 = sb.st_size;
            while ((size_t)(p3 - begin) < objsize2 && isspace(p3[0])) {
                p3++;
                objsize2--;
            }

            switch (*p3) {
                case '(':
                case '<':
                    res = pdf_parse_string(pdf, obj, p3, objsize2, NULL, NULL, meta);
                    break;
                default:
                    res = pdf_finalize_string(pdf, obj, begin, objsize2);
                    if (!res) {
                        res = cli_calloc(1, objsize2+1);
                        if (!(res)) {
                            close(fd);
                            cli_unlink(newobj->path);
                            free(newobj->path);
                            newobj->path = NULL;
                            free(begin);
                            return NULL;
                        }
                        memcpy(res, begin, objsize2);
                        res[objsize2] = '\0';

                        if (meta) {
                            meta->length = objsize2;
                            meta->obj = obj;
                            meta->success = 0;
                        }
                    } else if (meta) {
                        meta->length = strlen(res);
                        meta->obj = obj;
                        meta->success = 1;
                    }
            }
            free(begin);
        }

        close(fd);
        cli_unlink(newobj->path);
        free(newobj->path);
        newobj->path = NULL;

        if (endchar)
            *endchar = p2;

        return res;
    }

    if (*p1 == '<') {
        /* Hex string */

        p2 = p1+1;
        while ((size_t)(p2 - q) < objsize && *p2 != '>')
            p2++;

        if ((size_t)(p2 - q) == objsize) {
            return NULL;
        }


        res = pdf_finalize_string(pdf, obj, p1, (p2 - p1) + 1);
        if (!res) {
            res = cli_calloc(1, (p2 - p1) + 2);
            if (!(res))
                return NULL;
            memcpy(res, p1, (p2 - p1) + 1);
            res[(p2 - p1) + 1] = '\0';

            if (meta) {
                meta->length = (p2 - p1) + 1;
                meta->obj = obj;
                meta->success = 0;
            }
        } else if (meta) {
            meta->length = strlen(res);
            meta->obj = obj;
            meta->success = 1;
        }

        if (res && endchar)
            *endchar = p2;

        return res;
    }

    /* We should be at the start of a string literal (...) here */
    if (*p1 != '(')
        return NULL;

    /* Make a best effort to find the end of the string and determine if UTF-* */
    p2 = ++p1;
    while (p2 < objstart + objsize) {
        int shouldbreak=0;

        switch (*p2) {
            case '\\':
                p2++;
                break;
            case ')':
                shouldbreak=1;
                break;
        }

        if (shouldbreak) {
            p2--;
            break;
        }

        p2++;
    }

    if (p2 == objstart + objsize)
        return NULL;

    len = (size_t)(p2 - p1) + 1;

    res = pdf_finalize_string(pdf, obj, p1, len);
    if (!res) {
        res = cli_calloc(1, len+1);
        if (!(res))
            return NULL;
        memcpy(res, p1, len);
        res[len] = '\0';

        if (meta) {
            meta->length = len;
            meta->obj = obj;
            meta->success = 0;
        }
    } else if (meta) {
        meta->length = strlen(res);
        meta->obj = obj;
        meta->success = 1;
    }

    if (res && endchar)
        *endchar = p2;

    return res;
}