task main()
{
	waitForStart();
	while(true)
	{

		getJoystickSettings(joystick);
//first joypad
	//right drive
	 const int threshold =8; // Int 'threshold' will allow us to ignore low  readings that keep our robot in perpetual motion.
		if(abs(joystick.joy1_y1) > threshold)   // If the right analog stick's Y-axis readings are either above or below the threshold:
		{
		motor[RightMotor] = joystick.joy1_y1;         // Motor D is assigned a power level equal to the right analog stick's Y-axis reading.
		}else                                    // Else if the readings are within the threshold:
			{
				motor[RightMotor] = 0;                        // Motor D is stopped with a power level of 0.
			}
 //left drive
		if(abs(joystick.joy1_y2) > threshold)   // If the left analog stick's Y-axis readings are either above or below the threshold:
		{
		motor[LeftMotor] = joystick.joy1_y2;         // Motor E is assigned a power level equal to the left analog stick's Y-axis reading.
		}
			else                                    // Else if the readings are within the threshold:
			{
				motor[LeftMotor] = 0;                        // Motor E is stopped with a power level of 0.
			}
//Flag Raiser
			if(joy1Btn(5))
			{
				motor[FlagRaiser] = 80;
		  }
		  else if(joy1Btn(7))
		  {
		  	motor[FlagRaiser] = -80;
		  }
		  else
		  {
		 		motor[FlagRaiser] = 0;
		  }
//Second Joypad
		//Tower Lift--has two paralell motors mounted on the uprights
		if(joy2Btn(2))//A
			{
				motor[TowerLift]=-80;//down
			}else if(joy2Btn(3))//B
				{
					motor[TowerLift]=80;//up
				}else//not A, or B...
					{
						motor[TowerLift]=0;//stop
					}
	//lift--has one motor mounted at the tower cross-section
		if(joy2Btn(4))//X
			{
				writeDebugStreamLine("arm: %i", nMotorEncoder[potentiometer]);
				motor[Lift]=80;//down
			}else if(joy2Btn(1))//Y
				{
					writeDebugStreamLine("arm: %i", nMotorEncoder[potentiometer]);
					motor[Lift]=-80;//up
				}else//not X, or Y...
					{
						motor[Lift]=0;//stop
					}
	//Block Gate
			if(joy2Btn(6))//LB
			{
			servo[BlockGate]=254;// opens the block gate
			}else//not LB...
				{
					servo[BlockGate]=5;//close block gate
				}
	//ejector
			if(joy2Btn(8)&&servo[BlockGate] !=5)
			{
				servo[Ejector]=100;//opens the ejector servo
			}else
				{
					servo[Ejector]=5;//closes the ejector servo
				}
	}//end of while(true)
}//main end block