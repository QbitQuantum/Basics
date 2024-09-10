static int image_extract(const char *input, const char *output)
{
    int fdi, ret;
    struct stat fdistat, fdostat;
    void *fdimap;
    char *focfgname;
    FILE *focfg;

    fdi = open(input, O_RDONLY);
    if (fdi < 0) {
        fprintf(stderr, "Cannot open input file %s: %m\n",
                input);
        return -1;
    }

    ret = fstat(fdi, &fdistat);
    if (ret < 0) {
        fprintf(stderr, "Cannot stat input file %s: %m\n",
                input);
        close(fdi);
        return -1;
    }

    fdimap = mmap(NULL, fdistat.st_size, PROT_READ, MAP_PRIVATE, fdi, 0);
    if (fdimap == MAP_FAILED) {
        fprintf(stderr, "Cannot map input file %s: %m\n",
                input);
        close(fdi);
        return -1;
    }

    close(fdi);

    ret = stat(output, &fdostat);
    if (ret < 0) {
        fprintf(stderr, "Cannot stat output directory %s: %m\n",
                output);
        munmap(fdimap, fdistat.st_size);
        return -1;
    }

    if (!S_ISDIR(fdostat.st_mode)) {
        fprintf(stderr, "Output %s should be a directory\n",
                output);
        munmap(fdimap, fdistat.st_size);
        return -1;
    }

    ret = asprintf(&focfgname, "%s/kwbimage.cfg", output);
    if (ret < 0) {
        fprintf(stderr, "Failed to allocate memory\n");
        munmap(fdimap, fdistat.st_size);
        return -1;
    }

    focfg = fopen(focfgname, "w+");
    if (!focfg) {
        fprintf(stderr, "Output file %s could not be created\n",
                focfgname);
        free(focfgname);
        munmap(fdimap, fdistat.st_size);
        return -1;
    }

    free(focfgname);

    if (image_version(fdimap) == 0)
        ret = image_extract_v0(fdimap, output, focfg);
    else if (image_version(fdimap) == 1)
        ret = image_extract_v1(fdimap, output, focfg);
    else {
        fprintf(stderr, "Invalid image version %d\n",
                image_version(fdimap));
        ret = -1;
    }

    fclose(focfg);
    munmap(fdimap, fdistat.st_size);
    return ret;
}