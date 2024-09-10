void ThreadedFileWorker::HandleRequest( int iRequest )
{
	{
		m_DeletedFilesLock.Lock();
		vector<RageFileBasic *> apDeletedFiles = m_apDeletedFiles;
		m_apDeletedFiles.clear();
		m_DeletedFilesLock.Unlock();

		for( unsigned i = 0; i < apDeletedFiles.size(); ++i )
			delete apDeletedFiles[i];
	}

	/* We have a request. */
	switch( iRequest )
	{
	case REQ_OPEN:
		ASSERT( m_pResultFile == NULL );
		ASSERT( !m_sRequestPath.empty() );
		m_iResultRequest = 0;
		m_pResultFile = m_pChildDriver->Open( m_sRequestPath, m_iRequestMode, m_iResultRequest );
		break;

	case REQ_CLOSE:
		ASSERT( m_pRequestFile != NULL );
		delete m_pRequestFile;

		/* Clear m_pRequestFile, so RequestTimedOut doesn't double-delete. */
		m_pRequestFile = NULL;
		break;

	case REQ_GET_FILE_SIZE:
		ASSERT( m_pRequestFile != NULL );
		m_iResultRequest = m_pRequestFile->GetFileSize();
		break;

	case REQ_SEEK:
		ASSERT( m_pRequestFile != NULL );
		m_iResultRequest = m_pRequestFile->Seek( m_iRequestPos );
		m_sResultError = m_pRequestFile->GetError();
		break;

	case REQ_READ:
		ASSERT( m_pRequestFile != NULL );
		ASSERT( m_pResultBuffer != NULL );
		m_iResultRequest = m_pRequestFile->Read( m_pResultBuffer, m_iRequestSize );
		m_sResultError = m_pRequestFile->GetError();
		break;

	case REQ_WRITE:
		ASSERT( m_pRequestFile != NULL );
		ASSERT( m_pRequestBuffer != NULL );
		m_iResultRequest = m_pRequestFile->Write( m_pRequestBuffer, m_iRequestSize );
		m_sResultError = m_pRequestFile->GetError();
		break;

	case REQ_FLUSH:
		ASSERT( m_pRequestFile != NULL );
		m_iResultRequest = m_pRequestFile->Flush();
		m_sResultError = m_pRequestFile->GetError();
		break;

	case REQ_COPY:
		ASSERT( m_pRequestFile != NULL );
		m_pResultFile = m_pRequestFile->Copy();
		break;

	case REQ_POPULATE_FILE_SET:
		ASSERT( !m_sRequestPath.empty() );
		m_ResultFileSet = FileSet();
		m_pChildDriver->FDB->GetFileSetCopy( m_sRequestPath, m_ResultFileSet );
		break;

	case REQ_FLUSH_DIR_CACHE:
		m_pChildDriver->FlushDirCache( m_sRequestPath );
		break;

	case REQ_REMOVE:
		ASSERT( !m_sRequestPath.empty() );
		m_iResultRequest = m_pChildDriver->Remove( m_sRequestPath )? 0:-1;
		break;

	case REQ_MOVE:
		ASSERT( !m_sRequestPath.empty() );
		ASSERT( !m_sRequestPath2.empty() );
		m_iResultRequest = m_pChildDriver->Move( m_sRequestPath, m_sRequestPath2 ) ? 0 : -1;
		break;

	default:
		FAIL_M( ssprintf("%i", iRequest) );
	}
}