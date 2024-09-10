float roundf( float f ) {
    if( f < 0.0f ) return truncf( f-0.5f );
    return truncf( f+0.5f );
}