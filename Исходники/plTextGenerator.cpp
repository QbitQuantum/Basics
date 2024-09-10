void    plTextGenerator::FlushToHost( void )
{
#if HS_BUILD_FOR_WIN32
    // Flush the GDI first, to make sure it's done
    GdiFlush();

    // Now copy our alpha channel over. I hate the GDI
    uint32_t      i = fHost->fWidth * fHost->fHeight;
    uint32_t      *dest = fWinRGBBits;
    uint8_t       *src = fWinAlphaBits;

/*  while( i-- )
    {
        *dest &= 0x00ffffff;
        *dest |= ( *src ) << 24;
//      *dest |= ( *dest << 16 ) & 0xff000000;
        dest++;
        src++;
    }
*/
    do
    {
        i--;
        dest[ i ] &= 0x00ffffff;
        dest[ i ] |= src[ i ] << 24;
    } while( i );
#endif

    // Dirty the mipmap's deviceRef, if there is one
    if( fHost->GetDeviceRef() != nil )
        fHost->GetDeviceRef()->SetDirty( true );
}