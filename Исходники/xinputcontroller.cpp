/**
*
* This function Sets the vibration of the Xbox controller
*
* @Author Carsten Scholz
* @_fMagnitude is the strength of the vibration
* @_eMotor is the motor which you want to vibrate
* 
*/
void 
CXInputController::SetVibration(float32 _fMagnitude, EMotor _eMotor)
{
	if (_eMotor & MOTOR_LEFT)
	{
		m_Vibration.wLeftMotorSpeed = static_cast<uint16>(_fMagnitude * (float32)VIBRATION_MODIFIER);
	}
	if (_eMotor & MOTOR_RIGHT)
	{
		m_Vibration.wRightMotorSpeed = static_cast<uint16>(_fMagnitude * (float32)VIBRATION_MODIFIER);
	}

	XInputSetState(m_uiController, &m_Vibration);
}