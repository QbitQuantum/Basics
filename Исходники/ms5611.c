bool ms5611_display_pressure_result(MS5611_t *structure, unsigned char osr)
{
	signed int Preasure = 0;
	signed int Temperature = 0;
	//if(!ms5611_read_prom_cmd_send(prom_data, TwiStruct)) return false;
	if(!ms5611_read(structure, osr, &Preasure, &Temperature)) return false;
#ifndef _TINY_PRINT_
	UARTprintf(DebugCom, "MS5611:\n\rP = %4.2f milibar, T = %2.2f gr celsius\n\r", ((float)Preasure) / 100.0, ((float)Temperature) / 100.0);
#else
	float PreasureInt = 0;
	float PreasureDec = modff(((float)Preasure)/100.0, &PreasureInt);
	float TemperatureInt = 0;
	float TemperatureDec = modff(((float)Preasure)/100.0, &Temperature);
	UARTprintf(DebugCom, "MS5611:\n\rP = %d.%u milibar, T = %d.%u gr celsius\n\r", (signed int)PreasureInt, (unsigned int)(PreasureDec * 100.0), (signed int)TemperatureInt, (unsigned int)(TemperatureDec * 100.0));
#endif
	return true;
}