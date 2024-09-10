static vi_key ConvertWierdCharacter( WORD vk, WORD data )
{
    unsigned char   keyboard_state[256];
    unsigned int    scancode = LOBYTE( data );
#if defined( __NT__ )
    WORD            newkey;
#else
    DWORD           newkey;
#endif

    GetKeyboardState( keyboard_state );
    if( ToAscii( vk, scancode, keyboard_state, &newkey, FALSE ) == 0 ) {
        return( 0 );
    }

    return( (vi_key)( newkey & 0xFF ) );
}