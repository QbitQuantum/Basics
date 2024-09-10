void WiimoteService::writeWiimoteEvent()
{
	Event* evt = writeHead();
	evt->reset(Event::Update, Service::Controller, myEventSourceId);

	// See if button state has changed and send Up / Down events accordingly. 
	// NOTE: this currently works correctly only if ONE button state changes during each
	// poll cycle.
	uint curButtonState = pollButtonState();
	if(curButtonState != myButtonState)
	{
		// If button state is bigger than previous state, it means one additional bit has been
		// set - so send a down event.
		if(curButtonState > myButtonState)
		{
			evt->reset(Event::Down, Service::Controller, myEventSourceId);
			if(isDebugEnabled()) omsg("Wiimote button down");
		}
		else
		{
			evt->reset(Event::Up, Service::Controller, myEventSourceId);
			if(isDebugEnabled()) omsg("Wiimote button up");
		}
		myButtonState = curButtonState;
	}
	else
	{
		// Button state has not changed, just send an update event.
		evt->reset(Event::Update, Service::Controller, myEventSourceId);
	}

	// Save digital information
	evt->setFlags(myButtonState);

	// Save analog information
	evt->setExtraDataType(Event::ExtraDataFloatArray);
	evt->setExtraDataFloat(0, myWiimote.Acceleration.X);
	evt->setExtraDataFloat(1, myWiimote.Acceleration.Y);
	evt->setExtraDataFloat(2, myWiimote.Acceleration.Z);
	evt->setExtraDataFloat(0, myWiimote.BatteryPercent);
}