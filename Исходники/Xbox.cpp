//----------------------------------------------------------------------------------------------------
void Xbox::Controller::Vibrate( float leftIntensityZeroToOne, float rightIntensityZeroToOne, float durationSeconds )
{
	m_vibration.wLeftMotorSpeed = static_cast< WORD >( leftIntensityZeroToOne * VIBRATION_MAXIMUM ); 
	m_vibration.wRightMotorSpeed = static_cast< WORD >( rightIntensityZeroToOne * VIBRATION_MAXIMUM ); 
	m_vibrationTimeSeconds = durationSeconds;

	//Vibrate the controller 
	XInputSetState( m_padNumber, &m_vibration ); 
}