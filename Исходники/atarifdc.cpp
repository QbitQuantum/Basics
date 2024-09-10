void atari_fdc_device::atari_load_proc(device_image_interface &image, bool is_created)
{
    int id = floppy_get_drive(image);
    int size, i;

    m_drv[id].image = std::make_unique<uint8_t[]>(MAXSIZE);
    if (!m_drv[id].image)
        return;

    /* tell whether the image is writable */
    m_drv[id].mode = !image.is_readonly();
    /* set up image if it has been created */
    if (is_created)
    {
        int sector;
        char buff[256];
        memset(buff, 0, sizeof(buff));
        /* default to 720 sectors */
        for( sector = 0; sector < 720; sector++ )
            image.fwrite(buff, 256);
        image.fseek(0, SEEK_SET);
    }

    size = image.fread(m_drv[id].image.get(), MAXSIZE);

    if( size <= 0 )
    {
        m_drv[id].image = nullptr;
        return;
    }


    /* re allocate the buffer; we don't want to be too lazy ;) */
    //m_drv[id].image = (uint8_t*)image.image_realloc(m_drv[id].image, size);

    // hack alert, this means we can only load ATR via the softlist at the moment, image.filetype returns "" :/
    bool is_softlist_entry = image.software_entry() != nullptr;

    /* no extension: assume XFD format (no header) */
    if (image.is_filetype("") && !is_softlist_entry)
    {
        m_drv[id].type = FORMAT_XFD;
        m_drv[id].header_skip = 0;
    }
    else
        /* XFD extension */
        if( image.is_filetype("xfd") )
        {
            m_drv[id].type = FORMAT_XFD;
            m_drv[id].header_skip = 0;
        }
        else
            /* ATR extension */
            if( image.is_filetype("atr") || is_softlist_entry)
            {
                m_drv[id].type = FORMAT_ATR;
                m_drv[id].header_skip = 16;
            }
            else
                /* DSK extension */
                if( image.is_filetype("dsk") )
                {
                    m_drv[id].type = FORMAT_DSK;
                    m_drv[id].header_skip = sizeof(atari_dsk_format);
                }
                else
                {
                    m_drv[id].type = FORMAT_XFD;
                    m_drv[id].header_skip = 0;
                }

    if( m_drv[id].type == FORMAT_ATR &&
            (m_drv[id].image[0] != 0x96 || m_drv[id].image[1] != 0x02) )
    {
        m_drv[id].type = FORMAT_XFD;
        m_drv[id].header_skip = 0;
    }


    switch (m_drv[id].type)
    {
    /* XFD or unknown format: find a matching size from the table */
    case FORMAT_XFD:
        for( i = 0; xfd_formats[i].size; i++ )
        {
            if( size == xfd_formats[i].size )
            {
                m_drv[id].density = xfd_formats[i].dsk.density;
                m_drv[id].tracks = xfd_formats[i].dsk.tracks;
                m_drv[id].spt = xfd_formats[i].dsk.spt;
                m_drv[id].heads = (xfd_formats[i].dsk.doublesided) ? 2 : 1;
                m_drv[id].bseclen = 128;
                m_drv[id].seclen = 256 * xfd_formats[i].dsk.seclen_hi + xfd_formats[i].dsk.seclen_lo;
                m_drv[id].sectors = m_drv[id].tracks * m_drv[id].heads * m_drv[id].spt;
                break;
            }
        }
        break;
    /* ATR format: find a size including the 16 bytes header */
    case FORMAT_ATR:
    {
        int s;
        m_drv[id].bseclen = 128;
        /* get sectors from ATR header */
        s = (size - 16) / 128;
        /* 3 + odd number of sectors ? */
        if ( m_drv[id].image[4] == 128 || (s % 18) == 0 || (s % 26) == 0 || ((s - 3) % 1) != 0 )
        {
            m_drv[id].sectors = s;
            m_drv[id].seclen = 128;
            /* sector size 128 or count not evenly dividable by 26 ? */
            if( m_drv[id].seclen == 128 || (s % 26) != 0 )
            {
                /* yup! single density */
                m_drv[id].density = 0;
                m_drv[id].spt = 18;
                m_drv[id].heads = 1;
                m_drv[id].tracks = s / 18;
                if( s % 18 != 0 )
                    m_drv[id].tracks += 1;
                if( m_drv[id].tracks % 2 == 0 && m_drv[id].tracks > 80 )
                {
                    m_drv[id].heads = 2;
                    m_drv[id].tracks /= 2;
                }
            }
            else
            {
                /* yes: medium density */
                m_drv[id].density = 0;
                m_drv[id].spt = 26;
                m_drv[id].heads = 1;
                m_drv[id].tracks = s / 26;
                if( s % 26 != 0 )
                    m_drv[id].tracks += 1;
                if( m_drv[id].tracks % 2 == 0 && m_drv[id].tracks > 80 )
                {
                    m_drv[id].heads = 2;
                    m_drv[id].tracks /= 2;
                }
            }
        }
        else
        {
            /* it's double density */
            s = (s - 3) / 2 + 3;
            m_drv[id].sectors = s;
            m_drv[id].density = 2;
            m_drv[id].seclen = 256;
            m_drv[id].spt = 18;
            m_drv[id].heads = 1;
            m_drv[id].tracks = s / 18;
            if( s % 18 != 0 )
                m_drv[id].tracks += 1;
            if( m_drv[id].tracks % 2 == 0 && m_drv[id].tracks > 80 )
            {
                m_drv[id].heads = 2;
                m_drv[id].tracks /= 2;
            }
        }
    }
    break;
    /* DSK format: it's all in the header */
    case FORMAT_DSK:
    {
        atari_dsk_format *dsk = (atari_dsk_format *) m_drv[id].image.get();

        m_drv[id].tracks = dsk->tracks;
        m_drv[id].spt = dsk->spt;
        m_drv[id].heads = (dsk->doublesided) ? 2 : 1;
        m_drv[id].seclen = 256 * dsk->seclen_hi + dsk->seclen_lo;
        m_drv[id].bseclen = m_drv[id].seclen;
        m_drv[id].sectors = m_drv[id].tracks * m_drv[id].heads * m_drv[id].spt;
    }
    break;
    }
    logerror("atari opened floppy '%s', %d sectors (%d %s%s) %d bytes/sector\n",
             image.filename(),
             m_drv[id].sectors,
             m_drv[id].tracks,
             (m_drv[id].heads == 1) ? "SS" : "DS",
             (m_drv[id].density == 0) ? "SD" : (m_drv[id].density == 1) ? "MD" : "DD",
             m_drv[id].seclen);
    return;
}