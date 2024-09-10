int CDownloadTask::Run()
{
//	if ( theApp.m_bIsVistaOrNewer )
//		::SetThreadPriority( GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN );	// Too aggressive?

	BOOL bCOM = SUCCEEDED( OleInitialize( NULL ) );

	switch ( m_nTask )
	{
	case dtaskCopy:
		RunCopy();
		break;
	case dtaskMergeFile:
		RunMerge();
		break;
	case dtaskPreviewRequest:
		RunPreviewRequest();
	//	break;
	}

	if ( bCOM )
		OleUninitialize();

	return 0;
}