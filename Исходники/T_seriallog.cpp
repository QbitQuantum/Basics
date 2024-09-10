LOCAL_C void doOpenSerialL(RBusDevComm& aSerial, TInt aPort)
	{
	TInt error;
#if defined (__WINS__)
	error=User::LoadPhysicalDevice(_L("ECDRV"));
#else
	error=User::LoadPhysicalDevice(_L("EUART1"));
	if (error==KErrNone||error==KErrAlreadyExists)
		error=User::LoadPhysicalDevice(_L("EUART2"));
	if (error==KErrNone||error==KErrAlreadyExists)
		error=User::LoadPhysicalDevice(_L("EUART3"));
	if (error==KErrNone||error==KErrAlreadyExists)
		error=User::LoadPhysicalDevice(_L("EUART4"));
#endif
	if (error==KErrNone||error==KErrAlreadyExists||error==KErrNotFound)
		error=User::LoadLogicalDevice(_L("ECOMM"));
	if (error==KErrAlreadyExists)
		error=KErrNone;
	User::LeaveIfError(error);

	test.Printf(_L("Loaded serial device drivers.\n"));

	// Open serial port.
	User::LeaveIfError(aSerial.Open(aPort));
	User::LeaveIfError(SetSerialConfiguration(aSerial));

	test.Printf(_L("Opened serial port.\n"));
	}