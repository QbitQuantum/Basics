	static void getDevices(std::vector<al::Bluetooth>& devs){


		//BLUETOOTH_ADDRESS returnAddress = { BLUETOOTH_NULL_ADDRESS };
		/*
		typedef struct {
		  DWORD  dwSize;
		  BOOL   fReturnAuthenticated;
		  BOOL   fReturnRemembered;
		  BOOL   fReturnUnknown;
		  BOOL   fReturnConnected;
		  BOOL   fIssueInquiry;
		  UCHAR  cTimeoutMultiplier;	// in units of 1.28 seconds
		  HANDLE hRadio;				// NULL == search all local radios
		} BLUETOOTH_DEVICE_SEARCH_PARAMS;
		*/
		BLUETOOTH_DEVICE_SEARCH_PARAMS params = {
			sizeof(params),
			//TRUE, FALSE, FALSE, TRUE, FALSE, 0, NULL
			TRUE, FALSE, TRUE, TRUE, TRUE, 5, NULL
		};
		BLUETOOTH_DEVICE_INFO info = { sizeof(info) };

		HBLUETOOTH_DEVICE_FIND hFind = BluetoothFindFirstDevice(&params, &info);

		if(NULL != hFind){
			char addr[18];
			char name[256];

			Bluetooth bt;

			do{
				//printf("%x%x\n", long(info.Address.ullLong>>32), long(info.Address.ullLong));
				btaddr2str(addr, info.Address.rgBytes);			
				wcstombs(name, info.szName, sizeof(name));

				//printf("Found %s (%s)\n", addr, name);
				//wprintf(L"%s)\n", info.szName);

				bt.mName = name;
				bt.mAddr = addr;
				bt.mClass= info.ulClassofDevice;
				devs.push_back(bt);
			} while(BluetoothFindNextDevice(hFind, &info));
		}

		BluetoothFindDeviceClose(hFind);
	}