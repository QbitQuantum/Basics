void InputHandler_DInput::Update(float fDeltaTime)
{
	RageTimer zero;
	zero.SetZero();

	/* Handle polled devices. */
	PollAndAcquireDevices();
	for( unsigned i = 0; i < Devices.size(); ++i )
	{
		if( !Devices[i].buffered )
			UpdatePolled( Devices[i], zero );
		else if( !InputThread.IsCreated() )
		{
			/* If we have an input thread, it'll handle buffered devices. */
			UpdateBuffered( Devices[i], zero );
		}
	}

	InputHandler::UpdateTimer();
}