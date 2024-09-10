BOOL CPatrolPath::LoadPatrol( LPCTSTR szFileName )
{
	CScript s;
	if( s.Load( szFileName, FALSE ) )
	{
		Clear();
		
		DWORD nIndex = 0;
		D3DXVECTOR3 v3Pos;
		vector<D3DXVECTOR3> v3PosList;
		_VECINFO vecInfo;
		_VECINFO vecInfoBackup;
		
		s.GetToken();
		
		while( s.tok != FINISHED )
		{
			if( s.Token == _T( "INDEX" ) )
			{
				v3PosList.clear();
				nIndex = s.GetNumber();
				AddPatrolIndex( nIndex );
			}
			
			s.GetToken();
			
			int nCount = s.GetNumber();
			
			while( s.Token != _T( "}" ) )
			{
				v3Pos.x = s.GetFloat();
				v3Pos.y = s.GetFloat();
				v3Pos.z = s.GetFloat();

				v3PosList.push_back( v3Pos );
				
				if( nCount != 0 )
				{
					vecInfo.m_vDir.x = s.GetFloat();
					vecInfo.m_vDir.y = s.GetFloat();
					vecInfo.m_vDir.z = s.GetFloat();
					vecInfo.m_dwState = s.GetNumber();
					vecInfo.m_dwDelay = s.GetNumber();
					vecInfo.m_fLength = s.GetFloat();	
					
					AddPatrolPath( nIndex, vecInfo );
				}	
				
				if( nCount == 1 )
				{
					vecInfoBackup = vecInfo;
				}
				
				nCount = s.GetNumber();
			}

			D3DXVECTOR3	v3Pos1 = v3PosList[0];
			D3DXVECTOR3	v3Pos2 = v3PosList[v3PosList.size()-1];
			D3DXVECTOR3	v3Dir  = v3Pos1 - v3Pos2;

			D3DXVec3Subtract( &v3Dir, &v3Pos1, &v3Pos2 );
			D3DXVec3Normalize( &vecInfoBackup.m_vDir, &v3Dir );		
			vecInfoBackup.m_fLength = D3DXVec3Length( &v3Dir );			

			AddPatrolPath( nIndex, vecInfoBackup );
			
			
			s.GetToken();			
		}
	}	
	else
	{
		return FALSE;
	}
	
	return TRUE;	
}