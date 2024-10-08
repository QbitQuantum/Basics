char *file2strl(
    const char *path,
    unsigned int *file_len_out
)
{
    FILE *file;


    if (!(file = fopen(path, "rb")))
    {
        fprintf(stderr, "Unable to open file %s\n", path);
        return NULL;
    }

    if (-1 == fseek(file, 0, SEEK_END))
    {
        fprintf(stderr, "Unable to seek file %s\n", path);
        fclose(file);
        return NULL;
    }

    unsigned long file_len;
    unsigned long bytes_read;
    if (-1 == (file_len = ftell(file)))
    {
        fprintf(stderr, "Unable to ftell() file %s\n", path);
        fclose(file);
        return NULL;
    }

    if (-1 == fseek(file, 0, SEEK_SET))
    {
        fprintf(stderr, "Unable to seek file %s\n", path);
        fclose(file);
        return NULL;
    }

    char *contents;
    if (!(contents = malloc(file_len + 1)))
    {
        fprintf(stderr, "Memory error!\n");
        fclose(file);
        return NULL;
    }

    bytes_read = fread(contents, file_len, 1, file);
    if(bytes_read == 0 && ferror(file)) {
        fprintf(stderr, "Read error");
        free(contents);
        fclose(file);
        return NULL;   
    }
    fclose(file);

    contents[file_len] = '\0';

    if (file_len_out)
        *file_len_out = file_len + 1;

    return contents;
}