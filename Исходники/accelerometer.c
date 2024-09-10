//converting raw measurement from ADC values into a floating data type
void conversion(uint8_t *calibrate, float *angle, uint8_t *measurement, uint8_t secondmode)
{
	float components[3]={};
	float resultant=0;
	uint8_t i=0;
	
	for (i=0;i<=2;i++)
	{
		//Convert measurement and zero's into a component of gravity vector ((measurement-zero)*Vref[5V]/ADC resolution[255])/Sensibility[800mV/g]
		components[i]=((measurement[i]-calibrate[i])*4/255.0);
		//Add up the components squared in order to obtain...
		resultant=resultant + (components[i]*components[i]);
	}
	// ...Pythagoras theorem
	resultant=sqrt(resultant);
	
	if (secondmode==1)
	{
		//obtain direction cosines of the resultant/truncate the value just to one decimal point.
		//subtract 90 in order to make it more "readable"
		//just needing x & y axis to show
		angle[0]=truncf((acos(components[0]/resultant))*572.9)/10;
		angle[0]=angle[0]-90;
		
	}
	else
	{
		for (i=0;i<=1;i++)
		{
			//obtain direction cosines of the resultant/truncate the value just to one decimal point.
			//subtract 90 in order to make it more "readable"
			//just needing x & y axis to show
			angle[i]=truncf((acos(components[i]/resultant))*572.9)/10;
			angle[i]=angle[i]-90;
			
		}
	}
}