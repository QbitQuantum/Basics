	virtual void input_init(running_machine &machine) override
	{
		HRESULT result = get_xinput_devices(m_xinput_deviceids);
		if (result != 0)
		{
			m_xinput_detect_failed = true;
			osd_printf_warning("XInput device detection failed. XInput won't be used. Error: 0x%X\n", static_cast<unsigned int>(result));
		}

		// Enumerate all the directinput joysticks and add them if they aren't xinput compatible
		result = m_dinput_helper->enum_attached_devices(DI8DEVCLASS_GAMECTRL, this, &machine);
		if (result != DI_OK)
			fatalerror("DirectInput: Unable to enumerate keyboards (result=%08X)\n", static_cast<UINT32>(result));

		xinput_joystick_device *devinfo;

		// now add all xinput devices
		if (!m_xinput_detect_failed)
		{
			// Loop through each gamepad to determine if they are connected
			for (UINT i = 0; i < XUSER_MAX_COUNT; i++)
			{
				XINPUT_STATE state = { 0 };

				if (m_xinput_helper->XInputGetState(i, &state) == ERROR_SUCCESS)
				{
					// allocate and link in a new device
					devinfo = m_xinput_helper->create_xinput_device(machine, i, *this);
					if (devinfo == nullptr)
						continue;

					// Configure each gamepad to add buttons and Axes, etc.
					devinfo->configure();
				}
			}
		}
	}