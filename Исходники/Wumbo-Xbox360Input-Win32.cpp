	void Xbox360Input_Win32::update()
	{
        DWORD dwResult;
        XINPUT_STATE state;
        for(int id=0;id<MAX_CONTROLLERS;id++)
        {
			ZeroMemory(&state,sizeof(XINPUT_STATE));
			dwResult = XInputGetState(id,&state);
			if (dwResult == ERROR_SUCCESS)
			{
				bConnected[id] = true;
				//printf("XBOX -- Controller %i connected\n",id);
				if (state.dwPacketNumber != dwPacketNumber[id])
				{
					fLeftTrigger[id] = (float) (state.Gamepad.bLeftTrigger-XINPUT_GAMEPAD_TRIGGER_THRESHOLD < 0 ? 0 : state.Gamepad.bLeftTrigger-XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / (float) (255-XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
					fRightTrigger[id] = (float) (state.Gamepad.bRightTrigger-XINPUT_GAMEPAD_TRIGGER_THRESHOLD < 0 ? 0 : state.Gamepad.bRightTrigger-XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / (float) (255-XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
					bool neg = false;
					SHORT thumbRawX, thumbRawY;
					SHORT fixedX, fixedY, deadzone;
					fixedX = -1000;
					fixedY = -1000;
					thumbRawX = state.Gamepad.sThumbLX;
					thumbRawY = state.Gamepad.sThumbLY;
					//printf("XBOX -- Controller %i raw left thumb values: %i %i\n",id,state.Gamepad.sThumbLX,state.Gamepad.sThumbLY);
					deadzone = 32767-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
					if (thumbRawX < 0)
						if (thumbRawX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
							fixedX = 0;
					if (thumbRawX > 0)
						if (thumbRawX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
							fixedX = 0;
					if (thumbRawX < 0 && fixedX == -1000)
						fixedX = thumbRawX+XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
					if (thumbRawX > 0 && fixedX == -1000)
						fixedX = thumbRawX-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

					if (thumbRawY < 0)
						if (thumbRawY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
							fixedY = 0;
					if (thumbRawY > 0)
						if (thumbRawY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
							fixedY = 0;
					if (thumbRawY < 0 && fixedY == -1000)
						fixedY = thumbRawY+XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
					if (thumbRawY > 0 && fixedY == -1000)
						fixedY = thumbRawY-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
					if (fixedX != -1000)
						fThumbLX[id] = abs((float)(fixedX)) / (float)(deadzone) * (thumbRawX < 0 ? -1 : 1);
					if (fixedY != -1000)
						fThumbLY[id] = abs((float)(fixedY)) / (float)(deadzone) * (thumbRawY < 0 ? 1 : -1);

					//printf("XBOX -- Controller %i fixed left thumb values: %f %f\n",id,fThumbLX[id],fThumbLY[id]);


					fixedX = -1000;
					fixedY = -1000;
					thumbRawX = state.Gamepad.sThumbRX;
					thumbRawY = state.Gamepad.sThumbRY;
					deadzone = 32767-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
					if (thumbRawX < 0)
						if (thumbRawX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
							fixedX = 0;
					if (thumbRawX > 0)
						if (thumbRawX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
							fixedX = 0;
					if (thumbRawX < 0 && fixedX == -1000)
						fixedX = thumbRawX+XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
					if (thumbRawX > 0 && fixedX == -1000)
						fixedX = thumbRawX-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

					if (thumbRawY < 0)
						if (thumbRawY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
							fixedY = 0;
					if (thumbRawY > 0)
						if (thumbRawY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
							fixedY = 0;
					if (thumbRawY < 0 && fixedY == -1000)
						fixedY = thumbRawY+XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
					if (thumbRawY > 0 && fixedY == -1000)
						fixedY = thumbRawY-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
					if (fixedX != -1000)
						fThumbRX[id] = abs((float)(fixedX)) / (float)(deadzone) * (thumbRawX < 0 ? -1 : 1);
					if (fixedY != -1000)
						fThumbRY[id] = abs((float)(fixedY)) / (float)(deadzone) * (thumbRawY < 0 ? 1 : -1);
					wButtons[id]  = state.Gamepad.wButtons;
				}
				dwPacketNumber[id] = state.dwPacketNumber;
			}
			else
				bConnected[id] = false;
        }
	}