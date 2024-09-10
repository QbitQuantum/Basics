		//*************************************************************//
		// CHECK FOR NEW CONTROLLERS
		bool InputManager::CheckForNewControllers( void )
		{
			// Sanity-check the wrapper's status
			assert( m_eStatus == E_INITIALIZED && "InputManager::CheckForNewControllers - wrapper has not been initialized" );
			if( m_eStatus != E_INITIALIZED )
				return false;

			// Read new gamepads (too slow to call every Update)
			std::vector< DIDEVICEINSTANCEW > instances;
			HRESULT hResult = m_pDirectInput->EnumDevices( DI8DEVCLASS_GAMECTRL, &EnumerateJoystick, &instances, DIEDFL_ATTACHEDONLY );
			if( FAILED( hResult ) )
			{
				// MESSAGE
				char szBuffer[ 128 ];
				_snprintf_s( szBuffer, 128, _TRUNCATE, "!!! InputManager::CheckForNewControllers - failed to enumerate DirectInput devices (0x%X) !!!\n", hResult );
				OutputDebugStringA( szBuffer );

				return false;
			}


			// Hold the current number of known devices
			unsigned int numKnown = m_vGamepads.size();


			// Initialize each device
			for( unsigned int i = 0; i < instances.size(); i++ )
			{
				// Has this device already been initialized?
				bool known = false;
				for( unsigned int j = 0; j < m_vGamepads.size(); j++ )
					if( instances[ i ].guidInstance == m_vGamepads[ j ].id )
					{
						known = true;
						break;
					}

				if( known == true )
					continue;


				// New device
				GamepadInfo info = { };
				info.id = instances[ i ].guidInstance;


				// Create the device
				hResult = m_pDirectInput->CreateDevice( info.id, &info.pDevice, nullptr );
				if( FAILED( hResult ) )
					continue;


				// Get the capabilities
				DIDEVCAPS capabilities;
				memset( &capabilities, 0, sizeof( capabilities ) );
				capabilities.dwSize = sizeof( capabilities );
				hResult = info.pDevice->GetCapabilities( &capabilities );
				if( FAILED( hResult ) )
					continue;

				if( capabilities.dwAxes > 4 )
					info.bHasTriggerAxis = true;


				// Set the cooperative level
				hResult = info.pDevice->SetCooperativeLevel( m_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
				if( FAILED( hResult ) )
					continue;
				

				// Set the data format (simple joystick)
				hResult = info.pDevice->SetDataFormat( &c_dfDIJoystick );
				if( FAILED( hResult ) )
					continue;


				// Set joystick axes properties: range / deadzone(min) / saturation(max)
				DIPROPRANGE range;
				range.lMin = -1000;
				range.lMax = +1000;
				range.diph.dwSize = sizeof( DIPROPRANGE );
				range.diph.dwHeaderSize = sizeof( DIPROPHEADER );
				range.diph.dwHow = DIPH_DEVICE;
				range.diph.dwObj = 0;

				info.pDevice->SetProperty( DIPROP_RANGE, &range.diph );

				
				DIPROPDWORD deadzone;
				deadzone.dwData = 1000;		// 10%  	- any movement less than deadzone threshold is min
				deadzone.diph.dwSize = sizeof( DIPROPDWORD );
				deadzone.diph.dwHeaderSize = sizeof( DIPROPHEADER );
				deadzone.diph.dwHow = DIPH_DEVICE;
				deadzone.diph.dwObj = 0;

				info.pDevice->SetProperty( DIPROP_DEADZONE, &deadzone.diph );

								
				DIPROPDWORD saturation;
				saturation.dwData = 9000;	// 90%  	- any movement greater than saturation threshold is max
				saturation.diph.dwSize = sizeof( DIPROPDWORD );
				saturation.diph.dwHeaderSize = sizeof( DIPROPHEADER );
				saturation.diph.dwHow = DIPH_DEVICE;
				saturation.diph.dwObj = 0;

				info.pDevice->SetProperty( DIPROP_SATURATION, &saturation.diph );
						


				// Acquire the joystick 
				hResult = info.pDevice->Acquire();

				// Ignore failure so the device registers; will be handled in Update
				//if( FAILED( hResult ) )
				//	continue;


				// Store the product name				
				info.wszName = _wcsdup( instances[ i ].tszProductName );

				// Store the gamepad
				m_vGamepads.push_back( info );
			}
					
			// Did a joystick initialization fail?
			if( m_vGamepads.size() != instances.size() )
			{
				// MESSAGE
				char szBuffer[ 128 ];
				_snprintf_s( szBuffer, 128, _TRUNCATE, "!!! InputManager::CheckForNewControllers - failed to initialize a DirectInput device !!!\n" );
				OutputDebugStringA( szBuffer );
			}


			// Was there a new joystick?
			return ( m_vGamepads.size() > numKnown );
		}