int main(void)
{	
	
	set_fuses();
	init();
	PORT_LED &=~ ((1 << LED_RV) | (1<< LED_RH) | ( 1 << LED_LH) | (1 << LED_LV));
/*
	_delay_ms(1000);
*/
	unsigned char programm_step = 1;
	beep(2);
	
	
	PORT_LED &=~ ((1<< LED_RH) | ( 1 << LED_LH) | (1 << LED_LV));
	PORT_LED |= (1 << LED_RV);
	_delay_ms(500);
	PORT_LED &=~ ((1 << LED_RV) | ( 1 << LED_LH) | (1 << LED_LV));
	PORT_LED |= (1 << LED_RH);
	_delay_ms(500);
	PORT_LED &=~ ((1 << LED_RV) | (1<< LED_RH) | (1 << LED_LV));
	PORT_LED |= (1 << LED_LH);
	_delay_ms(500);
	PORT_LED &=~ ((1 << LED_RV) | (1<< LED_RH) | ( 1 << LED_LH) );
	PORT_LED |= (1 << LED_LV);
	_delay_ms(500);
/*
	while(!(status&(1<<STATUS_END)))
    {

		switch (programm_step)
		{
			case 1:
			{	
				if (!(status&(1<<STATUS_BUSY)))
				{
					drive_Robot(MOT_FORWARD,242,MOT_BACKWARD,254,ONE_TURN,ONE_TURN);
				}
				else
				{
					if(check_impulse()) 
					{
						programm_step++;
					}				
				}
			}
			break;
			
			case 2:
			{
				_delay_ms(1000);
				programm_step++;
			}
			break;
			
			case 3:
			{
				if (!(status&(1<<STATUS_BUSY)))
				{
					drive_Robot(MOT_BACKWARD,242,MOT_FORWARD,254,ONE_TURN,ONE_TURN);
				}
				else
				{
					if(check_impulse())
					{
						programm_step++;
					}
				}
			}
			break;

			case 4:
			{
				if (!(status&(1<<STATUS_BUSY)))
				{
					drive_Robot(MOT_FORWARD,242,MOT_FORWARD,254, (5*ONE_TURN),(5*ONE_TURN));
				}
				else
				{
					if(check_impulse())
					{
						programm_step++;
					}
				}
			}
			break;

			case 5:
			{
				if (!(status&(1<<STATUS_BUSY)))
				{
					drive_Robot(MOT_BACKWARD,242,MOT_FORWARD,254,ONE_TURN,ONE_TURN);
				}
				else
				{
					if(check_impulse())
					{
						programm_step++;
					}
				}
			}
			break;
			
			case 6:
			{
				if (!(status&(1<<STATUS_BUSY)))
				{
					drive_Robot(MOT_FORWARD,242,MOT_FORWARD,254,(5*ONE_TURN),(5*ONE_TURN));
				}
				else
				{
					if(check_impulse())
					{
						status |= (1<<STATUS_END);
					}
				}
			}
			break;
		}		
	}
*/
	PORT_DUAL |= (1 << LED_ROT);
	PORT_LED &=~ ((1 << LED_RV) | (1<< LED_RH) | ( 1 << LED_LH) | (1 << LED_LV));

	pwm_left = 250;
	pwm_right = 250;/*
	drive_Robot(MOT_BACKWARD,pwm_right,MOT_BACKWARD,pwm_left,3*ONE_TURN,3*ONE_TURN);
	while (!check_impulse()) {
		beep(1);
		PORT_LED ^= (1 << LED_RH) | (1 << LED_LH);
	}
	PORT_LED &=~ ((1 << LED_RV) | (1<< LED_RH) | ( 1 << LED_LH) | (1 << LED_LV));
	
	drive_Robot(MOT_FORWARD, pwm_right, MOT_FORWARD, pwm_left, 0, ONE_TURN);
	while (!check_impulse()) {
		PORT_LED ^= (1 << LED_RH) | (1 << LED_RV);
		_delay_ms(200);
	}*/
	
	
	/*
	PORT_LED &=~ ((1 << LED_RV) | (1<< LED_RH) | ( 1 << LED_LH) | (1 << LED_LV));
	drive_Robot(MOT_FORWARD, 185, MOT_FORWARD, 185, 300, 300);
	for (int i = 20; i > 0; i--) {
		OCR4B = 240 - i * 5;
		OCR4D = 240 - i * 5;
		_delay_ms(200);
	}
	while (!check_impulse());
	*/
	int co = 4;
/*	while (co--){
	drive_Robot(MOT_FORWARD, 250, MOT_FORWARD, 250, 3*ONE_TURN-3, 3*ONE_TURN-3);
	while (!check_impulse());
	drive_Robot(MOT_FORWARD, 250, MOT_FORWARD, 0, ONE_TURN, 0);
	while (!check_impulse());
	}*/
	co = 0;
	while (co--) {
		drive_Robot(MOT_FORWARD, 250, MOT_BACKWARD, 250, 30,30);
		while (!check_impulse());
	}
//	_delay_ms(20);
/*
	pwm_left = 0;
	pwm_right = pwm_left-(pwm_left/RATIO_Left_Right);
	drive_Robot(MOT_FAST_STOPP,pwm_right,MOT_FAST_STOPP,pwm_left,STOPP,STOPP);
//	_delay_ms(200);

	pwm_left = 200;
	pwm_right = pwm_left-(pwm_left/RATIO_Left_Right);
	drive_Robot(MOT_FORWARD,pwm_right,MOT_BACKWARD,pwm_left,ROT_180,ROT_180);
while(!check_impulse()) {}
//	_delay_ms(850);

	pwm_left = 0;
	pwm_right = pwm_left-(pwm_left/RATIO_Left_Right);
	drive_Robot(MOT_FAST_STOPP,pwm_right,MOT_FAST_STOPP,pwm_left,ONE_TURN,ONE_TURN);
//	_delay_ms(200);

	pwm_left = 200;
	pwm_right = pwm_left-(pwm_left/RATIO_Left_Right);
	drive_Robot(MOT_FORWARD,pwm_right,MOT_FORWARD,pwm_left,5*ONE_TURN,5*ONE_TURN);
while(!check_impulse()) {}
//	_delay_ms(10000);

	pwm_left = 0;
	pwm_right = pwm_left-(pwm_left/RATIO_Left_Right);
	drive_Robot(MOT_FAST_STOPP,pwm_right,MOT_FAST_STOPP,pwm_left,ONE_TURN,ONE_TURN);
*/
	
	/*char dot = 3;
	while(dot)
	{
		if(!check_impulse()) {}
		else
		{
			PORTD ^= (1<<LED_GRUEN);
			PORTB ^= (1<<LED_RH);
			PORTB ^= (1<<LED_RV);
			beep(3);
			_delay_ms(200);
			dot--;
		}
	}
	*/
	timer_beep_melodie();
//	beep(4);
	PORT_DUAL &=~ (1 << LED_ROT);
	PORT_DUAL |= (1 << LED_GRUEN);
	while (1)
	{
		PORT_DUAL &=~ (1 << LED_GRUEN);
		_delay_ms(500);
		PORT_DUAL |= (1 << LED_GRUEN);
		_delay_ms(2000);
	}
}