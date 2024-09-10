void CSchedulerWnd::OnSchedulerActivate()
{
	HRESULT hr;

	CString sTaskName = GetItem( m_wndList.GetNextItem( -1, LVIS_SELECTED ) );
	if ( sTaskName.IsEmpty() )
		return;

	CComPtr< ITask > pTask;
	hr = m_pScheduler->Activate( sTaskName, IID_ITask, (IUnknown**)&pTask );
	if ( FAILED( hr ) )
		return;

	DWORD nFlags = 0;
	hr = pTask->GetFlags( &nFlags );
	if ( ( nFlags & TASK_FLAG_DISABLED ) == TASK_FLAG_DISABLED )
	{
		hr = pTask->SetFlags( nFlags & ~TASK_FLAG_DISABLED );
		if ( SUCCEEDED( hr ) )
		{
			CComQIPtr< IPersistFile > pFile( pTask );
			if ( pFile )
			{
				hr = pFile->Save( NULL, TRUE );
				if ( SUCCEEDED( hr ) )
				{
					Update();
				}
			}
		}
	}
}