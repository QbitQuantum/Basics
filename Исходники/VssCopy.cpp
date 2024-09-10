	VssCopy::~VssCopy()
	{
		//Free resource allocated by GetSnapshotProperties()
		if (snapshotProperties_ != nullptr)
		{
			VssFreeSnapshotProperties(snapshotProperties_);
			delete snapshotProperties_;
		}

		//Free resource allocated by SetBackupState()
		if (backupState_)
		{
			try
			{
				CComPtr<IVssAsync> pBackupCompleteResults;
				CHECK_HRESULT( pBackupComponents_->BackupComplete(&pBackupCompleteResults) );
				WaitAndQueryStatus(pBackupCompleteResults);

				CHECK_HRESULT( pBackupComponents_->FreeWriterMetadata() );
			}
			catch (CAtlException&)
			{
			}
		}

		CoUninitialize();
	}