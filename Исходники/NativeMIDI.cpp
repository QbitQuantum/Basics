	FREObject closeOutputDevice(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		int pointer = 0;
		FREGetObjectAsInt32(argv[0],&pointer);

		try
		{
			RtMidiOut *out = (RtMidiOut *)pointer;
			if(out->isPortOpen()) out->closePort();
			removeDeviceOut(out);
			delete out;
		}catch(std::exception e)
		{
			printf("Error closing output device.\n");
		}

		FREObject result;
		FRENewObjectFromBool(true,&result);
		return result;
	}