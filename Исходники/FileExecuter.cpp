void CFileExecuter::OpenFileBySystemDefaultL(TFileName aFileName)
{
	#ifndef __SERIES60_3X__
	{
		//如果是Jar、Sis或Sisx文件则调用内容打开
		TInt nType=ParseExPathNum(aFileName);

		if (nType==2)
		{
			OpenAppFile(aFileName);

			return;
		}
	}
	#endif
	
	TDataType empty=TDataType();

	#ifdef __SERIES60_3X__
	{
		iDocHandler->SetExitObserver(this);

		TRAPD(error,iDocHandler->OpenFileEmbeddedL(aFileName,empty));
	}
	#else
	{
		iDocHandler->OpenFileL(aFileName,empty );

		//If the standalone handler is already running then update the
		//document file
		TUid handlerUid;
		TInt err = KErrNone;

		#ifdef __SERIES60_3X__
		err = iDocHandler->HandlerAppUid(handlerUid);
		#else
		RApaLsSession apaLs;
		User::LeaveIfError( apaLs.Connect() );
		err = apaLs.AppForDocument(aFileName, handlerUid, empty);  
		apaLs.Close();          
		#endif

		if( !err )
		{
			RefreshDocumentFileL(handlerUid, aFileName);
		}
		else if( err == KNotInitialized )
		{
			//Handler not initialized
		}
		else
		{
			//Some other error
		}

	}
	#endif
}