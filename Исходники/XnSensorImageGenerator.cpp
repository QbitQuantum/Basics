XnStatus XnExportedSensorImageGenerator::IsSupportedForDevice(xn::Context& context, xn::NodeInfo& sensorInfo, XnBool* pbSupported)
{
	XnStatus nRetVal = XN_STATUS_OK;

	nRetVal = XnExportedSensorGenerator::IsSupportedForDevice(context, sensorInfo, pbSupported);
	XN_IS_STATUS_OK(nRetVal);

	if (*pbSupported == FALSE)
	{
		return XN_STATUS_OK;
	}

	xn::Device sensor;
	nRetVal = sensorInfo.GetInstance(sensor);
	XN_IS_STATUS_OK(nRetVal);

	XnUInt64 nImageSupported = FALSE;

	if (sensor.IsValid())
	{
		nRetVal = sensor.GetIntProperty(XN_MODULE_PROPERTY_IMAGE_SUPPORTED, nImageSupported);
		XN_IS_STATUS_OK(nRetVal);
	}
	else
	{
		// Don't create sensor through OpenNI. This will cause it to soft-reset.
		// instead, "talk" directly to the sensor class
		XnSensor lowLevelSensor(FALSE);
		XnDeviceConfig config;
		config.DeviceMode = XN_DEVICE_MODE_READ;
		config.cpConnectionString = sensorInfo.GetCreationInfo();
		config.SharingMode = XN_DEVICE_EXCLUSIVE;
		config.pInitialValues = NULL;
		nRetVal = lowLevelSensor.Init(&config);
		XN_IS_STATUS_OK(nRetVal);

		nRetVal = lowLevelSensor.GetProperty(XN_MODULE_NAME_DEVICE, XN_MODULE_PROPERTY_IMAGE_SUPPORTED, &nImageSupported);
		XN_IS_STATUS_OK(nRetVal);
	}

	if (nImageSupported != TRUE)
	{
		*pbSupported = FALSE;
	}

	return (XN_STATUS_OK);
}