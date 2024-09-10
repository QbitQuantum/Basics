int extract_fastfile(char * infilename, char * outfilename) {
    FILE *fd,
         *fdo  = NULL;

    uint32_t inlen,
             outlen;
    int i,
        files;

    char *file_input,
         *file_output,
         *file_offset;

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    file_input  = infilename;
    file_output = outfilename;
    file_offset = "0x15";

    printf("Extracting fastfile: %s\n", file_input);
    fd = fopen(file_input, "rb");
    if(!fd) std_err();

    if(minzip > INSZ) minzip = INSZ;
    if(minzip < 1)    minzip = 1;

    in       = malloc(INSZ);
    out      = malloc(OUTSZ);
    filebuff = malloc(FBUFFSZ);
    if(!in || !out || !filebuff) std_err();

    offset = get_num(file_offset);  // do not skip, needed for buffseek
    buffseek(fd, offset, SEEK_SET);

    z.zalloc = (alloc_func)0;
    z.zfree  = (free_func)0;
    z.opaque = (voidpf)0;
    if(inflateInit2(&z, zipwbits) != Z_OK) zlib_err(Z_INIT_ERROR);

    fdo = save_file(file_output);
    unzip(fd, &fdo, &inlen, &outlen);
    FCLOSE(fdo)

    printf("\n"
        "%u bytes compressed\n"
        "%u bytes extracted\n",
        inlen, outlen);

    FCLOSE(fdo)
    FCLOSE(fd)
    inflateEnd(&z);
    free(in);
    free(out);
    free(filebuff);
    return(0);
}