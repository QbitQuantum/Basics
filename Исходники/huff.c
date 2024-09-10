/* Entry point for the program. Opens the file, and executes the mode specified by command line args */
int main(int argc, char* argv[])
{
    if(argc != 3 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-t") != 0))
    {
        printf("usage: huff [-c | -d | -t] file\n");
        return -1;
    }


    /* Execute the correct mode */
    if(strcmp(argv[1], "-c") == 0)
    {
        //append the extension to the name
        const char * extension = ".temp";
        char *tempFile = malloc(strlen(argv[2])+strlen(extension) + 1);
        strncpy(tempFile, argv[2], strlen(argv[2]));
        strcat(tempFile, extension);

        //RLE encode the file
        rle_encode(argv[2], tempFile);

        //create a vairiable to hold hold the file length
        unsigned long long fileLength = 0;

        //get a buffer of the contents of the file as a unsigned char*
        unsigned char *file_pointer = openFile(tempFile, &fileLength);

        //huff compress the output.
        compress(file_pointer, fileLength, argv[2]);
        free(file_pointer);
        //free(tempFile);
        remove(tempFile);

    }
    else if(strcmp(argv[1], "-d") == 0)
    {
        unsigned long long fileLength = 0;
        unsigned char *file_pointer = openFile(argv[2], &fileLength);
        decompress(file_pointer, fileLength, argv[2]);

        //remove the .hurl extension from the fileName;

        char *tempFileName = calloc(strlen(argv[2]), sizeof(char));
        strncpy(tempFileName, argv[2], strlen(argv[2]) - strlen(".hurl"));
        strncat(tempFileName, ".temp", sizeof(".temp"));

        char *outputFileName = calloc(sizeof(char), strlen(argv[2]));
        strncpy(outputFileName, argv[2], strlen(argv[2]));
        outputFileName[strlen(outputFileName) -5] = '\0';

        rle_decode(tempFileName, outputFileName);
        free(file_pointer);
        remove(tempFileName);
    }
    else if(strcmp(argv[1], "-t") == 0)
    {
        unsigned long long fileLength = 0;
        unsigned char *file_pointer = openFile(argv[2], &fileLength);
        print_table(file_pointer, fileLength, argv[2]);
        free(file_pointer);

    }

    // free(file_pointer);
    return 0;
}