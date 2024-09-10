/*:::::*/
FBCALL FBSTRING *fb_UIntToStr ( unsigned int num )
{
    FBSTRING 	*dst;

    /* alloc temp string */
    dst = fb_hStrAllocTemp( NULL, sizeof( int ) * 3 );
    if( dst != NULL )
    {
        /* convert */
#ifdef HOST_MINGW
        _ultoa( num, dst->data, 10 );
#else
        sprintf( dst->data, "%u", num );
#endif
        fb_hStrSetLength( dst, strlen( dst->data ) );
    }
    else
        dst = &__fb_ctx.null_desc;

    return dst;
}