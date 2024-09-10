void sr844_GetXYRTP(gpibioPtr dev)
{
	double hi, lo;
	int i = 0, sens, senso;
	char str[256];
	sr844Ptr lia;
	sr844_channels chan;
	lia = dev->device;
	sr844_GetCharVal (dev, "SNAP?1,2,3,5", str);
	Scan (str, "%s>%f,%f,%f,%f",
		&lia->channels[X]->reading,
		&lia->channels[Y]->reading,
		&lia->channels[R]->reading,
		&lia->channels[T]->reading);
	sr844_CheckClear(dev);
	lia->channels[P]->reading = sr844_GetDoubleVal (dev, "PHAS?");
	for (chan = X; chan <= P; chan++) lia->channels[chan]->newreading = TRUE;
	if(lia->autosens)
	{
		senso = lia->sens;
        hi = sr844_Conv2Sensitivity (lia->sens);
        lo = sr844_Conv2Sensitivity (lia->sens-1);
		if (lia->channels[R]->reading > hi) lia->sens++;
        else if (lia->channels[R]->reading < lo) lia->sens--;
		if(lia->sens < 0) lia->sens = 0;
		if(lia->sens >14) lia->sens = 14;
		Fmt (str, "SENS%i", lia->sens);
        if(senso != lia->sens)
			gpibio_Out (dev, str);
	}
}