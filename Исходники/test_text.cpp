void SaveAsPPM(RefPtr<Gdk::Pixbuf> pix, const char* name_prefix)
{
    const char* fnam = TmpNam(0, name_prefix);
    io::stream strm(fnam, iof::def|iof::trunc);

    int wdh  = pix->get_width();
    int hgt  = pix->get_height();
    int rowstride = pix->get_rowstride();
    RGBA::Pixel* dat = (RGBA::Pixel*)pix->get_pixels(), *cur;
    BOOST_CHECK( pix->get_has_alpha() );

    strm << "P6\n" << wdh << " " << hgt << "\n255\n";
    for( int y=0; cur=dat, y<hgt; y++, dat = (RGBA::Pixel*)((char*)dat + rowstride) )
        for( int x=0; x<wdh; x++, cur++ )
        {
            strm << cur->red << cur->green << cur->blue;
        }
}