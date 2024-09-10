        WriteResult local_writeImage(std::ostream& fout,const osg::Image& img,const osgDB::ReaderWriter::Options* options) const
        {
            std::string my_errmsg;
            try
            {
                gta::header hdr;
                gta::compression compression = gta::zlib;
                if (options)
                {
                    std::istringstream iss(options->getOptionString());
                    std::string opt;
                    std::string compressionMethod;
                    while (iss >> opt)
                    {
                        if (opt == "COMPRESSION")
                        {
                            iss >> compressionMethod;
                        }
                    };
                    if (compressionMethod == "NONE")
                        compression = gta::none;
                    else if (compressionMethod == "ZLIB")
                        compression = gta::zlib;
                    else if (compressionMethod == "ZLIB1")
                        compression = gta::zlib1;
                    else if (compressionMethod == "ZLIB2")
                        compression = gta::zlib2;
                    else if (compressionMethod == "ZLIB3")
                        compression = gta::zlib3;
                    else if (compressionMethod == "ZLIB4")
                        compression = gta::zlib4;
                    else if (compressionMethod == "ZLIB5")
                        compression = gta::zlib5;
                    else if (compressionMethod == "ZLIB6")
                        compression = gta::zlib6;
                    else if (compressionMethod == "ZLIB7")
                        compression = gta::zlib7;
                    else if (compressionMethod == "ZLIB8")
                        compression = gta::zlib8;
                    else if (compressionMethod == "ZLIB9")
                        compression = gta::zlib9;
                    else if (compressionMethod == "BZIP2")
                        compression = gta::bzip2;
                    else if (compressionMethod == "XZ")
                        compression = gta::xz;
                }
                hdr.set_compression(compression);
                if (img.s() > 0 && img.t() <= 1 && img.r() <= 1)
                {
                    hdr.set_dimensions(img.s());
                }
                else if (img.s() > 0 && img.t() > 1 && img.r() <= 1)
                {
                    hdr.set_dimensions(img.s(), img.t());
                }
                else if (img.s() > 0 && img.t() > 1 && img.r() > 1)
                {
                    hdr.set_dimensions(img.s(), img.t(), img.r());
                }
                else
                {
                    my_errmsg = "Image has unsupported dimensions";
                    throw std::exception();
                }
                gta::type type;
                switch (img.getDataType())
                {
                case GL_BYTE:
                    type = gta::int8;
                    break;
                case GL_UNSIGNED_BYTE:
                    type = gta::uint8;
                    break;
                case GL_SHORT:
                    type = gta::int16;
                    break;
                case GL_UNSIGNED_SHORT:
                    type = gta::uint16;
                    break;
                case GL_INT:
                    type = gta::int32;
                    break;
                case GL_UNSIGNED_INT:
                    type = gta::uint32;
                    break;
                case GL_FLOAT:
                    type = gta::float32;
                    break;
                default:
                    my_errmsg = "Image has unsupported data type";
                    throw std::exception();
                }
                switch (img.getPixelFormat())
                {
                case 1:
                case GL_DEPTH_COMPONENT:
                case GL_LUMINANCE:
                case GL_ALPHA:
                    hdr.set_components(type);
                    break;
                case 2:
                case GL_LUMINANCE_ALPHA:
                    hdr.set_components(type, type);
                    break;
                case 3:
                case GL_RGB:
                    hdr.set_components(type, type, type);
                    break;
                case 4:
                case GL_RGBA:
                    hdr.set_components(type, type, type, type);
                    break;
                default:
                    my_errmsg = "Image has unsupported pixel format";
                    throw std::exception();
                }
                if (img.getPacking() != 1)
                {
                    my_errmsg = "Image has unsupported packing";
                    throw std::exception();
                }
                hdr.write_to(fout);
#if 0   /* Does not seem to be necessary */
                if (img.t() > 1 && img.getOrigin() == osg::Image::BOTTOM_LEFT)
                {
                    int depth = (img.r() >= 1 ? img.r() : 1);
                    const unsigned char* data = static_cast<const unsigned char*>(img.getDataPointer());
                    size_t row_size = hdr.element_size() * img.s();
                    gta::io_state io_state;
                    for (int k = 0; k < depth; k++)
                    {
                        const unsigned char* slice = data + k * (row_size * img.t());
                        for (int j = 0; j < img.t(); j++)
                        {
                            const unsigned char* p = slice + (img.t() - 1 - j) * row_size;
                            hdr.write_elements(io_state, fout, img.s(), p);
                        }
                    }
                }
                else
                {
                    hdr.write_data(fout, img.getDataPointer());
                }
#endif
                hdr.write_data(fout, img.getDataPointer());
            }