HRESULT 
InitDI8( TDI8Data* data )
{	
        DIPROPDWORD  dipdw; 
        dipdw.diph.dwSize = sizeof(DIPROPDWORD); 
        dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
        dipdw.diph.dwObj = 0; 
        dipdw.diph.dwHow = DIPH_DEVICE; 
        dipdw.dwData = MOUSE_BUFFERSIZE;

        /* Create The DI Object */
        if( DI_OK != DirectInput8Create( data->hInstance              ,  
                                         DIRECTINPUT_VERSION          , 
                                         ((REFIID)IID_IDirectInput8)  , 
                                         ((void**)&data->pDI)         , 
                                         NULL                         ) )
        {                                         
                return E_FAIL;
        }                
	
	/* Set up keyboard input */
	if( FAILED( data->pDI->CreateDevice( GUID_SysKeyboard , 
	                                     &data->pDIKeybrd , 
	                                     NULL             ) ) )
        {	                                     
		return E_FAIL;
        }
        
	if( FAILED( data->pDIKeybrd->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
	        return E_FAIL;
        }
                 
        dipdw.dwData = KEYBOARD_BUFFERSIZE;
        if( FAILED( data->pDIKeybrd->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
        {
                return E_FAIL;
        }        	        

        if( FAILED( data->pDIKeybrd->SetCooperativeLevel( data->hWnd                            , 
                                                          DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
        {                                                          
                return E_FAIL;
        }                

        if ( data->pDIKeybrd ) 
        {
                data->pDIKeybrd->Acquire(); 
        }                

        /* Set up mouse input */

        if( FAILED( data->pDI->CreateDevice( GUID_SysMouse   , 
                                             &data->pDIMouse , 
                                             NULL            ) ) )
        {                                             
                return E_FAIL;
        }                

        if( FAILED( data->pDIMouse->SetDataFormat( &c_dfDIMouse2 ) ) )
        {
                return E_FAIL;
        }
         
        dipdw.dwData = MOUSE_BUFFERSIZE; 
        if( FAILED( data->pDIMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
        {
                return E_FAIL;
        }

        if( FAILED( data->pDIMouse->SetCooperativeLevel( data->hWnd                         , 
                                                         DISCL_FOREGROUND | DISCL_EXCLUSIVE ) ) )
        {                                                         
                return E_FAIL;
        }                

        data->hMouse = CreateEvent( 0, 0, 0, 0 );

        if ( data->hMouse == NULL )
        {
                ShutdownDI8( data );
                return 0;
        }

        data->hr = data->pDIMouse->SetEventNotification( data->hMouse );

        if ( FAILED( data->hr ) )
        {
                ShutdownDI8( data );
                return 0;
        }

        if ( FAILED( data->hr ) )
        {
                ShutdownDI8( data );
                return 0;
        }

        if ( data->pDIMouse ) 
        {
                data->pDIMouse->Acquire();
        }                

	/*Set up Joystick input (Only the first joy) */
   /*
        if( FAILED( data->pDI->EnumDevices( DI8DEVCLASS_GAMECTRL  , 
                                            EnumJoysticksCallback , 
                                            (VOID*) data          , 
                                            DIEDFL_ATTACHEDONLY   ) ) )
        {
                return E_FAIL;
        }                

        if( FAILED( data->pDIJoy->SetDataFormat( &c_dfDIJoystick2 ) ) )
        {
                return E_FAIL;
        }                

        if( FAILED( data->pDIJoy->SetCooperativeLevel( data->hWnd                         ,  
                                                       DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
        {                                                       
                return E_FAIL;
        }                

        data->DIDevCaps.dwSize = sizeof( DIDEVCAPS );
        if ( FAILED( data->pDIJoy->GetCapabilities( &data->DIDevCaps ) ) )
        {
                return E_FAIL;
        }                

        if ( FAILED( data->pDIJoy->EnumObjects( EnumAxesCallback , 
                                                (VOID*) data     , 
                                                DIDFT_AXIS       ) ) )
        {                                                
                return E_FAIL;
        }                

        if( data->pDIJoy ) 
        {
                data->pDIJoy->Acquire();
        }
                    */
	return S_OK;
}