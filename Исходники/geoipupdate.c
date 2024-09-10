static int gunzip_and_replace(geoipupdate_s * gu, const char *gzipfile,
                              const char *geoip_filename,
                              const char *expected_file_md5)
{
    gzFile gz_fh;
    FILE *fh = fopen(gzipfile, "rb");
    exit_if(NULL == fh, "Can't open %s\n", gzipfile);
    size_t bsize = 8096;
    char *buffer = (char *)xmalloc(bsize);
    ssize_t read_bytes = my_getline(&buffer, &bsize, fh);
    exit_if(-1 == fclose(fh), "Error closing stream: %s", strerror(errno));
    if (read_bytes < 0) {
        fprintf(stderr, "Read error %s\n", gzipfile);
        unlink(gzipfile);
        free(buffer);
        return ERROR;
    }
    const char *no_new_upd = "No new updates available";
    if (!strncmp(no_new_upd, buffer, strlen(no_new_upd))) {
        say_if(gu->verbose, "%s\n", no_new_upd);
        unlink(gzipfile);
        free(buffer);
        return OK;
    }
    if (strncmp(buffer, "\x1f\x8b", 2)) {
        // error not a zip file
        unlink(gzipfile);
        printf("%s is not a valid gzip file\n", gzipfile);
        return ERROR;
    }

    // We do this here as we have to check that there is an update before
    // we check for the header.
    exit_unless( 32 == strnlen(expected_file_md5, 33),
                 "Did not receive a valid expected database MD5 from server\n");

    char *file_path_test;
    xasprintf(&file_path_test, "%s.test", geoip_filename);
    say_if(gu->verbose, "Uncompress file %s to %s\n", gzipfile, file_path_test);
    gz_fh = gzopen(gzipfile, "rb");
    exit_if(gz_fh == NULL, "Can't open %s\n", gzipfile);
    FILE *fhw = fopen(file_path_test, "wb");
    exit_if(fhw == NULL, "Can't open %s\n", file_path_test);

    for (;; ) {
        int amt = gzread(gz_fh, buffer, bsize);
        if (amt == 0) {
            break;              // EOF
        }
        exit_if(amt == -1, "Gzip read error while reading from %s\n", gzipfile);
        exit_unless(fwrite(buffer, 1, amt, fhw) == (size_t)amt,
                    "Gzip write error\n");
    }
    exit_if(-1 == fclose(fhw), "Error closing stream: %s", strerror(errno));
    exit_if(gzclose(gz_fh) != Z_OK, "Gzip read error while closing from %s\n",
            gzipfile);
    free(buffer);

    char actual_md5[33];
    md5hex(file_path_test, actual_md5);
    exit_if(strncasecmp(actual_md5, expected_file_md5, 32),
            "MD5 of new database (%s) does not match expected MD5 (%s)",
            actual_md5, expected_file_md5);

    say_if(gu->verbose, "Rename %s to %s\n", file_path_test, geoip_filename);
    int err = rename(file_path_test, geoip_filename);
    exit_if(err, "Rename %s to %s failed\n", file_path_test, geoip_filename);

    // fsync directory to ensure the rename is durable
    int dirfd = open(gu->database_dir, O_DIRECTORY);
    exit_if(-1 == dirfd, "Error opening database directory: %s",
            strerror(errno));
    exit_if(-1 == fsync(dirfd), "Error syncing database directory: %s",
            strerror(errno));
    exit_if(-1 == close(dirfd), "Error closing database directory: %s",
            strerror(errno));
    exit_if(-1 == unlink(gzipfile), "Error unlinking %s: %s", gzipfile,
            strerror(errno));

    free(file_path_test);
    return OK;
}