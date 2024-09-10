	Ci8042()
	{
		m_IsScrollActive = false;
		m_IsNumActive = false;
		m_IsCapsActive = false;

		KeLinkIrq(1);
		KeLinkIrq(12);
		KeEnableNotification(NfKe_Irq);
		KeEnableNotification(NfKe_TimerTick);
		KeEnableNotification(NfKe_TerminateProcess);
		KeEnableNotification(NfKeyboard_SwitchLEDStatus);

		InitDevices();

		CNotification<16> N;
		for (;;)
		{
			KeWaitFor(1);
			dword NfCount = KeGetNotificationCount();

			for (dword z = 0; z < NfCount; z++)
			{
				N.Recv();
				if (N.GetID() == NfKe_TimerTick)
				{
					m_TimeoutTimer++;
					if (m_TimeoutTimer >= 20)
					{
						KeDisableNotification(NfKe_TimerTick);
						//DebugOut("[MouseInitTimeout]", 18);
						KeInPortByte(0x60);
						m_IsInitFinished = true;
					}
				}
				else if (N.GetID() == NfKe_Irq)
				{
					if (N.GetByte(0) == 1)
					{
						byte D = KeInPortByte(0x60);

						//DebugOut("[fK:", 4);
						//DebugOut(D);
						//DebugOut("]", 1);

						OnKeybByte(D);
						KeEndOfInterrupt(1);
					}
					else if (N.GetByte(0) == 12)
					{
						bool M = false;
						if (KeInPortByte(0x64) & 0x20)
							M = true;
						byte D = KeInPortByte(0x60);

						//if (M)
						//	DebugOut("[fM:", 4);
						//else
						//	DebugOut("[fm:", 4);
						//DebugOut(D);
						//DebugOut("]", 1);

						if (M)
							OnMouseByte(D);
						KeEndOfInterrupt(12);
					}
				}
				else if (N.GetID() == NfKeyboard_SwitchLEDStatus)
				{
					SwitchLEDStatus(N.GetByte(0));
				}
				else if (N.GetID() == NfKe_TerminateProcess)
					return;
			}

			if (KeGetNotificationCount() == 0)
			{
				if (m_LEDSwitchState == 1)
				{
					SendKeyboardData(0xED);
					m_LEDSwitchState = 2;
				}
				else if (m_LEDSwitchState == 3)
				{
					SendKeyboardData(m_LEDStatus);
					m_LEDSwitchState = 4;
				}
			}
		}
	}