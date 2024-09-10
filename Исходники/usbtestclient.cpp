//////////////////////////////////////////////////////////////////////////////
//
// Application entry point
//
//////////////////////////////////////////////////////////////////////////////
static void RunAppL()
	{

    TInt error = KErrUnknown;

	//RDebug::Print(_L("USBMSAPP: Creating console\n"));
	console = Console::NewL(KTxtApp,TSize(KConsFullScreen,KConsFullScreen));
	CleanupStack::PushL(console);

	console->SetPos(0,2);
	console->Printf(_L("========================================"));

	// Command line: list of drive letters to auto-mount (all if not specified)
	User::CommandLine(mountList);
	mountList.UpperCase();

	CActiveScheduler* sched = new(ELeave) CActiveScheduler;
	CleanupStack::PushL(sched);
	CActiveScheduler::Install(sched);

	fs.Connect();
	CleanupClosePushL(fs);

	_LIT(KMountAllDefault,"(all)");
	console->SetPos(0,3);
	LogPrint(_L("Drives to auto-mount: %S"), (mountList.Length() ? &mountList : &KMountAllDefault));

	// Add MS file system
	error = fs.AddFileSystem(KMsFsy);
	if(error != KErrNone && error != KErrAlreadyExists)
		{
		//RDebug::Print(_L("AddFileSystem failed, err=%d\n"), error);
		User::Leave(error);
		}
	console->SetPos(0,4);
	LogPrint(_L("MSFS file system:\tAdded OK\n"));

	RUsb usb;

	// Load the logical device
	_LIT(KDriverFileName,"EUSBC.LDD");
	error = User::LoadLogicalDevice(KDriverFileName);
	if (error != KErrAlreadyExists)
		User::LeaveIfError(error);

	error = usb.Open(0);
	User::LeaveIfError(error);

	_LIT(KOtgdiLddFilename, "otgdi");
	// Check for OTG support
	TBuf8<KUsbDescSize_Otg> otg_desc;
	error = usb.GetOtgDescriptor(otg_desc);
	if (!(error == KErrNotSupported || error == KErrNone))
		{
		LogPrint(_L("Error %d while fetching OTG descriptor"), error);
		User::Leave(-1);
		return;
		}

	// On an OTG device we have to start the OTG driver, otherwise the Client
	// stack will remain disabled forever.
	if (error == KErrNotSupported)
	{
		CleanupClosePushL(usb);
		User::Leave(-1);
	}

	error = User::LoadLogicalDevice(KOtgdiLddFilename);
	if (error != KErrNone)
		{
		LogPrint(_L("Error %d on loading OTG LDD"), error);
		User::Leave(-1);
		return;
		}

	RUsbOtgDriver iOtgPort;

	error = iOtgPort.Open();
	if (error != KErrNone)
		{
		LogPrint(_L("Error %d on opening OTG port"), error);
		User::Leave(-1);
		return;
		}
	error = iOtgPort.StartStacks();
	if (error != KErrNone)
		{
		LogPrint(_L("Error %d on starting USB stack"), error);
		User::Leave(-1);
		return;
		}

	CleanupClosePushL(usb);

//		RDebug::Print(_L("USBMSAPP: Create active objects\n"));
	CMessageKeyProcessor::NewLC(console);
	CPropertyWatch::NewLC(EUsbMsDriveState_KBytesRead, PropertyHandlers::Read);
	CPropertyWatch::NewLC(EUsbMsDriveState_KBytesWritten, PropertyHandlers::Written);
	CPropertyWatch::NewLC(EUsbMsDriveState_DriveStatus, PropertyHandlers::DriveStatus);
	CPropertyWatch::NewLC(EUsbMsDriveState_MediaError, PropertyHandlers::MediaError);
	CUsbWatch::NewLC(usb);
	CPeriodUpdate::NewLC();

	RUsbMassStorage UsbMs;
	TBuf<8>  t_vendorId(_L("vendor"));
	TBuf<16> t_productId(_L("product"));
	TBuf<4>  t_productRev(_L("1.00"));

	TMassStorageConfig msConfig;
	msConfig.iVendorId.Copy(t_vendorId);
	msConfig.iProductId.Copy(t_productId);
	msConfig.iProductRev.Copy(t_productRev);

//   	console->Printf(_L("Connect to Mass Storage"));
	error = UsbMs.Connect();
	User::LeaveIfError(error);

//   	console->Printf(_L("Start Mass Storage"));
	error = UsbMs.Start(msConfig);
	User::LeaveIfError(error);

	TBuf8<KUsbDescSize_Device> deviceDescriptor;
	error = usb.GetDeviceDescriptor(deviceDescriptor);
	User::LeaveIfError(error);

	const TInt KUsbSpecOffset = 2;
	const TInt KUsbDeviceClassOffset = 4;
	const TInt KUsbVendorIdOffset = 8;
	const TInt KUsbProductIdOffset = 10;
	const TInt KUsbDevReleaseOffset = 12;
	//Change the USB spec number to 2.00
	deviceDescriptor[KUsbSpecOffset]   = 0x00;
	deviceDescriptor[KUsbSpecOffset+1] = 0x02;
	//Change the Device Class, Device SubClass and Device Protocol
	deviceDescriptor[KUsbDeviceClassOffset] = 0x00;
	deviceDescriptor[KUsbDeviceClassOffset+1] = 0x00;
	deviceDescriptor[KUsbDeviceClassOffset+2] = 0x00;
	//Change the device vendor ID (VID) to 0x0E22 (Symbian)
	deviceDescriptor[KUsbVendorIdOffset]   = 0x22;   // little endian
	deviceDescriptor[KUsbVendorIdOffset+1] = 0x0E;
	//Change the device product ID (PID) to 0x1111
	deviceDescriptor[KUsbProductIdOffset]   = 0x12;
	deviceDescriptor[KUsbProductIdOffset+1] = 0x11;
	//Change the device release number to 3.05
	deviceDescriptor[KUsbDevReleaseOffset]   = 0x05;
	deviceDescriptor[KUsbDevReleaseOffset+1] = 0x03;
	error = usb.SetDeviceDescriptor(deviceDescriptor);
	User::LeaveIfError(error);

	// Remove possible Remote-Wakup support in Configuration descriptor,
	// so that we can use the MSC device also easily for Chapter9 testing.
	TBuf8<KUsbDescSize_Config> configDescriptor;
	error = usb.GetConfigurationDescriptor(configDescriptor);
	User::LeaveIfError(error);
	const TInt KConfDesc_AttribOffset = 7;
	configDescriptor[KConfDesc_AttribOffset] &= ~KUsbDevAttr_RemoteWakeup;
	error = usb.SetConfigurationDescriptor(configDescriptor);
	User::LeaveIfError(error);

	_LIT16(productID_L, "Symbian USB Mass Storage Device (Base)");
	TBuf16<KUsbStringDescStringMaxSize / 2> productID(productID_L);
	error = usb.SetProductStringDescriptor(productID);
	User::LeaveIfError(error);

	TRequestStatus enum_status;
	console->SetPos(0,5);
	LogPrint(_L("Re-enumerating...\n"));
	usb.ReEnumerate(enum_status);
	User::LeaveIfError(error);
	console->SetPos(0,5);
	User::WaitForRequest(enum_status);
	if(enum_status.Int() == KErrNone)
		LogPrint(_L("Re-enumeration Done\n"));
	else
		LogPrint(_L("Re-enumeration not successfully done\n"));


    console->SetPos(0,14);
    TBuf<3>password(KDefPwd);
    LogPrint(_L("Password: %S"), &password);

	ShowDriveSelection();

	console->SetPos(0,17);

	_LIT(KMsgTitleB,"Menu: q=quit  d=chg drv\n      m=mount u=unmount\n       l=lock i=lock n=unlock\n      c=clr pwd");


	//RDebug::Print(_L("USBMSAPP: Start CActiveScheduler\n"));

	console->Printf(KMsgTitleB);

	CActiveScheduler::Start();

	error = UsbMs.Stop();
	User::LeaveIfError(error);
	UsbMs.Close();
	error = fs.RemoveFileSystem(KMsFs);
	User::LeaveIfError(error);

	CleanupStack::PopAndDestroy(11);

	iOtgPort.StopStacks();
	iOtgPort.Close();
	error = User::FreeLogicalDevice(RUsbOtgDriver::Name());
	User::LeaveIfError(error);

	error = User::FreeLogicalDevice(_L("USBC"));
	User::LeaveIfError(error);

	}