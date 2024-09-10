HRESULT InputGamepad::UpdateControllerState()
{
    DWORD dwResult;
    for( DWORD i = 0; i < MAX_CONTROLLERS; i++ )
    {
        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState( i, &m_Controllers[i].state );

		if (dwResult == ERROR_SUCCESS){m_Controllers[i].bConnected = true;}
		else                          {m_Controllers[i].bConnected = false;}

		// つながってないときはチェックしない
		if( !m_Controllers[i].bConnected ) continue ;

		// スティックの状態を取得(無効領域はOFF,有効領域はON)
		// 左
        bool stick = m_Controllers[i].state.Gamepad.sThumbLX < -INPUT_DEADZONE;

		if (stick && ((gamepadState & 0x10000) != 0)) { gamepadAction[GamePadLStick_LEFT] = KEY_ON; }
		if (stick && ((gamepadState & 0x10000) == 0)) { gamepadAction[GamePadLStick_LEFT] = KEY_PUSH; }
		if (!stick && ((gamepadState & 0x10000) == 0)){ gamepadAction[GamePadLStick_LEFT] = KEY_OFF; }
		if (!stick && ((gamepadState & 0x10000) != 0)) { gamepadAction[GamePadLStick_LEFT] = KEY_RELEASE; }

		// 前回のキーの状態として保存
		if (stick)	{ gamepadState |= 0x10000; }
		else		{ gamepadState &= ~0x10000; }

		// 右
		stick = m_Controllers[i].state.Gamepad.sThumbLX > INPUT_DEADZONE;
		if (stick && ((gamepadState & 0x20000) != 0))	{ gamepadAction[GamePadLStick_RIGHT] = KEY_ON; }
		if (stick && ((gamepadState & 0x20000) == 0)) { gamepadAction[GamePadLStick_RIGHT] = KEY_PUSH; }
		if (!stick && ((gamepadState & 0x20000) == 0)) { gamepadAction[GamePadLStick_RIGHT] = KEY_OFF; }
		if (!stick && ((gamepadState & 0x20000) != 0)) { gamepadAction[GamePadLStick_RIGHT] = KEY_RELEASE; }

		// 前回のキーの状態として保存
		if (stick) { gamepadState |= 0x20000; }
		else		{ gamepadState &= ~0x20000; }
		
		// 上
        stick = m_Controllers[i].state.Gamepad.sThumbLY > INPUT_DEADZONE;

		if (stick && ((gamepadState & 0x40000) != 0)) { gamepadAction[GamePadLStick_UP] = KEY_ON; }
		if (stick && ((gamepadState & 0x40000) == 0)) { gamepadAction[GamePadLStick_UP] = KEY_PUSH; }
		if (!stick && ((gamepadState & 0x40000) == 0)) { gamepadAction[GamePadLStick_UP] = KEY_OFF; }
		if (!stick && ((gamepadState & 0x40000) != 0)) { gamepadAction[GamePadLStick_UP] = KEY_RELEASE; }

		// 前回のキーの状態として保存
		if (stick)	{ gamepadState |= 0x40000; }
		else		{ gamepadState &= ~0x40000; }

		// 下
		stick = m_Controllers[i].state.Gamepad.sThumbLY < -INPUT_DEADZONE;
		if (stick && ((gamepadState & 0x80000) != 0))	{ gamepadAction[GamePadLStick_DOWN] = KEY_ON; }
		if (stick && ((gamepadState & 0x80000) == 0))  { gamepadAction[GamePadLStick_DOWN] = KEY_PUSH; }
		if (!stick && ((gamepadState & 0x80000) == 0)) { gamepadAction[GamePadLStick_DOWN] = KEY_OFF; }
		if (!stick && ((gamepadState & 0x80000) != 0)) { gamepadAction[GamePadLStick_DOWN] = KEY_RELEASE; }

		// 前回のキーの状態として保存
		if (stick) { gamepadState |= 0x80000; }
		else		{ gamepadState &= ~0x80000; }
	
		// 各キーの状態を取得
		for( int i = 0; i < XINPUT_KEY_MAX; i++ ) {
			// ボタンの状態をチェック
			bool now = (m_Controllers->state.Gamepad.wButtons & XINPUT_KEY_LIST[i]) != 0;

			// 前回押されてて今回押されてるとき
			if( now && ((gamepadState & XINPUT_KEY_LIST[i]) != 0) ) {
				gamepadAction[ i ] = KEY_ON;
			}
			// 前回押されてなくて今回押されてるとき
			if( now && ((gamepadState & XINPUT_KEY_LIST[i]) == 0) ) {
				gamepadAction[ i ] = KEY_PUSH;
			}
			// 前回押されてなくて今回押されていないとき
			if( !now && ((gamepadState & XINPUT_KEY_LIST[i]) == 0) ) {
				gamepadAction[ i ] = KEY_OFF;
			}
			// 前回押されていて今回押されていないと
			if( !now && ((gamepadState & XINPUT_KEY_LIST[i]) != 0) ) {
				gamepadAction[ i ] = KEY_RELEASE;
			}

			// 前回のキーの状態として保存
			if (now) { gamepadState |= XINPUT_KEY_LIST[i]; }
			else	  { gamepadState &= ~XINPUT_KEY_LIST[i]; }
		}

	}
    return S_OK;
}