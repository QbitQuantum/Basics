void sht11_display_data(SHT11_t *structure) {
#ifndef _TINY_PRINT_
	UARTprintf(DebugCom, "SHT11: T = %2.2f, H = %2.3f\n\r", structure->temperature, structure->humidity);
#else
	float Temp;
	float FractTemp = modff(structure->temperature, &Temp) * 1000;
	float Hum;
	float FractHum = modff(structure->humidity, &Hum) * 1000;
	UARTprintf(DebugCom, "SHT11: T = %d.%d, H = %d.%d\n\r", (signed long)Temp, (signed long)FractTemp, (signed long)Hum, (signed long)FractHum);
#endif
}