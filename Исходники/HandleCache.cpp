    // private
    //-------------------------------------------------------------------------
    Hash HandleCache::_CalculateHash( HCURSOR hcursor )
    {
        static const ULong HASH_BUFFER_LIMIT = KILOBYTES(8);
    
        ICONINFO    iconinfo = {0};
        LONG        count;
        Byte        buffer[HASH_BUFFER_LIMIT];

        // require valid
        if( hcursor == NULL )
            return 0;

        // get icon info
        if( GetIconInfo(hcursor, &iconinfo) == FALSE )
            return 0;

        // get icon bitmap buffer
        count = GetBitmapBits( iconinfo.hbmColor ? iconinfo.hbmColor : iconinfo.hbmMask, sizeof(buffer), buffer );

        // iconinfo cleanup 
        if( iconinfo.hbmColor )
            DeleteObject(iconinfo.hbmColor);
        if( iconinfo.hbmMask )
            DeleteObject(iconinfo.hbmMask);

        // fail if no bits read
        if(count == 0)
            return 0;

        // generate hash
        return Tools::Fnv164Hash(buffer, count);
    }