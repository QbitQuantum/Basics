static void k2400_GetMeasurementParameters (gpibioPtr dev)
{
    char msg[256];
    int srctype;
    k2400Ptr smu = dev->device;
	/*Check Source mode*/
    k2400_Out(dev, ":SOURce:FUNCtion:MODE?", .008);
    k2400_In(dev, msg);
	if(msg[0] == 'V')
		smu->src.current = 0;
	else
		smu->src.current = 1;
	
	/*Check for remote/local sense*/
	k2400_Out(dev, ":SYStem:RSENse?", .008);
	k2400_In(dev, msg);
	Scan(msg, "%i", &smu->sense);
	
	/*Check Filter steps*/
	k2400_Out(dev, ":SENSe:AVERage:COUNt?", .008);
	k2400_In(dev, msg);
	Scan(msg, "%i", &smu->meas.filter);
	
	/*Check Integration time*/
	k2400_Out(dev, ":SENSe:CURRent:NPLCycles?", .008);
	k2400_In(dev, msg);
	Scan(msg, "%f", &smu->meas.inttime);
	
	/*Check Delay time*/
	k2400_Out(dev, ":SOURce:DELay:AUTO?", .008);
	k2400_In(dev, msg);
	Scan(msg, "%i", &smu->src.delay);
										  
    //Scan (msg, "%s[i3]>L,%i", &smu->meas.range);
}