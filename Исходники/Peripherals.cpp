bool CPeripherals::Buzzer_LED(bool State)
{
	DWORD numBytesWritten = 0;

	if(State)
	{
		TRACE("Buzzer & LED Activated\n");
		m_pOwner->SystemInfo.SetWindowText("");
		m_pOwner->SystemInfo.SetWindowText("Buzzer & LED Activated.");
		m_pOwner->UpdateData(true);	
		WritePort(&m_activateBuzzerLed, 1, numBytesWritten);
	}
	else
	{
		TRACE("Buzzer & LED Deactivated\n");
		m_pOwner->SystemInfo.SetWindowText("");
		m_pOwner->SystemInfo.SetWindowText("Buzzer & LED Deactivated.");
		m_pOwner->UpdateData(true);	
		WritePort(&m_deactivateBuzzerLed, 1, numBytesWritten);
	}

	return true;
}