int main()
{
    int cTotal = 0;
    int cState = STATE_READ;

    char toggleOut = FALSE;

    Signal motor1;
    Signal motor2;
    Signal estop;
    Signal rcMode;

    init_coridium();

	setbaud(0, 17);
	
	
    statusMessage[0] = '#';
	statusMessage[1] = '%';
	statusMessage[2] = 0x82;



    INPUT(RC1); motor1.pin = RC1;
    INPUT(RC2); motor2.pin = RC2;
    INPUT(RC3); estop.pin = RC3;
    INPUT(RC4); rcMode.pin = RC4;


    OUTPUT(TX);
    OUTPUT(ESTOP); LOW(ESTOP);
    OUTPUT(RCMode);
    OUTPUT(FreqPin);
    OUTPUT(LIGHT);

    motor1.state = STATE_WAIT;
    motor1.duty = 0;
    motor1.valid = 0;

    motor2.state = STATE_WAIT;
    motor2.duty = 0;
    motor2.valid = 0;

    estop.state = STATE_WAIT;
    estop.duty = 0;
    estop.valid = 0;

    rcMode.state = STATE_WAIT;
    rcMode.duty = 0;
    rcMode.valid = 0;

    SLEEP(2);

    while (TRUE)
    {
        switch (cState)
        {
        case STATE_READ:
            if (toggleOut)
            {
                toggleOut = FALSE;
                HIGH(FreqPin);
            }
            else
            {
                toggleOut = TRUE;
                LOW(FreqPin);
            }

            cTotal += getDuty(&motor1);
            cTotal += getDuty(&motor2);
            cTotal += getDuty(&estop);
            cTotal += getDuty(&rcMode);

            if (cTotal > 8)
            {
                cState = STATE_SERIAL;
                cTotal = 0;
            }
            break;

        case STATE_SERIAL:
			if (estop.lastVal > 0)
            {
                sendESTOP(0);
                gESTOP = FALSE;
				
                if (rcMode.lastVal > 0)
                {
                    HIGH(LIGHT);
                    HIGH(RCMode);

                    // 11 == Manual (teleop) Mode
                    statusMessage[3] = 0x00;
                    statusMessage[4] = 0xFF;
                    statusMessage[5] = 0xFF;
                    statusMessage[6] = 0xFF;

                    calcSum();
					//statusMessage[7] = 0x84;
                    //SEROUT(TXD0,9600, 1, 3, statusMessage);
					TXD0(statusMessage[0]);
					TXD0(statusMessage[1]);
					TXD0(statusMessage[2]);
					TXD0(statusMessage[3]);
					TXD0(statusMessage[4]);
					TXD0(statusMessage[5]);
					TXD0(statusMessage[6]);
					TXD0(statusMessage[7]);
                }
                else
                {
                    if (flashcount > 0)
                    {
                        HIGH(LIGHT);
                    }
                    else
                    {
                        LOW(LIGHT);
                    }

                    if (flashcount > LIGHTDUTY)
                    {
                        flashcount = -LIGHTDUTY;
                    }

                    LOW(RCMode);

                    // 00 == Autonomous Mode
                    statusMessage[3] = 0x00;
                    statusMessage[4] = 0x00;
                    statusMessage[5] = 0x00;
                    statusMessage[6] = 0x00;

                    calcSum();
					//statusMessage[7] = 0x84;
                    //SEROUT(TXD0,9600, 1, 3, statusMessage);
					
					TXD0(statusMessage[0]);
					TXD0(statusMessage[1]);
					TXD0(statusMessage[2]);
					TXD0(statusMessage[3]);
					TXD0(statusMessage[4]);
					TXD0(statusMessage[5]);
					TXD0(statusMessage[6]);
					TXD0(statusMessage[7]);
                }
            }
            else
            {
                HIGH(LIGHT);
                HIGH(RCMode);
                sendESTOP(1);
                gESTOP = TRUE;
				
				// 11 == Manual (teleop) Mode
				statusMessage[3] = 0x00;
				statusMessage[4] = 0xFF;
				statusMessage[5] = 0xFF;
				statusMessage[6] = 0xFF;

				calcSum();
				//statusMessage[7] = 0x84;
				//SEROUT(TXD0,9600, 1, 3, statusMessage);
				TXD0(statusMessage[0]);
				TXD0(statusMessage[1]);
				TXD0(statusMessage[2]);
				TXD0(statusMessage[3]);
				TXD0(statusMessage[4]);
				TXD0(statusMessage[5]);
				TXD0(statusMessage[6]);
				TXD0(statusMessage[7]);
            }

#ifdef DEBUG
            putchar( binToHexstr((char)((motor1.lastVal >> 4) & 0x0F)) );
            putchar( binToHexstr((char)(motor1.lastVal & 0x0F)) );
            putchar(' ');
                        putchar( binToHexstr((char)((motor2.lastVal >> 4) & 0x0F)) );
            putchar( binToHexstr((char)(motor2.lastVal & 0x0F)) );
            putchar('\n');
            //printf("%d\n", estop.lastVal);
#endif
            // motor1 == forward value
            // motor2 == left/right value

            int left_motor = motor1.lastVal/2 - motor2.lastVal/2;
            int right_motor = motor1.lastVal/2 + motor2.lastVal/2;

            sendSerial(right_motor, 1);
            sendSerial(left_motor, 0);

            cState = STATE_READ;

            break;
        }
        flashcount++;
    }

    return 0;
}