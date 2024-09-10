    bool ExportTo8bppPNG( const gimg::tiled_image_i8bpp & in_indexed,
                          const std::string             & filepath,
                          unsigned int                    begpixX,
                          unsigned int                    begpixY,
                          unsigned int                    endpixX,
                          unsigned int                    endpixY )
    {
        png::image<png::index_pixel> output;
        output.set_palette( PalToPngPal(in_indexed.getPalette()) );
        const size_t srcMaxX = in_indexed.getNbPixelWidth()  - endpixX;
        const size_t srcMaxY = in_indexed.getNbPixelHeight() - endpixY;

        //Copy image
        output.resize( (srcMaxX - begpixX), (srcMaxY - begpixY) );

        for( unsigned int i = 0; i < output.get_width(); ++i )
        {
            for( unsigned int j = 0; j < output.get_height(); ++j )
            {
                size_t srcX = i + begpixX;
                size_t srcY = j + begpixY;

                if( srcX < srcMaxX && srcY < srcMaxY )
                    output.set_pixel( i,j, static_cast<uint8_t>( in_indexed.getPixel( srcX, srcY ).getWholePixelData() ) );
                else 
                    break;
            }
        }

        try
        {
            output.write( filepath );
        }
        catch( const std::exception & e )
        {
            cerr << "<!>- Error outputing image : " << filepath <<"\n"
                 << "     Exception details : \n"     
                 << "        " <<e.what()  <<"\n";

            assert(false);
            return false;
        }
        return true;
    }