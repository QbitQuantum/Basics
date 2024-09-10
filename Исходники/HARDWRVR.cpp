void THardwareInfo::setScreenMode( ushort mode )
{
    COORD newSize = { 80, 25 };
    SMALL_RECT rect = { 0, 0, 79, 24 };

    if( mode & TDisplay::smFont8x8 )
        {
        newSize.Y = 50;
        rect.Bottom = 49;
        }

#if LIB_PLATFORM != LIB_PLATFORM_DPMI32
    COORD maxSize = GetLargestConsoleWindowSize( consoleHandle[cnOutput] );
    if( newSize.Y > maxSize.Y )
    {
        newSize.Y = maxSize.Y;
        rect.Bottom = newSize.Y-1;
    }
#endif

    if( mode & TDisplay::smFont8x8 )
        {
        SetConsoleScreenBufferSize( consoleHandle[cnOutput], newSize );
        SetConsoleWindowInfo( consoleHandle[cnOutput], True, &rect );
        }
    else
        {
        SetConsoleWindowInfo( consoleHandle[cnOutput], True, &rect );
        SetConsoleScreenBufferSize( consoleHandle[cnOutput], newSize );
        }

    GetConsoleScreenBufferInfo( consoleHandle[cnOutput], &sbInfo );
}