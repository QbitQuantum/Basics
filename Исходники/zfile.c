/* If `name' has a correct extension, try to list its contents and search for
   the first file with a proper extension; if found, extract it.  If this
   succeeds, return the name of the temporary file; if the archive file is
   valid but `write_mode' is non-zero, return a zero-length string; in all
   the other cases, return NULL.  */
static char *try_uncompress_archive(const char *name, int write_mode,
                                    const char *program,
                                    const char *listopts,
                                    const char *extractopts,
                                    const char *extension,
                                    const char *search)
{
#ifdef __riscos
    return NULL;
#else
    char *tmp_name = NULL;
    int l = strlen(name), nameoffset, found = 0, len;
    int exit_status;
    char *argv[8];
    FILE *fd;
    char tmp[1024];

    /* Do we have correct extension?  */
    len = strlen(extension);
    if (l <= len || strcasecmp(name + l - len, extension) != 0)
        return NULL;

    /* First run listing and search for first recognizeable extension.  */
    argv[0] = lib_stralloc(program);
    argv[1] = lib_stralloc(listopts);
    argv[2] = archdep_filename_parameter(name);
    argv[3] = NULL;

    ZDEBUG(("try_uncompress_archive: spawning `%s %s %s'",
            program, listopts, name));
    exit_status = archdep_spawn(program, argv, &tmp_name, NULL);

    lib_free(argv[0]);
    lib_free(argv[1]);
    lib_free(argv[2]);

    /* No luck?  */
    if (exit_status != 0) {
        ZDEBUG(("try_uncompress_archive: `%s %s' failed.", program,
                listopts));
        ioutil_remove(tmp_name);
        lib_free(tmp_name);
        return NULL;
    }

    ZDEBUG(("try_uncompress_archive: `%s %s' successful.", program,
            listopts));

    fd = fopen(tmp_name, MODE_READ);
    if (!fd) {
        ZDEBUG(("try_uncompress_archive: cannot read `%s %s' output.",
                program, tmp_name));
        ioutil_remove(tmp_name);
        lib_free(tmp_name);
        return NULL;
    }

    ZDEBUG(("try_uncompress_archive: searching for the first valid file."));

    /* Search for `search' first (if any) to see the offset where
       filename begins, then search for first recognizeable file.  */
    nameoffset = search ? -1 : 0;
    len = search ? strlen(search) : 0;
    while (!feof(fd) && !found) {
        fgets(tmp, 1024, fd);
        l = strlen(tmp);
        while (l > 0) {
            tmp[--l] = 0;
            if (nameoffset < 0 && l >= len &&
                    !strcasecmp(tmp + l - len, search) != 0) {
                nameoffset = l - 4;
            }
            if (nameoffset >= 0 && is_valid_extension(tmp, l, nameoffset)) {
                ZDEBUG(("try_uncompress_archive: found `%s'.",
                        tmp + nameoffset));
                found = 1;
                break;
            }
        }
    }

    fclose(fd);
    ioutil_remove(tmp_name);
    if (!found) {
        ZDEBUG(("try_uncompress_archive: no valid file found."));
        lib_free(tmp_name);
        return NULL;
    }

    /* This would be a valid ZIP file, but we cannot handle ZIP files in
       write mode.  Return a null temporary file name to report this.  */
    if (write_mode) {
        ZDEBUG(("try_uncompress_archive: cannot open file in write mode."));
        lib_free(tmp_name);
        return "";
    }

    /* And then file inside zip.  If we have a zipcode extract all of them
       to the same file. */
    argv[0] = lib_stralloc(program);
    argv[1] = lib_stralloc(extractopts);
    argv[2] = archdep_filename_parameter(name);
    if (is_zipcode_name(tmp + nameoffset)) {
        argv[3] = lib_stralloc(tmp + nameoffset);
        argv[4] = lib_stralloc(tmp + nameoffset);
        argv[5] = lib_stralloc(tmp + nameoffset);
        argv[6] = lib_stralloc(tmp + nameoffset);
        argv[7] = NULL;
        argv[3][0] = '1';
        argv[4][0] = '2';
        argv[5][0] = '3';
        argv[6][0] = '4';
    } else {
        argv[3] = archdep_quote_parameter(tmp + nameoffset);
        argv[4] = NULL;
    }

    ZDEBUG(("try_uncompress_archive: spawning `%s %s %s %s'.",
            program, extractopts, name, tmp + nameoffset));
    exit_status = archdep_spawn(program, argv, &tmp_name, NULL);

    lib_free(argv[0]);
    lib_free(argv[1]);
    lib_free(argv[2]);
    lib_free(argv[3]);
    if (is_zipcode_name(tmp + nameoffset)) {
        lib_free(argv[4]);
        lib_free(argv[5]);
        lib_free(argv[6]);
    }

    if (exit_status != 0) {
        ZDEBUG(("try_uncompress_archive: `%s %s' failed.",
                program, extractopts));
        ioutil_remove(tmp_name);
        lib_free(tmp_name);
        return NULL;
    }

    ZDEBUG(("try_uncompress_archive: `%s %s' successful.", program,
            tmp_name));
    return tmp_name;
#endif
}