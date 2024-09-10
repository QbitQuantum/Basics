        WriteResult writeRGBStream(const osg::Image& img, std::ostream &fout, const std::string& name) const
        {
            rawImageRec raw;
            raw.imagic = 0732;

            GLenum dataType = img.getDataType();

            raw.type  = dataType == GL_UNSIGNED_BYTE ? 1 :
                dataType == GL_BYTE ? 1 :
                dataType == GL_BITMAP ? 1 :
                dataType == GL_UNSIGNED_SHORT ? 2 :
                dataType == GL_SHORT ? 2 :
                dataType == GL_UNSIGNED_INT ? 4 :
                dataType == GL_INT ? 4 :
                dataType == GL_FLOAT ? 4 :
                dataType == GL_UNSIGNED_BYTE_3_3_2 ? 1 :
                dataType == GL_UNSIGNED_BYTE_2_3_3_REV ? 1 :
                dataType == GL_UNSIGNED_SHORT_5_6_5 ? 2 :
                dataType == GL_UNSIGNED_SHORT_5_6_5_REV ? 2 :
                dataType == GL_UNSIGNED_SHORT_4_4_4_4 ? 2 :
                dataType == GL_UNSIGNED_SHORT_4_4_4_4_REV ? 2 :
                dataType == GL_UNSIGNED_SHORT_5_5_5_1 ? 2 :
                dataType == GL_UNSIGNED_SHORT_1_5_5_5_REV ? 2 :
                dataType == GL_UNSIGNED_INT_8_8_8_8 ? 4 :
                dataType == GL_UNSIGNED_INT_8_8_8_8_REV ? 4 :
                dataType == GL_UNSIGNED_INT_10_10_10_2 ? 4 :
                dataType == GL_UNSIGNED_INT_2_10_10_10_REV ? 4 : 4;

            GLenum pixelFormat = img.getPixelFormat();

            raw.dim    = 3;
            raw.sizeX = img.s();
            raw.sizeY = img.t();
            raw.sizeZ =
                pixelFormat == GL_COLOR_INDEX? 1 :
                pixelFormat == GL_RED? 1 :
                pixelFormat == GL_GREEN? 1 :
                pixelFormat == GL_BLUE? 1 :
                pixelFormat == GL_ALPHA? 1 :
                pixelFormat == GL_RGB? 3 :
                pixelFormat == GL_BGR ? 3 :
                pixelFormat == GL_RGBA? 4 :
                pixelFormat == GL_BGRA? 4 :
                pixelFormat == GL_LUMINANCE? 1 :
                pixelFormat == GL_LUMINANCE_ALPHA ? 2 : 1;
            raw.min = 0;
            raw.max = 0xFF;
            raw.wasteBytes = 0;
            strncpy( raw.name, name.c_str(), 80);
            raw.colorMap = 0;
            raw.bpc = (img.getPixelSizeInBits()/raw.sizeZ)/8;

            int isize = img.getImageSizeInBytes();
            unsigned char *buffer = new unsigned char[isize];
            if(raw.bpc == 1)
            {
                unsigned char *dptr = buffer;
                int i, j;
                for( i = 0; i < raw.sizeZ; ++i )
                {
                    const unsigned char *ptr = img.data();
                    ptr += i;
                    for( j = 0; j < isize/raw.sizeZ; ++j )
                    {
                        *(dptr++) = *ptr;
                        ptr += raw.sizeZ;
                    }
                }
            }
            else
            { // bpc == 2
                unsigned short *dptr = reinterpret_cast<unsigned short*>(buffer);
                int i, j;
                for( i = 0; i < raw.sizeZ; ++i )
                {
                    const unsigned short *ptr = reinterpret_cast<const unsigned short*>(img.data());
                    ptr += i;
                    for( j = 0; j < isize/(raw.sizeZ*2); ++j )
                    {
                        *dptr = *ptr;
                        ConvertShort(dptr++, 1);
                        ptr += raw.sizeZ;
                    }
                }
            }

        
            if( raw.needsBytesSwapped() )
                raw.swapBytes();

            /*
            swapBytes( raw.imagic );
            swapBytes( raw.type );
            swapBytes( raw.dim );
            swapBytes( raw.sizeX );
            swapBytes( raw.sizeY );
            swapBytes( raw.sizeZ );
            swapBytes( raw.min );
            swapBytes( raw.max );
            swapBytes( raw.colorMap );
            */


            char pad[512 - sizeof(rawImageRec)];
            memset( pad, 0, sizeof(pad));

            fout.write((const char*)&raw,sizeof(rawImageRec));
            fout.write((const char*)pad,sizeof(pad));
            fout.write((const char*)buffer,isize);

            delete [] buffer;

            return WriteResult::FILE_SAVED;
        }