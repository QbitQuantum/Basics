xinput_joystick_device * xinput_api_helper::create_xinput_device(running_machine &machine, UINT index, wininput_module &module)
{
	xinput_joystick_device *devinfo;

	XINPUT_CAPABILITIES caps = { 0 };
	if (FAILED(XInputGetCapabilities(index, 0, &caps)))
	{
		// If we can't get the capabilities skip this device
		return nullptr;
	}

	char device_name[16];
	snprintf(device_name, sizeof(device_name), "XInput Player %u", index + 1);

	// allocate the device object
	devinfo = module.devicelist()->create_device1<xinput_joystick_device>(machine, device_name, module, shared_from_this());

	// Set the player ID
	devinfo->xinput_state.player_index = index;

	// Assign the caps we captured earlier
	devinfo->xinput_state.caps = caps;

	return devinfo;
}