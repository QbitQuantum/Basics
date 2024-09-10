/* Convert '.files' db to newest db. Returns 1 if a valid file is
 * found and could be converted, 0 in all other cases.
 *
 * '.files' is a text file which contains file records built up in the
 * following way:
 *      '<filename> <nick> <tm> <gots>\n'
 *      '- <comment>\n'
 *      '- <comment>\n'
 *      ...
 */
static int convert_old_files(char *path, char *newfiledb)
{
    FILE *f, *fdb;
    char *s, *fn, *nick, *tm, *s1;
    filedb_entry *fdbe = NULL;
    int in_file = 0, i;
    struct stat st;

    s = nmalloc(strlen(path) + 8);
    sprintf(s, "%s/.files", path);
    f = fopen(s, "r");
    my_free(s);
    if (f == NULL)
        return 0;

    fdb = fopen(newfiledb, "w+b");
    if (!fdb) {
        putlog(LOG_MISC, "(!) Can't create filedb in %s", newfiledb);
        fclose(f);
        return 0;
    }
    lockfile(fdb);
    lockfile(f);
    filedb_initdb(fdb);

    putlog(LOG_FILES, "*", FILES_CONVERT, path);
    /* Scan contents of .files and painstakingly create .filedb entries */
    while (!feof(f)) {
        s = nmalloc(121);
        s1 = s;
        fgets(s, 120, f);
        if (s[strlen(s) - 1] == '\n')
            s[strlen(s) - 1] = 0;
        if (!feof(f)) {
            fn = newsplit(&s1);
            rmspace(fn);
            if ((fn[0]) && (fn[0] != ';') && (fn[0] != '#')) {
                /* Not comment */
                if (fn[0] == '-') {
                    /* Adjust comment for current file */
                    if (in_file && fdbe) {
                        rmspace(s);
                        if (fdbe->desc) {
                            fdbe->desc = nrealloc(fdbe->desc,
                                                  strlen(fdbe->desc) + strlen(s) + 2);
                            strcat(fdbe->desc, "\n");
                        } else
                            fdbe->desc = nmalloc(strlen(s) + 2);
                        strcat(fdbe->desc, s);
                    }
                } else {
                    if (fdbe) {
                        /* File pending. Write to DB */
                        filedb_addfile(fdb, fdbe);
                        free_fdbe(&fdbe);
                    }
                    fdbe = malloc_fdbe();
                    in_file = 1;
                    nick = newsplit(&s1);
                    rmspace(nick);
                    tm = newsplit(&s1);
                    rmspace(tm);
                    rmspace(s1);
                    i = strlen(fn) - 1;
                    if (fn[i] == '/')
                        fn[i] = 0;
                    malloc_strcpy(fdbe->filename, fn);
                    malloc_strcpy(fdbe->uploader, nick);
                    fdbe->gots = atoi(s1);
                    fdbe->uploaded = atoi(tm);
                    sprintf(s, "%s/%s", path, fn);
                    if (stat(s, &st) == 0) {
                        /* File is okay */
                        if (S_ISDIR(st.st_mode)) {
                            fdbe->stat |= FILE_DIR;
                            if (nick[0] == '+') {
                                char x[100];

                                /* Only do global flags, it's an old one */
                                struct flag_record fr = { FR_GLOBAL, 0, 0, 0, 0, 0 };

                                break_down_flags(nick + 1, &fr, NULL);
                                build_flags(x, &fr, NULL);
                                /* We only want valid flags */
                                malloc_strcpy_nocheck(fdbe->flags_req, x);
                            }
                        }
                        fdbe->size = st.st_size;
                    } else
                        in_file = 0;        /* skip */
                }
            }
        }
        my_free(s);
    }
    if (fdbe) {
        /* File pending. Write to DB */
        filedb_addfile(fdb, fdbe);
        free_fdbe(&fdbe);
    }
    fseek(fdb, 0L, SEEK_END);
    unlockfile(f);
    unlockfile(fdb);
    fclose(fdb);
    fclose(f);
    return 1;
}