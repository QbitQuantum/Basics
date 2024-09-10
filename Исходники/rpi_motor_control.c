/*========================================================= 
Name: read_temp
Description:
This thread reads temperature from the thermistor through
the ADC. It converts the ADC counts to temperature and
calculates the PWM duty demand for the fan.
*=========================================================*/
void * read_temp(void * arg)
{
unsigned short int thermistor_counts; /* ADC value in counts */
unsigned short int thermistor_counts_prev; /* Previous value of ADC counts */
float temp_adc_v; /* ADC value in volts */
float temp; /* Temperature read by the thermistor */
float temp_ramp = 0.0f; /* Temperature ramped output */
static float prev_temp_ramp; /* Previous value of temperature ramped output  */
static float pwm_temp = 0.0f; /* Value of temperature when PWM was updated */
unsigned char index = 0u;
static unsigned char first_run = TRUE; /* Flag to indicate first execution */
unsigned char print = FALSE; /* Display temperature */

/* Run indefinitely */
while(1)
{
	/* Transmit ADC read command and receive results */
	thermistor_counts = spi_read_adc(0);

	/* Ignore small change in counts */
	if (abs(thermistor_counts_prev - 
		thermistor_counts) < ADC_DIFFERENCE)
	{
		thermistor_counts = thermistor_counts_prev;
	}
	
	/* Convert counts to volts */
	temp_adc_v = thermistor_counts * ADC_SCALING;

	/* Convert volts to temperature */				
	temp = get_temperature(temp_adc_v);
		
	/* First run */
	if (TRUE == first_run)
	{
		first_run = FALSE;
		
		/* No need to ramp for the first time */
		temp_ramp = temp;
		print = TRUE;
	}	
	
	/* Look for temperature change and ramp slowly */
	if (calc_diff(temp_ramp, temp) > 0.75)
	{
		temp_ramp = ramp_temperature(temp_ramp, temp);
		print = TRUE;
	}
	
	/* Display temperature */
	if (TRUE == print)
	{	
		print = FALSE;
		system("date");
		fprintf (stdout, "Temperature is: %4.2f degC\n", temp_ramp);
		
		/* Limit fan speed */
		if ((temp_ramp/3) < 0)
		{
			index = 0;
		}
		else if ((temp_ramp/3) > 10)
		{
			index = 10;
		}
		else
		{
			index = (temp_ramp/3);
		}
		
		/* Update PWM demand for temperature change more than 2 degrees */
		if (fabsf(temp_ramp - pwm_temp) >= 2.0)
		{
			pwm_temp = temp_ramp;
			pwm_demand = fan_speed_dc[index - 1];
			fprintf(stdout, "pwm demand %d%\n", pwm_demand);
		}
	}
	
	/* Wait before next read */	
	sleep(1);

	/* Store previous temperature value */
	prev_temp_ramp = temp_ramp;
	thermistor_counts_prev = thermistor_counts;
}
}