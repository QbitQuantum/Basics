void Win360GamepadController::PollData() {
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(state));
	changeCount = 0;

	DWORD dwResult = XInputGetState(index, &state);
	DWORD timeStamp = GetTickCount();
	if (dwResult == ERROR_SUCCESS) {
		if (state.dwPacketNumber != prevState.dwPacketNumber) {
			// we have some changes we will need to register
			InputEventList& iel = inputEvents[currBuffer];
			
			if (state.Gamepad.wButtons != prevState.Gamepad.wButtons) {
				
				// insert button events
#define XBUTSTATE(state, i) (state.Gamepad.wButtons & (1 << i))

				for (uint32 i = 0; i < 16; ++i) {
					if (XBUTSTATE(state, i) != XBUTSTATE(prevState, i)) {
						if (buttonMap[i] != KeyName::KEY_INVALID_CODE) {
							InputEvent &ev = iel[changeCount++];
							KeyState k = buttonStates[buttonMap[i] - NEX_XB360_CTRL_BUTTON_START].value = XBUTSTATE(state, i) ? KeyState::KEY_STATE_DOWN : KeyState::KEY_STATE_UP;
							ev.key = buttonMap[i];
							ev.keyState = k;
							ev.timeStamp = timeStamp;
						}
					}
				}

#undef XBUTSTATE
			}

			if (state.Gamepad.bLeftTrigger != prevState.Gamepad.bLeftTrigger) {
				InputEvent &ev = iel[changeCount++];
				if (state.Gamepad.bLeftTrigger < triggerDeadZone)
					state.Gamepad.bLeftTrigger = 0;
				else
					state.Gamepad.bLeftTrigger -= triggerDeadZone;
				ev.analogValue = trigValues[0].value = (float)state.Gamepad.bLeftTrigger / (255.0f - triggerDeadZone);
				ev.key = KeyName::XBOX_TRIG_LEFT;
				ev.timeStamp = timeStamp;
				
			}

			if (state.Gamepad.bRightTrigger != prevState.Gamepad.bRightTrigger) {
				InputEvent &ev = iel[changeCount++];
				if (state.Gamepad.bRightTrigger < triggerDeadZone)
					state.Gamepad.bRightTrigger = 0;
				else
					state.Gamepad.bRightTrigger -= triggerDeadZone;
				ev.analogValue = trigValues[1].value = (float)state.Gamepad.bRightTrigger / (255.0f - triggerDeadZone);
				ev.key = KeyName::XBOX_TRIG_RIGHT;
				ev.timeStamp = timeStamp;
			}
						
			if (state.Gamepad.sThumbLX != prevState.Gamepad.sThumbLX ||
				state.Gamepad.sThumbLY != prevState.Gamepad.sThumbLY) {
				InputEvent &ev = iel[changeCount++];
				ev.analogDir = axes[0].value = GetCircular(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, thumbDeadZone[0]);
				ev.key = KeyName::XBOX_AXIS_LEFT;
				ev.timeStamp = timeStamp;
			}

			if (state.Gamepad.sThumbRX != prevState.Gamepad.sThumbRX ||
				state.Gamepad.sThumbRY != prevState.Gamepad.sThumbRY) {
				InputEvent &ev = iel[changeCount++];
				ev.analogDir = axes[0].value = GetCircular(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, thumbDeadZone[1]);
				ev.key = KeyName::XBOX_AXIS_RIGHT;
				ev.timeStamp = timeStamp;
			}
			prevState = state;
		}
	}
}