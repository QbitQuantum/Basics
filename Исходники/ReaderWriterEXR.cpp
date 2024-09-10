    bool writeEXRStream(const osg::Image &img, std::ostream& fout, const std::string &fileName) const
    {
        bool writeOK = true;

        //Obtain data from texture
        int width = img.s();
        int height = img.t();
        unsigned int pixelFormat = img.getPixelFormat();
        int numComponents = img.computeNumComponents(pixelFormat);
        unsigned int dataType = img.getDataType();

        //Validates image data
        //if numbers of components matches
        if (!(    numComponents == 3 ||
                  numComponents == 4))
        {
            writeOK = false;
            return false;
        }
        if (!(    dataType == GL_HALF_FLOAT_ARB ||
                  dataType == GL_FLOAT))
        {
            writeOK = false;
            return false;
        }

        //Create a stream to save to
        C_OStream outStream(&fout);

        //Copy data from texture to rgba pixel format
        Array2D<Rgba> outPixels(height,width);
        //If texture is half format
        if (dataType == GL_HALF_FLOAT_ARB)
        {
            half* pOut = (half*) img.data();
            for (long i = height-1; i >= 0; i--)
            {
                for (long j = 0 ; j < width; j++)
                {
                    outPixels[i][j].r = (*pOut);
                    pOut++;
                    outPixels[i][j].g = (*pOut);
                    pOut++;
                    outPixels[i][j].b = (*pOut);
                    pOut++;
                    if (numComponents >= 4)
                    {
                        outPixels[i][j].a = (*pOut);
                        pOut++;
                    }
                    else {
                        outPixels[i][j].a = 1.0f;
                    }
                }
            }
        }
        else if (dataType == GL_FLOAT)
        {
            float* pOut = (float*) img.data();
            for (long i = height-1; i >= 0; i--)
            {
                for (long j = 0 ; j < width; j++)
                {
                    outPixels[i][j].r = half(*pOut);
                    pOut++;
                    outPixels[i][j].g = half(*pOut);
                    pOut++;
                    outPixels[i][j].b = half(*pOut);
                    pOut++;
                    if (numComponents >= 4)
                    {
                        outPixels[i][j].a = half(*pOut);
                        pOut++;
                    }
                    else
                    {
                        outPixels[i][j].a = 1.0f;
                    }
                }
            }
        }
        else
        {
            //If texture format not supported
            return false;
        }

        try
        {
            //Write to stream
            Header outHeader(width, height);
            RgbaOutputFile rgbaFile (outStream, outHeader, WRITE_RGBA);
            rgbaFile.setFrameBuffer ((&outPixels)[0][0], 1, width);
            rgbaFile.writePixels (height);
        }
        catch( char * str )
        {
            writeOK = false;
        }


        return writeOK;
    }