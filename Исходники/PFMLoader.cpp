Vector3*
PFMLoader::readPFMImage(const char * filename, int * width, int * height)
{
    FILE *infile = 0;
    float *lineBuffer = 0;
    Vector3 *img = 0;
    char junk;

    try
    {
        fopen_s(&infile, filename, "rb");
        if (!infile)
            throw std::runtime_error("cannot open file.");

        int a = fgetc(infile);
        int b = fgetc(infile);
        fgetc(infile);

        if ((a != 'P') || ((b != 'F') && (b != 'f')))
            throw std::runtime_error("not a PFM image file.");

        b = (b == 'F');		// 'F' = RGB,  'f' = monochrome

        fscanf_s(infile, "%d %d%c", width, height, &junk);
        if ((*width <= 0) || (*height <= 0))
            throw std::runtime_error("invalid width or height.");

        float scaleFactor;
        fscanf_s(infile, "%f%c", &scaleFactor, &junk);

        img = new Vector3[*width * *height];

        a = *width * (b ? 3 : 1);
        lineBuffer = new float[a];
        for (int y = 0; y < *height; ++y)
        {
            Vector3 *cur = &img[y * *width];
            if (fread(lineBuffer, sizeof(float), a, infile) != (size_t) a)
                throw std::runtime_error("cannot read pixel data.");

            float *temp = lineBuffer;
            for (int x = 0; x < *width; x++)
            {
                if (b)
                {   // color
                    (*cur)[0] = *temp++;
                    (*cur)[1] = *temp++;
                    (*cur)[2] = *temp++;

                    if (scaleFactor > 0.0)
                    {
                        bigEndianFloat((*cur)[0]);
                        bigEndianFloat((*cur)[1]);
                        bigEndianFloat((*cur)[2]);
                    }
                    else
                    {
                        littleEndianFloat((*cur)[0]);
                        littleEndianFloat((*cur)[1]);
                        littleEndianFloat((*cur)[2]);
                    }
                }
                else
                {   // black and white
                    float c = *temp++;

                    if (scaleFactor > 0.0)
                        bigEndianFloat (c);
                    else
                        littleEndianFloat (c);

                    (*cur)[0] = (*cur)[1] = (*cur)[2] = c;
                }
                cur++;
            }
        }

        delete [] lineBuffer;
        fclose(infile);

        return img;
    }
    catch (const std::exception &e)
    {
        printf("Unable to read image file \"%s\": %s",
               filename, e.what());
        delete [] lineBuffer;
        delete [] img;
        if (infile)
            fclose (infile);
        return 0;
    }
    catch (...)
    {
        printf("Unable to read image file \"%s\".", filename);
        delete [] lineBuffer;
        delete [] img;
        if (infile)
            fclose (infile);
        return 0;
    }
}