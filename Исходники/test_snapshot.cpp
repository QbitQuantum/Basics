void CTestCamSnapshot::DoStartSnapshotL()
	{
	CFbsBitmap* snapshot = new(ELeave) CFbsBitmap;
	CleanupStack::PushL(snapshot);
	User::LeaveIfError(snapshot->Create(iSnapshotImageRect.Size(), iSnapshotImage->DisplayMode()));
	CFbsBitmapDevice* dev = CFbsBitmapDevice::NewL(snapshot);
	CleanupStack::PushL(dev);
	CFbsBitGc* gc = NULL;
	User::LeaveIfError(dev->CreateContext(gc));
	CleanupStack::Pop(dev);
	CleanupStack::Pop(snapshot);
	
	iSnapshot = snapshot;
	iSnapshotDev = dev;
	iSnapshotGc = gc;
		
	iSnapshotActive = ETrue;
	}