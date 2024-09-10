int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s file\n", argv[0]);
        exit(1);
    }

    FILE* file;
    file = fopen(argv[1], "r");

    if (file)
    {
        // Get the filesize. Note: We still want to generate an empty bytecode
        // file when reading an empty input file.
        size_t filesize;
        fseek(file, 0L, SEEK_END);
        filesize = ftell(file);
        // Reset filehandle to the beginning of the file.
        fseek(file, 0L, SEEK_SET);

        // Allocate file buffer
        char* file_buffer = (char*)malloc(filesize);
        if (file_buffer)
        {
            size_t bytes_read = 0;

            while (!feof(file))
            {
                size_t count = fread(file_buffer, sizeof(char), filesize, file);

                if (ferror(file))
                {
                    printf("Error while reading the file.\n");
                }
                else
                {
                    bytes_read += count;
                }
            }

            if (bytes_read == filesize)
            {
                int result = generate_bytecode(file_buffer, bytes_read);
                if (!result)
                {
                    printf("Error during bytecode generation.\n");
                    exit(1);
                }
            }
            else if (filesize == 0)
            {
                // Create empty output file
            }
            else
            {
                printf("Error while reading the file: %d\n", bytes_read);
            }

            free(file_buffer);
        }
        else
        {
            printf("Memory allocation failure.\nCould not allocate %d bytes.\n", filesize);
        }

        // Close the filehandle.
        fclose(file);
    }
    else
    {
        printf("Could not open file %s.\n", argv[1]);
        exit(1);
    }
}