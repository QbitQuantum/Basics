status_t AudioStreamOutWrapper::setParameters(const String8& keyValuePairs)
{
	AudioParameter param = AudioParameter(keyValuePairs);
	String8 key = String8(AudioParameter::keyRouting);
	status_t status = NO_ERROR;
	int device;

        LOGV("AudioStreamOutWrapper::setParameters(\"%s\")", keyValuePairs.string());

	if (param.getInt(key, device) == NO_ERROR) {
		mDevices = device;
		LOGV("set output routing %x", mDevices);
		uint32_t routes = devicesToRoutes(mDevices);
		status = mHardware->setRouting(AudioSystem::MODE_NORMAL, routes);
		param.remove(key);
	}

	if (param.size()) {
		status = BAD_VALUE;
	}
	return status;
}