        bool ExportBMP( const _TImg_t     & in_indexed,
                        const std::string & filepath )
    {
        //shorten this static constant
        typedef utils::do_exponent_of_2_<_TImg_t::pixel_t::mypixeltrait_t::BITS_PER_PIXEL> NbColorsPP_t;
        BMP output;
        output.SetBitDepth(_TImg_t::pixel_t::GetBitsPerPixel());

        if( in_indexed.getNbColors() != NbColorsPP_t::value )
        {
#ifdef _DEBUG
            assert(false);
#endif
            throw std::runtime_error( "ERROR: The tiled image to write to a bitmap image file has an invalid amount of color in its palette!" );
        }
        //copy palette
        for( int i = 0; i < NbColorsPP_t::value; ++i )
            output.SetColor( i, colorRGB24ToRGBApixel( in_indexed.getPalette()[i] ) );

        //Copy image
        output.SetSize( in_indexed.getNbPixelWidth(), in_indexed.getNbPixelHeight() );

        for( int i = 0; i < output.TellWidth(); ++i )
        {
            for( int j = 0; j < output.TellHeight(); ++j )
            {
                auto &  refpixel = in_indexed.getPixel( i, j );
                uint8_t temp     = static_cast<uint8_t>( refpixel.getWholePixelData() );
                output.SetPixel( i,j, colorRGB24ToRGBApixel( in_indexed.getPalette()[temp] ) ); //We need to input the color directly thnaks to EasyBMP
            }
        }

        bool bsuccess = false;
        try
        {
            bsuccess = output.WriteToFile( filepath.c_str() );
        }
        catch( std::exception e )
        {
            cerr << "<!>- Error outputing image : " << filepath <<"\n"
                 << "     Exception details : \n"     
                 << "        " <<e.what()  <<"\n";

            assert(false);
            bsuccess = false;
        }
        return bsuccess;
    }