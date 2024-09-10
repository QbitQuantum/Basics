bool wxBMPHandler::DoLoadDib(wxImage * image, int width, int height,
                             int bpp, int ncolors, int comp,
                             wxFileOffset bmpOffset, wxInputStream& stream,
                             bool verbose, bool IsBmp, bool hasPalette)
{
    wxInt32         aDword, rmask = 0, gmask = 0, bmask = 0, amask = 0;
    int             rshift = 0, gshift = 0, bshift = 0, ashift = 0;
    int             rbits = 0, gbits = 0, bbits = 0;
    wxInt32         dbuf[4];
    wxInt8          bbuf[4];
    wxUint8         aByte;
    wxUint16        aWord;

    // allocate space for palette if needed:
    BMPPalette *cmap;

    if ( bpp < 16 )
    {
        cmap = new BMPPalette[ncolors];
        if ( !cmap )
        {
            if (verbose)
            {
                wxLogError(_("BMP: Couldn't allocate memory."));
            }
            return false;
        }
    }
    else // no palette
    {
        cmap = NULL;
    }

    wxON_BLOCK_EXIT1(&BMPPalette::Free, cmap);

    // destroy existing here instead of:
    image->Destroy();
    image->Create(width, height);

    unsigned char *ptr = image->GetData();

    if ( !ptr )
    {
        if ( verbose )
        {
            wxLogError( _("BMP: Couldn't allocate memory.") );
        }
        return false;
    }

    unsigned char *alpha;
    if ( bpp == 32 )
    {
        // tell the image to allocate an alpha buffer
        image->SetAlpha();
        alpha = image->GetAlpha();
        if ( !alpha )
        {
            if ( verbose )
            {
                wxLogError(_("BMP: Couldn't allocate memory."));
            }
            return false;
        }
    }
    else // no alpha
    {
        alpha = NULL;
    }

    // Reading the palette, if it exists:
    if ( bpp < 16 && ncolors != 0 )
    {
        unsigned char* r = new unsigned char[ncolors];
        unsigned char* g = new unsigned char[ncolors];
        unsigned char* b = new unsigned char[ncolors];
        for (int j = 0; j < ncolors; j++)
        {
            if (hasPalette)
            {
                stream.Read(bbuf, 4);
                cmap[j].b = bbuf[0];
                cmap[j].g = bbuf[1];
                cmap[j].r = bbuf[2];

                r[j] = cmap[j].r;
                g[j] = cmap[j].g;
                b[j] = cmap[j].b;
            }
            else
            {
                //used in reading .ico file mask
                r[j] = cmap[j].r =
                g[j] = cmap[j].g =
                b[j] = cmap[j].b = ( j ? 255 : 0 );
            }
        }

#if wxUSE_PALETTE
        // Set the palette for the wxImage
        image->SetPalette(wxPalette(ncolors, r, g, b));
#endif // wxUSE_PALETTE

        delete[] r;
        delete[] g;
        delete[] b;
    }
    else if ( bpp == 16 || bpp == 32 )
    {
        if ( comp == BI_BITFIELDS )
        {
            int bit;
            stream.Read(dbuf, 4 * 3);
            rmask = wxINT32_SWAP_ON_BE(dbuf[0]);
            gmask = wxINT32_SWAP_ON_BE(dbuf[1]);
            bmask = wxINT32_SWAP_ON_BE(dbuf[2]);
            // find shift amount (Least significant bit of mask)
            for (bit = bpp-1; bit>=0; bit--)
            {
                if (bmask & (1 << bit))
                    bshift = bit;
                if (gmask & (1 << bit))
                    gshift = bit;
                if (rmask & (1 << bit))
                    rshift = bit;
            }
            // Find number of bits in mask (MSB-LSB+1)
            for (bit = 0; bit < bpp; bit++)
            {
                if (bmask & (1 << bit))
                    bbits = bit-bshift+1;
                if (gmask & (1 << bit))
                    gbits = bit-gshift+1;
                if (rmask & (1 << bit))
                    rbits = bit-rshift+1;
            }
        }
        else if ( bpp == 16 )
        {
            rmask = 0x7C00;
            gmask = 0x03E0;
            bmask = 0x001F;
            rshift = 10;
            gshift = 5;
            bshift = 0;
            rbits = 5;
            gbits = 5;
            bbits = 5;
        }
        else if ( bpp == 32 )
        {
            rmask = 0x00FF0000;
            gmask = 0x0000FF00;
            bmask = 0x000000FF;
            amask = 0xFF000000;

            ashift = 24;
            rshift = 16;
            gshift = 8;
            bshift = 0;
            rbits = 8;
            gbits = 8;
            bbits = 8;
        }
    }

    /*
     * Reading the image data
     */
    if ( IsBmp )
    {
        // NOTE: seeking a positive amount in wxFromCurrent mode allows us to
        //       load even non-seekable streams (see wxInputStream::SeekI docs)!
        const wxFileOffset pos = stream.TellI();
        if (pos != wxInvalidOffset && bmpOffset > pos)
            if (stream.SeekI(bmpOffset - pos, wxFromCurrent) == wxInvalidOffset)
                return false;
        //else: icon, just carry on
    }

    unsigned char *data = ptr;

    /* set the whole image to the background color */
    if ( bpp < 16 && (comp == BI_RLE4 || comp == BI_RLE8) )
    {
        for (int i = 0; i < width * height; i++)
        {
            *ptr++ = cmap[0].r;
            *ptr++ = cmap[0].g;
            *ptr++ = cmap[0].b;
        }
        ptr = data;
    }

    int linesize = ((width * bpp + 31) / 32) * 4;

    /* BMPs are stored upside down */
    for ( int line = (height - 1); line >= 0; line-- )
    {
        int linepos = 0;
        for ( int column = 0; column < width ; )
        {
            if ( bpp < 16 )
            {
                linepos++;
                aByte = stream.GetC();
                if ( bpp == 1 )
                {
                    for (int bit = 0; bit < 8 && column < width; bit++)
                    {
                        int index = ((aByte & (0x80 >> bit)) ? 1 : 0);
                        ptr[poffset] = cmap[index].r;
                        ptr[poffset + 1] = cmap[index].g;
                        ptr[poffset + 2] = cmap[index].b;
                        column++;
                    }
                }
                else if ( bpp == 4 )
                {
                    if ( comp == BI_RLE4 )
                    {
                        wxUint8 first;
                        first = aByte;
                        aByte = stream.GetC();
                        if ( first == 0 )
                        {
                            if ( aByte == 0 )
                            {
                                if ( column > 0 )
                                    column = width;
                            }
                            else if ( aByte == 1 )
                            {
                                column = width;
                                line = -1;
                            }
                            else if ( aByte == 2 )
                            {
                                aByte = stream.GetC();
                                column += aByte;
                                linepos = column * bpp / 4;
                                aByte = stream.GetC();
                                line -= aByte; // upside down
                            }
                            else
                            {
                                int absolute = aByte;
                                wxUint8 nibble[2] ;
                                int readBytes = 0 ;
                                for (int k = 0; k < absolute; k++)
                                {
                                    if ( !(k % 2 ) )
                                    {
                                        ++readBytes ;
                                        aByte = stream.GetC();
                                        nibble[0] = (wxUint8)( (aByte & 0xF0) >> 4 ) ;
                                        nibble[1] = (wxUint8)( aByte & 0x0F ) ;
                                    }
                                    ptr[poffset    ] = cmap[nibble[k%2]].r;
                                    ptr[poffset + 1] = cmap[nibble[k%2]].g;
                                    ptr[poffset + 2] = cmap[nibble[k%2]].b;
                                    column++;
                                    if ( k % 2 )
                                        linepos++;
                                }
                                if ( readBytes & 0x01 )
                                    aByte = stream.GetC();
                            }
                        }
                        else
                        {
                            wxUint8 nibble[2] ;
                            nibble[0] = (wxUint8)( (aByte & 0xF0) >> 4 ) ;
                            nibble[1] = (wxUint8)( aByte & 0x0F ) ;

                            for ( int l = 0; l < first && column < width; l++ )
                            {
                                ptr[poffset    ] = cmap[nibble[l%2]].r;
                                ptr[poffset + 1] = cmap[nibble[l%2]].g;
                                ptr[poffset + 2] = cmap[nibble[l%2]].b;
                                column++;
                                if ( l % 2 )
                                    linepos++;
                            }
                        }
                    }