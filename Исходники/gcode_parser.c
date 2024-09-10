static uint8_t _point(double value) 
{
	return((uint8_t)(value*10 - trunc(value)*10));	// isolate the decimal point as an int
}