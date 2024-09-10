void r3dGamepad::GetState()
{
	isConnected = false;
	memcpy(&PrevState, &State, sizeof(XINPUT_STATE));

	leftTrigger = 0.0f;
	rightTrigger = 0.0f;
	leftThumbX = 0.0f;
	leftThumbY = 0.0f;
	rightThumbX = 0.0f;
	rightThumbY = 0.0f;

	if( XInputGetState( 0, &State ) == ERROR_SUCCESS )
	{
		isConnected = true;
		
		// left thumb
		{
			float LX = State.Gamepad.sThumbLX;
			float LY = State.Gamepad.sThumbLY;

			//determine how far the controller is pushed
			float magnitude = sqrt(LX*LX + LY*LY);
			if(magnitude == 0.0f) magnitude = 1.0f;

			//determine the direction the controller is pushed
			float normalizedLX = LX / magnitude;
			float normalizedLY = LY / magnitude;

			float normalizedMagnitude = 0;

			//check if the controller is outside a circular dead zone
			if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				//clip the magnitude at its expected maximum value
				if (magnitude > 32767) magnitude = 32767;

				//adjust magnitude relative to the end of the dead zone
				magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

				//optionally normalize the magnitude with respect to its expected range
				//giving a magnitude value of 0.0 to 1.0
				normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
			}
			else //if the controller is in the deadzone zero out the magnitude
			{
				magnitude = 0.0;
				normalizedMagnitude = 0.0;
			}

			leftThumbX = normalizedLX * normalizedMagnitude;
			leftThumbY = normalizedLY * normalizedMagnitude;
		}
		// right thumb
		{
			float LX = State.Gamepad.sThumbRX;
			float LY = State.Gamepad.sThumbRY;

			//determine how far the controller is pushed
			float magnitude = sqrt(LX*LX + LY*LY);
			if(magnitude == 0.0f) magnitude = 1.0f;

			//determine the direction the controller is pushed
			float normalizedLX = LX / magnitude;
			float normalizedLY = LY / magnitude;

			float normalizedMagnitude = 0;

			//check if the controller is outside a circular dead zone
			if (magnitude > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE )
			{
				//clip the magnitude at its expected maximum value
				if (magnitude > 32767) magnitude = 32767;

				//adjust magnitude relative to the end of the dead zone
				magnitude -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ;

				//optionally normalize the magnitude with respect to its expected range
				//giving a magnitude value of 0.0 to 1.0
				normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE );
			}
			else //if the controller is in the deadzone zero out the magnitude
			{
				magnitude = 0.0;
				normalizedMagnitude = 0.0;
			}

			rightThumbX = normalizedLX * normalizedMagnitude;
			rightThumbY = normalizedLY * normalizedMagnitude;
		}
		// trigger
		{
			float LX = State.Gamepad.bLeftTrigger;
			float LY = State.Gamepad.bRightTrigger;

			//determine how far the controller is pushed
			float magnitude = sqrt(LX*LX + LY*LY);
			if(magnitude == 0.0f) magnitude = 1.0f;

			//determine the direction the controller is pushed
			float normalizedLX = LX / magnitude;
			float normalizedLY = LY / magnitude;

			float normalizedMagnitude = 0;

			//check if the controller is outside a circular dead zone
			if (magnitude > XINPUT_GAMEPAD_TRIGGER_THRESHOLD )
			{
				//clip the magnitude at its expected maximum value
				if (magnitude > 255) magnitude = 255;

				//adjust magnitude relative to the end of the dead zone
				magnitude -= XINPUT_GAMEPAD_TRIGGER_THRESHOLD ;

				//optionally normalize the magnitude with respect to its expected range
				//giving a magnitude value of 0.0 to 1.0
				normalizedMagnitude = magnitude / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD );
			}
			else //if the controller is in the deadzone zero out the magnitude
			{
				magnitude = 0.0;
				normalizedMagnitude = 0.0;
			}

			leftTrigger = normalizedLX * normalizedMagnitude;
			rightTrigger = normalizedLY * normalizedMagnitude;
		}
	}
}