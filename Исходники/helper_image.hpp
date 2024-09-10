inline bool
__loadPPM(const char *file, unsigned char **data,
          unsigned int *w, unsigned int *h, unsigned int *channels)
{
    FILE *fp = NULL;

    if (FOPEN_FAIL(FOPEN(fp, file, "rb")))
    {
        std::cerr << "__LoadPPM() : Failed to open file: " << file << std::endl;
        return false;
    }

    // check header
    char header[PGMHeaderSize];

    if (fgets(header, PGMHeaderSize, fp) == NULL)
    {
        std::cerr << "__LoadPPM() : reading PGM header returned NULL" << std::endl;
        return false;
    }

    if (strncmp(header, "P5", 2) == 0)
    {
        *channels = 1;
    }
    else if (strncmp(header, "P6", 2) == 0)
    {
        *channels = 3;
    }
    else
    {
        std::cerr << "__LoadPPM() : File is not a PPM or PGM image" << std::endl;
        *channels = 0;
        return false;
    }

    // parse header, read maxval, width and height
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int maxval = 0;
    unsigned int i = 0;

    while (i < 3)
    {
        if (fgets(header, PGMHeaderSize, fp) == NULL)
        {
            std::cerr << "__LoadPPM() : reading PGM header returned NULL" << std::endl;
            return false;
        }

        if (header[0] == '#')
        {
            continue;
        }

        if (i == 0)
        {
            i += SSCANF(header, "%u %u %u", &width, &height, &maxval);
        }
        else if (i == 1)
        {
            i += SSCANF(header, "%u %u", &height, &maxval);
        }
        else if (i == 2)
        {
            i += SSCANF(header, "%u", &maxval);
        }
    }

    // check if given handle for the data is initialized
    if (NULL != *data)
    {
        if (*w != width || *h != height)
        {
            std::cerr << "__LoadPPM() : Invalid image dimensions." << std::endl;
        }
    }
    else
    {
        *data = (unsigned char *) malloc(sizeof(unsigned char) * width * height **channels);
        *w = width;
        *h = height;
    }

    // read and close file
    if (fread(*data, sizeof(unsigned char), width * height **channels, fp) == 0)
    {
        std::cerr << "__LoadPPM() read data returned error." << std::endl;
    }

    fclose(fp);

    return true;
}