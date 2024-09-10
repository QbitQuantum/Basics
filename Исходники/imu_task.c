void get_MS5637_temp_and_pressure(double* temperature_ptr, double* pressure_ptr, uint8_t osr_d1, uint8_t osr_d2)
{
	uint32_t raw_temperature = 0;
	uint32_t raw_pressure = 0;
	double dt, offset, sens, t2, offset2, sens2;
	double temperature_buf;

	raw_pressure = I2C_MS5637_Read(osr_d1);
	raw_temperature = I2C_MS5637_Read(osr_d2);

    dt = raw_temperature - prom_data[5]*pow(2,8);    // calculate temperature difference from reference
    offset = prom_data[2]*pow(2, 17) + dt*prom_data[4]/pow(2,6);
    sens = prom_data[1]*pow(2,16) + (dt*prom_data[3])/pow(2,7);

    temperature_buf = (2000 + (dt*prom_data[6])/pow(2, 23))/100;           // First-order Temperature in degrees Centigrade

    // Second order corrections
    if(temperature_buf >= 20)
    {
    	t2 = 5*dt*dt/powl(2, 38); // correction for high temperatures
    	offset2 = 0;
    	sens2 = 0;
    }
    if(temperature_buf < 20)                   // correction for low temperature
    {
    	t2      = 3*dt*dt/powl(2, 33);
    	offset2 = 61*(temperature_buf - 2000)*(temperature_buf - 2000)/16;
    	sens2   = 29*(temperature_buf - 2000)*(temperature_buf - 2000)/16;
    }
    if(temperature_buf < -15)                      // correction for very low temperature
    {
    	offset2 = offset2 + 17*(temperature_buf + 1500)*(temperature_buf + 1500);
    	sens2 = sens2 + 9*(temperature_buf + 1500)*(temperature_buf + 1500);
    }

    if((temperature_buf < -50) || (temperature_buf > 100))
    {
//    	uint8_t reset_ctr = 0;
//    	for(reset_ctr = 0; reset_ctr < 7; reset_ctr++)
//    	{
//        	prom_data[reset_ctr] = 0;
//    	}
//    	setup_imu();
    }
    else
    {
        // End of second order corrections
        offset = offset - offset2;
        sens = sens - sens2;

    	if(xSemaphoreTake(xSemaphore_pressure_temperature_mutex_handle, 0))
    	{
    	    *temperature_ptr = temperature_buf - t2;
    	    *pressure_ptr = (((raw_pressure*sens)/pow(2, 21) - offset)/pow(2, 15))/100;  // Pressure in mbar or kPa		xSemaphoreGive( xSemaphore_pressure_temperature_mutex_handle );
    		xSemaphoreGive( xSemaphore_pressure_temperature_mutex_handle );
    	}
    }

}