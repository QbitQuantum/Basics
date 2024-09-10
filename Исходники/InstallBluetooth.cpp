int AddDevice(BLUETOOTH_DEVICE_INFO* pbtdi, wchar_t** portName)
{
	PWCHAR passKey = L"1234";
	DWORD result = BluetoothAuthenticateDevice(	NULL,
												NULL,
												pbtdi,
												passKey,
												wcslen(passKey));

	if(result != ERROR_SUCCESS)
	{
		return result;
	}

	/*PROBLEM: as far as i can tell, you can't get the port name (Ex: COM4) 
	from the windows api when adding and activating a bluetooth device.
	SOLUTION: check the registry for serial ports before and after, 
	and take the difference as being the new port
	*/

	std::vector<wchar_t*> serialPortsBefore, serialPortsAfter;

	result = GetComPortsFromRegistry(&serialPortsBefore);
	if(result != R_SUCCESS)
	{
		return R_REG_PORTS_RETRIEVAL_FAIL;
	}

	//set service state on device
	GUID service = SerialPortServiceClass_UUID;
	result = BluetoothSetServiceState(	NULL,
										pbtdi,
										&service,
										BLUETOOTH_SERVICE_ENABLE);

	if(result != ERROR_SUCCESS)
	{
		return result;
	}

	//it can take some time for the registry keys to show up, so we'll retry a couple times and delay between them
	for(int retry = 0; retry < 3;retry++)
	{
		result = GetComPortsFromRegistry(&serialPortsAfter);
		if(result != R_SUCCESS)
		{
			return R_REG_PORTS_RETRIEVAL_FAIL;
		}

		//if theres a size difference assume it's the new port and stop retrying
		if(serialPortsBefore.size() != serialPortsAfter.size())
			break;

		//wait a bit for the reg key to show up
		Sleep(2000);
	}

	std::vector<wchar_t*> diff;
	for(int i=0;i<serialPortsAfter.size();i++)
	{
		bool found = false;
		for(int j=0;j<serialPortsBefore.size();j++)
		{
			if(wcscmp(serialPortsAfter[i], serialPortsBefore[j]) == 0)
			{
				found = true;
				break;
			}
		}

		if(!found)
		{
			diff.push_back(serialPortsAfter[i]);
		}
	}

	if(diff.size() == 0)
	{
		return R_UNKNOWN_SERIAL_PORT;
	}
	else if(diff.size() > 1)
	{
		return R_UNKNOWN_SERIAL_PORT;
	}

	//copy the string to the provided buffer
	wcscpy(*portName, diff[0]);

	return result;

}