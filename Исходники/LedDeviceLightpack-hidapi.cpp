int LedDeviceLightpackHidapi::testAndOpen(hid_device_info *device, const std::string & requestedSerialNumber)
{
	if ((device->vendor_id == USB_VENDOR_ID && device->product_id == USB_PRODUCT_ID) ||
		(device->vendor_id == USB_OLD_VENDOR_ID && device->product_id == USB_OLD_PRODUCT_ID))
	{
		Debug(_log, "Found a lightpack device. Retrieving more information...");

		// get the serial number
		std::string serialNumber = "";
		if (device->serial_number != nullptr)
		{
			// the serial number needs to be converted to a char array instead of wchar
			size_t size = wcslen(device->serial_number);
			serialNumber.resize(size, '.');
			for (size_t i = 0; i < size; ++i)
			{
				int c = wctob(device->serial_number[i]);
				if (c != EOF)
				{
					serialNumber[i] = c;
				}
			}
		}
		else
		{
			Error(_log, "No serial number for Lightpack device");
		}

		Debug(_log, "Lightpack device found: path=%s serial=%s", device->path.c_str(), serialNumber.c_str());

		// check if this is the device we are looking for
		if (requestedSerialNumber.empty() || requestedSerialNumber == serialNumber)
		{
			// This is it!
			_deviceHandle = hid_open_path(device->path);

			if (_deviceHandle != nullptr)
			{
				_serialNumber = serialNumber;

				Info(_log, "Lightpack device successfully opened");

				// get the firmware version
				uint8_t buffer[256];
				buffer[0] = 0; // report id
				int error = hid_get_feature_report(_deviceHandle, buffer, sizeof(buffer));
				if (error < 4)
				{
					Error(_log, "Unable to retrieve firmware version number from Lightpack device");
				}
				else
				{
					_firmwareVersion.majorVersion = buffer[INDEX_FW_VER_MAJOR+1];
					_firmwareVersion.minorVersion = buffer[INDEX_FW_VER_MINOR+1];
				}

				// FOR TESTING PURPOSE: FORCE MAJOR VERSION TO 6
				_firmwareVersion.majorVersion = 6;

				// disable smoothing of the chosen device
				disableSmoothing();

				// determine the number of leds
				if (_firmwareVersion.majorVersion == 4)
				{
					_hwLedCount = 8;
				}
				else
				{
					_hwLedCount = 10;
				}

				// determine the bits per channel
				if (_firmwareVersion.majorVersion == 6)
				{
					// maybe also or version 7? The firmware suggest this is only for 6... (2013-11-13)
					_bitsPerChannel = 12;
				}
				else
				{
					_bitsPerChannel = 8;
				}

				// set the led buffer size (repport id + command + 6 bytes per led)
				_ledBuffer = std::vector<uint8_t>(2 + _hwLedCount * 6, 0);
				_ledBuffer[0] = 0x0; // report id
				_ledBuffer[1] = CMD_UPDATE_LEDS;

				// return success
				Debug(_log,"Lightpack device opened: path=%s serial=%s version=%s.%s.%s", device->path.c_str(), _serialNumber.c_str(), _firmwareVersion.majorVersion.c_str(),  _firmwareVersion.minorVersion.c_str());
				return 0;
			}
			else
			{
				Warning(_log, "Unable to open Lightpack device. Searching for other device");
			}
		}
	}

	return -1;
}