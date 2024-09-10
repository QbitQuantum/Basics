void CXBoxController::Vibrate( unsigned int leftVal, unsigned int rightVal )
{
	XINPUT_VIBRATION vibration;
	ZeroMemory( &vibration, sizeof( vibration ) );
	vibration.wLeftMotorSpeed = static_cast<WORD>(leftVal);
	vibration.wRightMotorSpeed = static_cast<WORD>(rightVal);

#ifdef _DEBUG
	// Call the pointer functions (from GetProcAddress)
	if ( !CXBoxController::bGetProcCompleted ) { return; }
	DWORD returnVal = CXBoxController::pXboxInputSetState( this->m_playerNumber, &vibration );
#else
	DWORD returnVal = XInputSetState( this->m_playerNumber, &vibration );
#endif
	return;
}