//Get current level/loudness of audio (RMS value)
GMexport double FMODGMS_Chan_Get_Level(double channel)
{
	int c = (int)round(channel);
	int chanListSize = channelList.size();

	if (chanListSize > c && c >= 0)
	{
		FMOD::DSP* headDSP;
		channelList[c]->getDSP(FMOD_CHANNELCONTROL_DSP_TAIL, &headDSP);

		//enable channel metering if it isn't already
		bool meteringEnabled = 0;
		if (headDSP->getMeteringEnabled(NULL, &meteringEnabled) != FMOD_OK)
			return FMODGMS_Util_ErrorChecker();
		if (!meteringEnabled)
			headDSP->setMeteringEnabled(true, false);

		//get level using metering on head dsp
		FMOD_DSP_METERING_INFO meteringInfo;
		if (headDSP->getMeteringInfo(&meteringInfo, NULL) != FMOD_OK)
			return FMODGMS_Util_ErrorChecker();
		double level = 0;
		short numChannels = meteringInfo.numchannels;
		for (int i = 0; i < numChannels; i++)
			level += (double)meteringInfo.rmslevel[i];
		level /= numChannels;

		if (FMODGMS_Util_ErrorChecker() == GMS_true)
			return level;
		else
			return GMS_error;
	}
	else
	{
		errorMessage = "Index out of bounds.";
		return GMS_error;
	}
}