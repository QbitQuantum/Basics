/*
========================
idJoystickWin32::PollInputEvents
========================
*/
int idJoystickWin32::PollInputEvents( int inputDeviceNum )
{
	numEvents = 0;
	
	if( !win32.activeApp )
	{
		return numEvents;
	}
	
	assert( inputDeviceNum < 4 );
	
//	if ( inputDeviceNum > in_joystick.GetInteger() ) {
//		return numEvents;
//	}

	controllerState_t* cs = &controllers[ inputDeviceNum ];
	
	// grab the current packet under a critical section
	XINPUT_STATE xis;
	XINPUT_STATE old;
	int		orBits;
	{
		idScopedCriticalSection crit( mutexXis );
		xis = cs->current;
		old = cs->previous;
		cs->previous = xis;
		// fetch or'd button bits
		orBits = cs->buttonBits;
		cs->buttonBits = 0;
	}
#if 0
	if( XInputGetState( inputDeviceNum, &xis ) != ERROR_SUCCESS )
	{
		return numEvents;
	}
#endif
	for( int i = 0 ; i < 32 ; i++ )
	{
		int	bit = 1 << i;
		
		if( ( ( xis.Gamepad.wButtons | old.Gamepad.wButtons ) & bit ) == 0
				&& ( orBits & bit ) )
		{
			idLib::Printf( "Dropped button press on bit %i\n", i );
		}
	}
	
	if( session->IsSystemUIShowing() )
	{
		// memset xis so the current input does not get latched if the UI is showing
		memset( &xis, 0, sizeof( XINPUT_STATE ) );
	}
	
	int joyRemap[16] =
	{
		J_DPAD_UP,		J_DPAD_DOWN,	// Up, Down
		J_DPAD_LEFT,	J_DPAD_RIGHT,	// Left, Right
		J_ACTION9,		J_ACTION10,		// Start, Back
		J_ACTION7,		J_ACTION8,		// Left Stick Down, Right Stick Down
		J_ACTION5,		J_ACTION6,		// Black, White (Left Shoulder, Right Shoulder)
		0,				0,				// Unused
		J_ACTION1,		J_ACTION2,		// A, B
		J_ACTION3,		J_ACTION4,		// X, Y
	};
	
	// Check the digital buttons
	for( int i = 0; i < 16; i++ )
	{
		int mask = ( 1 << i );
		if( ( xis.Gamepad.wButtons & mask ) != ( old.Gamepad.wButtons & mask ) )
		{
			PostInputEvent( inputDeviceNum, joyRemap[i], ( xis.Gamepad.wButtons & mask ) > 0 );
		}
	}
	
	// Check the triggers
	if( xis.Gamepad.bLeftTrigger != old.Gamepad.bLeftTrigger )
	{
		PostInputEvent( inputDeviceNum, J_AXIS_LEFT_TRIG, xis.Gamepad.bLeftTrigger * 128 );
	}
	if( xis.Gamepad.bRightTrigger != old.Gamepad.bRightTrigger )
	{
		PostInputEvent( inputDeviceNum, J_AXIS_RIGHT_TRIG, xis.Gamepad.bRightTrigger * 128 );
	}
	
	if( xis.Gamepad.sThumbLX != old.Gamepad.sThumbLX )
	{
		PostInputEvent( inputDeviceNum, J_AXIS_LEFT_X, xis.Gamepad.sThumbLX );
	}
	if( xis.Gamepad.sThumbLY != old.Gamepad.sThumbLY )
	{
		PostInputEvent( inputDeviceNum, J_AXIS_LEFT_Y, -xis.Gamepad.sThumbLY );
	}
	if( xis.Gamepad.sThumbRX != old.Gamepad.sThumbRX )
	{
		PostInputEvent( inputDeviceNum, J_AXIS_RIGHT_X, xis.Gamepad.sThumbRX );
	}
	if( xis.Gamepad.sThumbRY != old.Gamepad.sThumbRY )
	{
		PostInputEvent( inputDeviceNum, J_AXIS_RIGHT_Y, -xis.Gamepad.sThumbRY );
	}
	
	return numEvents;
}