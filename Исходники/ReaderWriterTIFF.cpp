        WriteResult::WriteStatus writeTIFStream(std::ostream& fout, const osg::Image& img) const
        {
            //Code is based from the following article on CodeProject.com
            //http://www.codeproject.com/bitmap/BitmapsToTiffs.asp

            TIFF *image;
            int samplesPerPixel;
            int bitsPerSample;
            uint16 photometric;

            image = TIFFClientOpen("outputstream", "w", (thandle_t)&fout,
                                    libtiffOStreamReadProc, //Custom read function
                                    libtiffOStreamWriteProc, //Custom write function
                                    libtiffOStreamSeekProc, //Custom seek function
                                    libtiffStreamCloseProc, //Custom close function
                                    libtiffOStreamSizeProc, //Custom size function
                                    libtiffStreamMapProc, //Custom map function
                                    libtiffStreamUnmapProc); //Custom unmap function
            
            if(image == NULL)
            {
                return WriteResult::ERROR_IN_WRITING_FILE;
            }

            switch(img.getPixelFormat()) {
                case GL_LUMINANCE:
                case GL_ALPHA:
                    photometric = PHOTOMETRIC_MINISBLACK;
                    samplesPerPixel = 1;
                    break;
                case GL_LUMINANCE_ALPHA:
                    photometric = PHOTOMETRIC_MINISBLACK;
                    samplesPerPixel = 2;
                    break;
                case GL_RGB:
                    photometric = PHOTOMETRIC_RGB;
                    samplesPerPixel = 3;
                    break;
                case GL_RGBA:
                    photometric = PHOTOMETRIC_RGB;
                    samplesPerPixel = 4;
                    break;
                default:
                    return WriteResult::ERROR_IN_WRITING_FILE;
                    break;
            }

            switch(img.getDataType()){
                case GL_FLOAT:
                    TIFFSetField(image, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_IEEEFP);
                    TIFFSetField(image, TIFFTAG_ROWSPERSTRIP, 1);
                    bitsPerSample = 32;
                    break;
                default:
                    bitsPerSample = 8;
                    break;
            }

            TIFFSetField(image, TIFFTAG_IMAGEWIDTH,img.s());
            TIFFSetField(image, TIFFTAG_IMAGELENGTH,img.t());
            TIFFSetField(image, TIFFTAG_BITSPERSAMPLE,bitsPerSample);
            TIFFSetField(image, TIFFTAG_SAMPLESPERPIXEL,samplesPerPixel);
            TIFFSetField(image, TIFFTAG_PHOTOMETRIC, photometric);
            TIFFSetField(image, TIFFTAG_COMPRESSION, COMPRESSION_PACKBITS); 
            TIFFSetField(image, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
            TIFFSetField(image, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

            //uint32 rowsperstrip = TIFFDefaultStripSize(image, -1); 
            //TIFFSetField(image, TIFFTAG_ROWSPERSTRIP, rowsperstrip);
            
            // Write the information to the file
            for(int i = 0; i < img.t(); ++i) {
                TIFFWriteScanline(image,(tdata_t)img.data(0,img.t()-i-1),i,0);
            }

            // Close the file
            TIFFClose(image);

            return WriteResult::FILE_SAVED;
        }