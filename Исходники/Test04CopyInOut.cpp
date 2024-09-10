enum TVerdict CTest04CopyInOut::doTestStepL(void)
	{
	__UHEAP_MARK;
	
#ifdef __CFLOG_ACTIVE
	__CFLOG_CREATEL;
	__CFLOG_OPEN;
#endif
	
	//-------------- substep 1 --------------------
	Log(_L("  01 Create CMBufManager and install active scheduler:"));
    CleanupStack::PushL( iActSch = new(ELeave) CActiveScheduler );
	CActiveScheduler::Install(iActSch);
	CleanupStack::PushL(CreateInstanceMBufMgrL(KMBufDefaultHeapSize));

	//-------------- substep 2 --------------------
	Log(_L("  02 Allocate two 5000-bytes long descriptors (Des1 & Des2):"));
	TBuf8<5000> *aDes1, *aDes2;
    CleanupStack::PushL( aDes1 = new(ELeave) TBuf8<5000> );
    CleanupStack::PushL( aDes2 = new(ELeave) TBuf8<5000> );
	aDes1->SetLength(5000);
	aDes2->SetLength(5000);

	//-------------- substep 3 --------------------
	Log(_L("  03 Fill in the Des1 with a pattern:"));
	StripeDes(*aDes1, 0, 5000, '@', 'Z');

	//-------------- substep 4 --------------------
	Log(_L("  04 Allocate 5000-bytes long RMBufChain:"));
	RMBufChain aChain;
	TRAPD(ret,aChain.AllocL(5000));
	if (ret != KErrNone)
		{
		Log(_L("Error: Couldn't allocate RMBuf:"));

#ifdef __CFLOG_ACTIVE
		__CFLOG_CLOSE;
		__CFLOG_DELETE;
#endif
		User::Leave(EFail);
		}

	//-------------- substep 5 --------------------
	Log(_L("  05 Copy in Des1 into Chain:"));
    aChain.CopyIn(*aDes1);

	//-------------- substep 6 --------------------
	Log(_L("  06 Fill in Des2 with zeros:"));
	StripeDes(*aDes2, 0, 5000, 0, 0);

	//-------------- substep 7 --------------------
	Log(_L("  07 Copy out Chain into Des2:"));
    aChain.CopyOut(*aDes2);

	//-------------- substep 8 --------------------
	Log(_L("  08 Compare the contents of Des1 & Des2:"));
	if(aDes1->Compare(*aDes2))
		{
		Log(_L("Error: The content is not the same"));
		aChain.Free();

#ifdef __CFLOG_ACTIVE
		__CFLOG_CLOSE;
		__CFLOG_DELETE;
#endif
		User::Leave(EFail);
		}

	//-------------- substep 9 --------------------
	Log(_L("  09 Free chain. Clean up stack:"));
	aChain.Free();
    CleanupStack::PopAndDestroy(aDes2);
    CleanupStack::PopAndDestroy(aDes1);
    CleanupStack::PopAndDestroy(iMBMngr);
	CActiveScheduler::Install(NULL);
	CleanupStack::PopAndDestroy(iActSch);

#ifdef __CFLOG_ACTIVE
	__CFLOG_CLOSE;
	__CFLOG_DELETE;
#endif
 	__UHEAP_MARKEND;
	return EPass;
	}