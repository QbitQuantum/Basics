void fb_ConsoleGetMaxWindowSize( int *cols, int *rows )
{
    COORD max = GetLargestConsoleWindowSize( __fb_out_handle );
    if( cols != NULL )
        *cols = (max.X==0 ? FB_SCRN_DEFAULT_WIDTH : max.X);
    if( rows != NULL )
        *rows = (max.Y==0 ? FB_SCRN_DEFAULT_HEIGHT : max.Y);
}