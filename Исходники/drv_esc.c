void pwm_set( uint8_t number , float pwm)
{

	if ( pwm < 0 ) pwm = 0;
	
	pwm = mapf ( pwm , 0 , 1 , ( (float) PWMTOP/PWMTOP_US)*ESC_MIN , ( (float) PWMTOP/PWMTOP_US)*ESC_MAX ); 

if ( onground ) pwm = ((float)PWMTOP/PWMTOP_US) * ESC_THROTTLEOFF;
	
	if ( failsafe ) 
	{
		if ( !pwm_failsafe_time )
		{
			pwm_failsafe_time = gettime();
		}
		else
		{
			// 100mS after failsafe we turn off the signal (for safety while flashing)
			if ( gettime() - pwm_failsafe_time > 100000 )
			{
				pwm = ((float)PWMTOP/PWMTOP_US) * ESC_FAILSAFE;
			}
		}
		
	}
	else
	{
		pwm_failsafe_time = 0;
	}

	if ( pwm > ((float)PWMTOP/PWMTOP_US)*ESC_MAX ) pwm = ((float)PWMTOP/PWMTOP_US)*ESC_MAX ;

#ifdef ONESHOT_125_ENABLE
	pwm = pwm/8;
#endif
	
	pwm = lroundf(pwm);
	

	

	
    if ( pwm < 0 ) pwm = 0;
  if ( pwm > PWMTOP ) pwm = PWMTOP;
	
	

  switch( number)
	{
		case 0:
		  TIMER1->CHCC1 = (uint32_t) pwm; 	  
		break;
		
		case 1:
		  TIMER3->CHCC4 = (uint32_t) pwm; 
		break;
		
		case 2:
		  TIMER1->CHCC2 = (uint32_t) pwm; 
		break;
		
		case 3:
		  TIMER1->CHCC3 = (uint32_t) pwm; 
		break;
		
		default:
			// handle error;
			//
		break;	
				
	}
	
}