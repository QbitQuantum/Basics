FWinRTInputInterface::FWinRTInputInterface( const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler )
	: MessageHandler( InMessageHandler )
	, ControllerScanTime( 0 )
	, InitialButtonRepeatDelay( 0 )
	, ButtonRepeatDelay( 0 )
	, NextControllerToScan( 0 )
{
	XInputEnable(true);
	FMemory::Memzero(WinRTKeyState, WinRTKeyCount);
	FMemory::Memzero(WinRTKeyLastState, WinRTKeyCount);
	FMemory::Memzero(WinRTCharState, WinRTKeyCount);
	FMemory::Memzero(WinRTCharLastState, WinRTKeyCount);

	for ( int32 ControllerIndex=0; ControllerIndex < MAX_NUM_XINPUT_CONTROLLERS; ++ControllerIndex )
	{
		FControllerState& ControllerState = ControllerStates[ControllerIndex];
		FMemory::Memzero( &ControllerState, sizeof(FControllerState) );

		ControllerState.ControllerId = ControllerIndex;
	}

	ControllerScanTime = 0.5f;
	InitialButtonRepeatDelay = 0.2f;
	ButtonRepeatDelay = 0.1f;

	// In the engine, all controllers map to xbox controllers for consistency 
	X360ToXboxControllerMapping[0] = 0;		// A
	X360ToXboxControllerMapping[1] = 1;		// B
	X360ToXboxControllerMapping[2] = 2;		// X
	X360ToXboxControllerMapping[3] = 3;		// Y
	X360ToXboxControllerMapping[4] = 4;		// L1
	X360ToXboxControllerMapping[5] = 5;		// R1
	X360ToXboxControllerMapping[6] = 7;		// Back 
	X360ToXboxControllerMapping[7] = 6;		// Start
	X360ToXboxControllerMapping[8] = 8;		// Left thumbstick
	X360ToXboxControllerMapping[9] = 9;		// Right thumbstick
	X360ToXboxControllerMapping[10] = 10;	// L2
	X360ToXboxControllerMapping[11] = 11;	// R2
	X360ToXboxControllerMapping[12] = 12;	// Dpad up
	X360ToXboxControllerMapping[13] = 13;	// Dpad down
	X360ToXboxControllerMapping[14] = 14;	// Dpad left
	X360ToXboxControllerMapping[15] = 15;	// Dpad right

	Buttons[0] = EControllerButtons::FaceButtonBottom;
	Buttons[1] = EControllerButtons::FaceButtonRight;
	Buttons[2] = EControllerButtons::FaceButtonLeft;
	Buttons[3] = EControllerButtons::FaceButtonTop;
	Buttons[4] = EControllerButtons::LeftShoulder;
	Buttons[5] = EControllerButtons::RightShoulder;
	Buttons[6] = EControllerButtons::SpecialRight;
	Buttons[7] = EControllerButtons::SpecialLeft;
	Buttons[8] = EControllerButtons::LeftThumb;
	Buttons[9] = EControllerButtons::RightThumb;
	Buttons[10] = EControllerButtons::LeftTriggerThreshold;
	Buttons[11] = EControllerButtons::RightTriggerThreshold;
	Buttons[12] = EControllerButtons::DPadUp;
	Buttons[13] = EControllerButtons::DPadDown;
	Buttons[14] = EControllerButtons::DPadLeft;
	Buttons[15] = EControllerButtons::DPadRight;
}