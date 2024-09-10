    //--------------------------------------------------------------
    Image::Ptr ReadImage(File* file, FileFormat::Enum ff, PixelFormat::Enum pf)
    {
        if (!file || (pf != PixelFormat::DontCare && pf < 0)) {
            return 0;
        }

        Image::Ptr image;

        switch (ff)
        {
            case FileFormat::BMP:
            {
                image = ReadBMP(file);
                break;
            }
            case FileFormat::PNG:
            {
                image = ReadPNG(file);
                break;
            }
            case FileFormat::JPEG:
            {
                image = ReadJPEG(file);
                break;
            }
            case FileFormat::AutoDetect:
            {
                int initial_pos = file->tell();

                // try reading as BMP
                image = ReadBMP(file);
                if (image) {
                    break;
                }

                file->seek(initial_pos);

                // try reading as PNG
                image = ReadPNG(file);
                if (image) {
                    break;
                }

                file->seek(initial_pos);

                // try reading as JPEG
                image = ReadJPEG(file);

                break;
            }
            default:
                return 0;
        }

        if (image && pf != PixelFormat::DontCare && image->getPixelFormat() != pf) {
            image = image->convert(pf);
        }

        return image;
    }