	void L298MotorShield::Motor2Break()
	{
		DCMotorParameters parameters = motor2.GetParameters();

		WritePort(parameters.PortA, 0);
	    WritePort(parameters.PortB, 0);
	};