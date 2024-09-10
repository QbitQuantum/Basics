void CAISenseRecorder::Update()
{
	// TODO: Optimize this so we don't do it every frame.

    LTFLOAT fTime = g_pLTServer->GetTime();

	for ( int iSense = 0 ; iSense < CAISense::kNumSenses ; iSense++ )
	{
		CAISenseRecord** ppRecord = m_alstpSenseRecords[iSense].GetItem(TLIT_FIRST);
		while ( ppRecord && *ppRecord )
		{
			if ( !(*ppRecord)->UpdateLifetime(fTime) )
			{
				Unlink((*ppRecord)->GetObject());
				FACTORY_DELETE((*ppRecord));
				m_alstpSenseRecords[iSense].Remove((*ppRecord));
				ppRecord = m_alstpSenseRecords[iSense].GetItem(TLIT_CURRENT);
			}
			else
			{
				ppRecord = m_alstpSenseRecords[iSense].GetItem(TLIT_NEXT);
			}
		}
	}
}