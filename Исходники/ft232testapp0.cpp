void get_info(void)
{
	
	UCHAR Mask = 0xff;
	UCHAR Mode = 1;     // Set asynchronous bit-bang mode
	LONG lComPortNumber;
	DWORD numDevs;
	
	//UCHAR BitMode;
	

	char ManufacturerBuf[32];
	char ManufacturerIdBuf[16];
	char DescriptionBuf[64];
	char SerialNumberBuf[16];
	ftData.Signature1 = 0x00000000; 
	ftData.Signature2 = 0xffffffff; 
	ftData.Version = 0x00000002; 

	ftData.Manufacturer = ManufacturerBuf;
	ftData.ManufacturerId = ManufacturerIdBuf;
	ftData.Description = DescriptionBuf;
	ftData.SerialNumber = SerialNumberBuf;

	ftStatus = FT_CreateDeviceInfoList(&numDevs);
	if (ftStatus == FT_OK)
	{ 
		printf("Number of devices is %d\n",numDevs);
	}
	if (numDevs > 0)
	{
		// allocate storage for list based on numDevs
		devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);  // get the device information list
		ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs); 
		if (ftStatus == FT_OK)
		{
			for (i = 0; i < numDevs; i++)
			{ 
				printf("Dev %d:\n",i);
				printf(" Flags=0x%x\n",devInfo[i].Flags);
				printf(" Type=%s\n",devices[devInfo[i].Type]); 
				printf(" ID=0x%x\n",devInfo[i].ID);
				printf(" LocId=0x%x\n",devInfo[i].LocId);
				printf(" SerialNumber=%s\n",devInfo[i].SerialNumber);
				printf(" Description=%s\n",devInfo[i].Description);
				// printf(" ftHandle=0x%x\n",devInfo[i].ftHandle);			

			}
		}

		i=0;  //open first device
		ftStatus = FT_Open(i,&ftHandle);

		if (ftStatus != FT_OK)
		{
			printf("Can't open %s device! \n",devInfo[i].Description);
		}
		else
		{     
			printf("Successfully open  %s device! \n",devInfo[i].Description);	
			ftStatus = FT_GetComPortNumber(ftHandle,&lComPortNumber);
			if (ftStatus == FT_OK)
			{ 
				if (lComPortNumber == -1)
				{ 
					printf(" NO com port Assigned!\n");
				}
				else
				{ 
					// COM port assigned with number held in lComPortNumber
					printf(" Current assigned COM Port: %d \n",lComPortNumber);
				} 
			}
			else
			{
				printf(" Failed to get the COM Port!\n");
			}

			ftStatus = FT_EE_Read(ftHandle, &ftData);
			if (ftStatus == FT_OK)
			{ 
				// FT_EE_Read OK, data is available in ftData
				printf(" EEPROM READ OK\n");
				printf("Signature1 = 0x%04x\n", ftData.Signature1);
				printf("Signature2 = 0x%04x\n", ftData.Signature2);
				printf("Version = 0x%04x\n", ftData.Version);
				printf("VendorID = 0x%04x\n", ftData.VendorId);
				printf("ProductID = 0x%04x\n", ftData.ProductId);
				printf("Manufacturer = %s\n", ftData.Manufacturer);
				printf("ManufacturerID = %s\n", ftData.ManufacturerId);
				printf("Description = %s\n", ftData.Description);
				printf("SerialNumber = %s\n", ftData.SerialNumber);
				printf("MaxPower = %d\n", ftData.MaxPower);
				printf("PnP = %x\n", ftData.PnP);
				printf("SelfPowered = %x\n", ftData.SelfPowered);
				printf("RemoteWakeup = %x\n", ftData.RemoteWakeup);
				printf("Use Ext Osc = %x\n", ftData.UseExtOsc);
				printf("High Drives = %x\n", ftData.HighDriveIOs);
				printf("Endpoint Size = %x\n", ftData.EndpointSize);
				printf("Pull Down Enabled = %x\n", ftData.PullDownEnableR);
				printf("Serial Number Enabled = %x\n", ftData.SerNumEnableR);
				printf("Invert TXD = %x\n", ftData.InvertTXD);
				printf("Invert RXD = %x\n", ftData.InvertRXD);
				printf("Invert RTS = %x\n", ftData.InvertRTS);
				printf("Invert CTS = %x\n", ftData.InvertCTS);
				printf("Invert DTR = %x\n", ftData.InvertDTR);
				printf("Invert DSR = %x\n", ftData.InvertDSR);
				printf("Invert DCD = %x\n", ftData.InvertDCD);
				printf("Invert RI = %x\n", ftData.InvertRI);
				printf("CBUS0 =  0X%02X\n", ftData.Cbus0);
				printf("CBUS1 =  0X%02X\n", ftData.Cbus1);
				printf("CBUS2 =  0X%02X\n", ftData.Cbus2);
				printf("CBUS3 =  0X%02X\n", ftData.Cbus3);
				printf("CBUS4 =  0X%02X\n", ftData.Cbus4);



			} 
			else
			{ 
				// FT_EE_Read FAILED! 
				printf(" EEPROM READ FAILED\n");

			}
			FT_Close(ftHandle);	
		}      
	}
	else
	{
		printf("No FT232 Device found! \n");
	}
}