void HID::update( UINT message, LPARAM lParam )
{
	UINT dwSize;
	RAWINPUT* pRaw;

	switch (message) 
	{
		case WM_INPUT:
			dwSize = 40;
			static BYTE lpb[40];
    
			GetRawInputData( (HRAWINPUT)lParam, RID_INPUT, 
							lpb, &dwSize, sizeof(RAWINPUTHEADER) );
    
			pRaw = (RAWINPUT*)lpb;
    
			if (pRaw->header.dwType == RIM_TYPEMOUSE) 
			{
				if ( m_mouse.click(pRaw, RI_MOUSE_LEFT_BUTTON_DOWN) )
				{
					POINT t_point = m_mouse.getPosition();
					XMFLOAT2 t_Vpoint;
					t_Vpoint.x = (float)t_point.x;
					t_Vpoint.y = (float)t_point.y;
					m_observable.broadcastLeftClick( t_Vpoint );
				}

				if( m_mouse.click(pRaw, RI_MOUSE_RIGHT_BUTTON_DOWN) )
				{
					POINT t_point = m_mouse.getPosition();
					XMFLOAT2 t_Vpoint;
					t_Vpoint.x = (float)t_point.x;
					t_Vpoint.y = (float)t_point.y;
					m_observable.broadcastRightClick(t_Vpoint);
				}

				//POINT t_point = m_mouse.getPosition();
				XMFLOAT2 t_Vpoint = m_mouse.mouseMove(pRaw);;
				/*t_Vpoint.x = (float)t_point.x;
				t_Vpoint.y = (float)t_point.y;*/
				m_observable.broadcastMousePos(t_Vpoint);
			}

			if (pRaw->header.dwType == RIM_TYPEKEYBOARD)
			{
				if(pRaw->data.keyboard.Flags == 0)
					m_observable.broadcastKeyPress( m_keyboard.keyDown(pRaw) );
			}
			break;
		default:
			
			break;
	}
}