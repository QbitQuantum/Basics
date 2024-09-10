void CVmc::setMotorRPM(int motor, int rpm)
{
	if((rpm < -1*_maxRpm) || (rpm > _maxRpm)) return;
	if((motor < 1) || (motor > 3)) return;

	enterCriticalSection();

	switch(motor)
	{
		case 1: _pwmOut1= rpm; break;
		case 2: _pwmOut2= rpm; break;
		case 3: _pwmOut3= rpm; break;
		default: break;
	}

	leaveCriticalSection();
}