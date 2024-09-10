void generate_temp_file(char *filename)
{
    /* gcc won't shut up if we use tmpnam() so we'll use mkstemp() if it is
     * likely to be available.
     */
#ifdef USE_MKSTEMP
    int fd;
    d_assign(filename, "make_doc_tmp.XXXXXX");
    fd = mkstemp(filename);
    if (fd == -1) {
        d_abort("could not generate temporary file name", "");
    }
    close(fd);
#else
    char *name = TEMPNAM(NULL, "make_doc_tmp.");
    if (!name) {
        d_abort("could not generate temporary file name", "");
    }
    d_assign(filename, name);
    free(name);
#endif
}