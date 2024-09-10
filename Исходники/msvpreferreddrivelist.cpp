void CMsvPreferredDriveList::Print()
	{
	_LIT8(KLtBracket, "[");
	_LIT8(KRtBracket, "]: DRIVE-NUM: ");
	_LIT8(KDriveId, " DRIVE-ID: ");
	_LIT8(KStatus, " STATUS: ");
	_LIT8(KAvailable, "EMsvMessageStoreAvailableStatus");
	_LIT8(KUnavailable, "EMsvMessageStoreUnavailableStatus");
	_LIT8(KNotSupported, "EMsvMessageStoreNotSupportedStatus");
	_LIT8(KDiskNotAvailable, "EMsvDriveDiskNotAvailableStatus");
	_LIT8(KCorruptStore, "EMsvMessageStoreCorruptStatus");
	_LIT8(KInvalid, "EMsvInvalidDriveStatus");
		
	RFileLogger logger;
	if (logger.Connect() == KErrNone)
		{
		logger.CreateLog(_L("msgs"), _L("DriveList.txt"), EFileLoggingModeAppend);
		logger.SetDateAndTime(EFalse, EFalse);
		logger.Write(_L(" Preferred Drive List:"));
		logger.Write(_L("--------------------------------"));
		logger.Write(_L(""));
		}
	
	TInt count = Count();
	for(TInt index = 0; index < count; ++index)
		{		
		RBuf8 text;
		text.CreateL(100);
		text.Append(KLtBracket);
		text.AppendNum(index);
		text.Append(KRtBracket);
		text.AppendNum((*iDrives)[index].driveNum);
		text.Append(KDriveId);
		text.AppendNum((*iDrives)[index].driveId);
		text.Append(KStatus);
		switch((*iDrives)[index].status)
			{	
			case EMsvMessageStoreAvailableStatus:
				text.Append(KAvailable);
				break;
			case EMsvMessageStoreUnavailableStatus:
				text.Append(KUnavailable);
				break;
			case EMsvMessageStoreNotSupportedStatus:
				text.Append(KNotSupported);
				break;
			case EMsvDriveDiskNotAvailableStatus:
				text.Append(KDiskNotAvailable);
				break;
			case EMsvMessageStoreCorruptStatus:
				text.Append(KCorruptStore);
				break;
			case EMsvInvalidDriveStatus:
				text.Append(KInvalid);
				break;
			}
				
		logger.Write(text);
		text.Close();		
		logger.Write(_L(""));
		}
	logger.CloseLog();
	logger.Close();
	}