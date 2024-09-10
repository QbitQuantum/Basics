/* Opens the filedb responsible to the specified directory.
 */
static FILE *filedb_open(char *path, int sort)
{
    char *s, *npath;
    FILE *fdb;
    filedb_top fdbt;
    struct stat st;

    if (count >= 2)
        putlog(LOG_MISC, "*", "(@) warning: %d open filedb's", count);
    npath = nmalloc(strlen(dccdir) + strlen(path) + 1);
    simple_sprintf(npath, "%s%s", dccdir, path);
    /* Use alternate filename if requested */
    if (filedb_path[0]) {
        char *s2;

        s2 = make_point_path(path);
        s = nmalloc(strlen(filedb_path) + strlen(s2) + 8);
        simple_sprintf(s, "%sfiledb.%s", filedb_path, s2);
        my_free(s2);
    } else {
        s = nmalloc(strlen(npath) + 10);
        simple_sprintf(s, "%s/.filedb", npath);
    }
    fdb = fopen(s, "r+b");
    if (!fdb) {
        if (convert_old_files(npath, s)) {
            fdb = fopen(s, "r+b");
            if (fdb == NULL) {
                putlog(LOG_MISC, "*", FILES_NOCONVERT, npath);
                my_free(s);
                my_free(npath);
                return NULL;
            }
            lockfile(fdb);
            filedb_update(npath, fdb, sort);
            count++;
            my_free(s);
            my_free(npath);
            return fdb;
        } else {
            filedb_top fdbt;

            /* Create new database and fix it up */
            fdb = fopen(s, "w+b");
            if (!fdb) {
                my_free(s);
                my_free(npath);
                return NULL;
            }
            lockfile(fdb);
            fdbt.version = FILEDB_NEWEST_VER;
            fdbt.timestamp = now;
            filedb_writetop(fdb, &fdbt);
            filedb_update(npath, fdb, sort);
            count++;
            my_free(s);
            my_free(npath);
            return fdb;
        }
    }

    lockfile(fdb);                /* Lock it from other bots */
    filedb_readtop(fdb, &fdbt);
    if (fdbt.version < FILEDB_NEWEST_VER) {
        if (!convert_old_db(&fdb, s)) {
            /* Conversion failed. Unlock file again and error out.
             * (convert_old_db() could have modified fdb, so check
             * for fdb != NULL.)
             */
            if (fdb)
                unlockfile(fdb);
            my_free(npath);
            my_free(s);
            return NULL;
        }
        filedb_update(npath, fdb, sort);
    }
    stat(npath, &st);
    /* Update filedb if:
     * + it's been 6 hours since it was last updated
     * + the directory has been visibly modified since then
     * (6 hours may be a bit often)
     */
    if (sort || ((now - fdbt.timestamp) > (6 * 3600)) ||
            (fdbt.timestamp < st.st_mtime) || (fdbt.timestamp < st.st_ctime))
        /* File database isn't up-to-date! */
        filedb_update(npath, fdb, sort & 1);
    else if ((now - fdbt.timestamp) > 300)
        filedb_mergeempty(fdb);

    count++;
    my_free(npath);
    my_free(s);
    return fdb;
}