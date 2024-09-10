bool initKeyboard( HWND hWnd )
{
    // create the keyboard device
    HRESULT result = din->CreateDevice( GUID_SysKeyboard,    // the default keyboard ID being used
                                        &dinKeyboard,    // the pointer to the device interface
                                        NULL    // COM stuff, so we'll set it to NULL
                                      );
    
    if ( FAILED( result ) )
    {
        logg( "    ERROR: Unable to initialize keyboard." );
        return ( false );
    }
    
    if ( FAILED( dinKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) ) // set the data format to keyboard format
    {
        logg( "    ERROR: Unable to set keyboard data format." );
        return ( false );
    }
    
    // set the control you will have over the keyboard
    if ( FAILED( dinKeyboard->SetCooperativeLevel( hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) ) )
    {
        logg( "    ERROR: Unable to set keyboard cooperative level." );
        return ( false );
    }
    
    char** kn = keyNames;
    for ( unsigned short i = 0; i < MAX_KEYS; i++ )
        *kn++ = "";
    numKeys = 0;
    if ( FAILED( dinKeyboard->EnumObjects( &EnumKeysCallback, NULL, DIDFT_ALL ) ) )
    {
        logg( "    ERROR: Unable to enumerate keyboard keys." );
        return ( false );
    }
    
    return ( true );
}