int CFileLoaderThread::DoThreadWork()
{
	int i;
	// Check for shutdown event
	if ( WAIT_OBJECT_0 == WaitForSingleObject( GetShutdownHandle(), 0 ) )
	{
		return 0;
	}

	// No changes to list right now
	Lock();
	// Move new items to work list
	int newItems = m_FileList.Count();
	for ( i = 0; i < newItems; i++ )
	{
		// Move to pending and issue async i/o calls
		m_Pending.AddToTail( m_FileList[ i ] );

		m_nTotalPending++;
	}
	m_FileList.RemoveAll();
	// Done adding new work items
	Unlock();

	int remaining = m_Pending.Count();
	if ( !remaining )
		return 1;

	int workitems = remaining; // min( remaining, 1000 );

	CUtlVector< SentenceRequest * > transfer;

	for ( i = 0; i < workitems; i++ )
	{
		SentenceRequest *r = m_Pending[ 0 ];
		m_Pending.Remove( 0 );

		transfer.AddToTail( r );
		// Do the work
		
		m_nTotalProcessed++;

		r->valid = SceneManager_LoadSentenceFromWavFileUsingIO( r->filename, r->sentence, m_ThreadIO );
	}

	// Now move to completed list
	Lock();
	for ( i = 0; i < workitems; i++ )
	{
		SentenceRequest *r = transfer[ i ];
		if ( r->valid )
		{
			m_nTotalCompleted++;

			m_Completed.AddToTail( r );
		}
		else
		{
			delete r;
		}
	}
	Unlock();
	return 1;
}