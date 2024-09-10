bool InitializeFlowInterface(Controller *me)
{
	RegistrationData regData;

	GetConfigData(&regData);

	if (InitialiseLibFlowMessaging((const char *)regData.url, (const char *)regData.key,(const char *)regData.secret))
	{
		if (RegisterDevice(regData.deviceType,
						regData.deviceMACAddress,
						regData.deviceSerialNumber,
						DEVICE_SOFTWARE_VERSION,
						regData.deviceName,
						regData.devRegKey))
		{
			if (GetUserId(me->userId))
			{
				GetDeviceId(SENSOR_DEVICE_TYPE, me->userId, &me->sensorConfig.sensorId);
				GetDeviceId(ACTUATOR_DEVICE_TYPE, me->userId, &me->actuatorConfig.actuatorId);
				printf("Flow Interface initialized successfully\n");
				return true;
			}
		}
	}

	printf("Flow Interface initialization failed\n");
	return false;
}