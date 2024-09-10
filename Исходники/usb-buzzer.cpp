USBDevice *usb_keyboard_init(void)
{
    USBKeyboardState *s;

    s = (USBKeyboardState *)malloc(sizeof(USBKeyboardState));
    if (!s)
        return NULL;
    memset(s,0,sizeof(USBKeyboardState));
    s->dev.speed = USB_SPEED_FULL;
    s->dev.handle_packet = usb_generic_handle_packet;

    s->dev.handle_reset = usb_keyboard_handle_reset;
    s->dev.handle_control = usb_keyboard_handle_control;
    s->dev.handle_data = usb_keyboard_handle_data;
    s->dev.handle_destroy = usb_keyboard_handle_destroy;

    strncpy(s->dev.devname, "Generic USB Keyboard", sizeof(s->dev.devname));

	int i=0;
	DWORD needed=0;
	unsigned char buf[8];
	HDEVINFO devInfo;
	GUID guid;
	SP_DEVICE_INTERFACE_DATA diData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA didData;
	HIDD_ATTRIBUTES attr;

	readData=CreateEvent(0, 0, 0, 0);
	memset(&ovl, 0, sizeof(OVERLAPPED));
	ovl.hEvent=readData;
	ovl.Offset=0;
	ovl.OffsetHigh=0;

	HidD_GetHidGuid(&guid);
	
	devInfo=SetupDiGetClassDevs(&guid, 0, 0, DIGCF_DEVICEINTERFACE);
	if(!devInfo)return 0;
	
	diData.cbSize=sizeof(diData);

	while(SetupDiEnumDeviceInterfaces(devInfo, 0, &guid, i, &diData)){
		if(usb_buzzer!=INVALID_HANDLE_VALUE)CloseHandle(usb_buzzer);

		SetupDiGetDeviceInterfaceDetail(devInfo, &diData, 0, 0, &needed, 0);

		didData=(PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(needed);
		didData->cbSize=sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		if(!SetupDiGetDeviceInterfaceDetail(devInfo, &diData, didData, needed, 0, 0)){
			free(didData);
			break;
		}

		usb_buzzer=CreateFile(didData->DevicePath, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
		if(usb_buzzer==INVALID_HANDLE_VALUE){
			printf("Could not open device %i\n", i);
			free(didData);
			i++;
			continue;
		}

		HidD_GetAttributes(usb_buzzer, &attr);

		printf("Device %i : VID %04X PID %04X\n", i, attr.VendorID, attr.ProductID);

		if((attr.VendorID==BUZZER_VID) && (attr.ProductID==BUZZER_PID || attr.ProductID==BUZZER_PID2)){
			//We've found our buzzers !!!
			free(didData);
			printf("Buzzers found !!!\n");
			
			memset(buf, 0, 8);
			buf[2]=0xFF;
			WriteFile(usb_buzzer, buf, 8, 0, &ovl);
			Sleep(100);

			memset(buf, 0, 8);
			buf[3]=0xFF;
			WriteFile(usb_buzzer, buf, 8, 0, &ovl);
			Sleep(100);

			memset(buf, 0, 8);
			buf[4]=0xFF;
			WriteFile(usb_buzzer, buf, 8, 0, &ovl);
			Sleep(100);

			memset(buf, 0, 8);
			buf[5]=0xFF;
			WriteFile(usb_buzzer, buf, 8, 0, &ovl);
			Sleep(100);

			memset(buf, 0, 8);
			WriteFile(usb_buzzer, buf, 8, 0, &ovl);
			break;
		}
		i++;
	}

	if(usb_buzzer==INVALID_HANDLE_VALUE)
		printf("Could not find buzzers\n");

    return (USBDevice *)s;
}