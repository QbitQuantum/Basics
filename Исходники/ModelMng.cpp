BOOL CModelMng::LoadScript( LPCTSTR lpszFileName )
{
	CScript script;
	if( script.Load( lpszFileName, FALSE ) == FALSE )
		return FALSE;

	CFixedArray< tagMODELELEM >* apModelElem; 
	TCHAR szObject[48];
	TCHAR szMotion[48];
	UINT iType, iObject, iMotion;
	MODELELEM modelElem;
	script.GetToken(); // subject or FINISHED
	while( script.tok != FINISHED )
	{
		iType = script.GetNumber();

		apModelElem = &m_aaModelElem[ iType ];
		script.GetToken(); // {
		script.GetToken(); // object name or }
		int nBrace = 1;
		// 여기부터 오브젝트 단위 obj, ctrl, item, sfx, mover
		while( nBrace )
		{
			ZeroMemory( &modelElem, sizeof( modelElem ) );
			if( *script.token == '}' ) 
			{
				nBrace--;
				if( nBrace > 0 )
				{
					script.GetToken(); // object name or }
					continue;
				}
				if( nBrace == 0 )
					continue;
			}
		#ifdef _DEBUG
			if( sizeof(szObject) <= strlen(script.token) + 1 )
				Error( "%s 스트링의 길이가 너무길다. %d", lpszFileName, strlen(script.token) );
		#endif

			_tcscpy( szObject, script.token ); // folder 또는 object name

			script.SetMark();
			// 스크립트 실수 검출 루틴 필요. - xuzhu -
			script.GetToken(); // {
			if( *script.token == '{' )
			{
				nBrace++;
				script.GetToken(); // object name or }
			#ifdef _DEBUG
				if( sizeof(szObject) <= strlen(script.token) + 1 )
					Error( "%s 스트링의 길이가 너무길다. %d", lpszFileName, strlen(script.token) );
			#endif

				_tcscpy( szObject, script.token ); // folder 또는 object name
				continue;
			}
			else
				script.GoMark();
			iObject = script.GetNumber();
			if( iObject == 0 )
			{
				CString str;
				str.Format( "CModelMng::LoadScript(%d) 0으로 지정된 모션 아이디 : %s, %s", script.GetLineNum(), szObject, script.token );
				AfxMessageBox( str );
			}
			modelElem.m_dwType = iType;
			modelElem.m_dwIndex = iObject;
		#ifdef _DEBUG
			if( sizeof(modelElem.m_szName) <= strlen(szObject) + 1 )
				Error( "%s 스트링의 길이가 너무길다. %d", lpszFileName, strlen(szObject) );
		#endif
			_tcscpy( modelElem.m_szName, szObject );
			modelElem.m_dwModelType = script.GetNumber();
			script.GetToken();
		#ifdef _DEBUG
			if( sizeof(modelElem.m_szPart) <= strlen(script.token) + 1 )
				Error( "%s 스트링의 길이가 너무길다. %d", lpszFileName, strlen(script.token) );
		#endif
			_tcscpy( modelElem.m_szPart, script.Token );
			modelElem.m_bFly = script.GetNumber();
			modelElem.m_dwDistant = script.GetNumber();
			modelElem.m_bPick = script.GetNumber();
			modelElem.m_fScale = script.GetFloat();
			modelElem.m_bTrans = script.GetNumber();
			modelElem.m_bShadow = script.GetNumber();			
			modelElem.m_bReserved = 0;
			modelElem.m_nTextureEx = script.GetNumber();
			modelElem.m_bRenderFlag = script.GetNumber();

			script.GetToken(); // object name or { or }
			// 여기부터 애니메이션 
			if( *script.token == '{' )
			{
				script.SetMark();
				script.GetToken(); // motion name or }
				int nMax = 0;
				// 모션 리스트 카운트 
				while( *script.token != '}' )
				{
				#ifdef _DEBUG
					if( sizeof(szMotion) <= strlen(script.token) + 1 )
						Error( "%s 스트링의 길이가 너무길다. %d", lpszFileName, strlen(script.token) );
				#endif
					_tcscpy( szMotion, script.token );
					iMotion = script.GetNumber();
					if( (int)( iMotion ) > nMax )
						nMax = iMotion;
					script.GetToken(); // motion name or }
				}
				nMax++;
				script.GoMark();
				// 실제 모션 리스트 세팅 
				script.GetToken(); // motion name or }
				modelElem.m_apszMotion = new TCHAR[ nMax * 32 ];
				modelElem.m_nMax = nMax;
				ZeroMemory( modelElem.m_apszMotion, sizeof( TCHAR ) * nMax * 32 );
				//TRACE( " %s %p\n", modelElem.m_szName, modelElem.m_apszMotion);
				while( *script.token != '}' )
				{
				#ifdef _DEBUG
					if( sizeof(szMotion) <= strlen(script.token) + 1 )
						Error( "%s 스트링의 길이가 너무길다. %d", lpszFileName, strlen(script.token) );
				#endif
					_tcscpy( szMotion, script.token );
					iMotion = script.GetNumber();
					TCHAR* lpszMotion = modelElem.GetMotion( iMotion );
					if( lpszMotion[0] )
					{
						CString str;
						str.Format( "CModelMng::LoadScript(%d) %s모션 중복 아이디 : %s", script.GetLineNum(), lpszFileName, lpszMotion );
						AfxMessageBox( str );
					}
					_tcscpy( lpszMotion, szMotion );
					script.GetToken(); // motion name or }
				}
				script.GetToken(); // object name or }
			}
			if( apModelElem->GetAt( iObject ) )
			{
				CString str;
				str.Format( "CModelMng::LoadScript(%d) %s중복 아이디 : type = %d, idx = %d, name = %s", script.GetLineNum(), lpszFileName, iType, iObject, modelElem.m_szName );
				AfxMessageBox( str );
			}

//////////////////////////////////////////////////////////

#ifndef __ENVIRONMENT_EFFECT

#ifdef __EVENT_FALL
			BOOL bEventFlag = FALSE;
			
			if( stricmp(modelElem.m_szName, "MaCoPrTr01") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr03") == 0 ||
				stricmp(modelElem.m_szName, "MaCoPrTr10") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr20") == 0 ||
				stricmp(modelElem.m_szName, "MaCoPrTr14") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr11") == 0 )
			{
				bEventFlag = TRUE;
				_tcscpy( modelElem.m_szName, "MapleTree01" );
			}
			
			if( stricmp(modelElem.m_szName, "MaCoPrTr04") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr05") == 0 ||
				stricmp(modelElem.m_szName, "MaCoPrTr12") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr15") == 0 ||
				stricmp(modelElem.m_szName, "MaCoPrTr13") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr02") == 0 )
			{
				bEventFlag = TRUE;
				_tcscpy( modelElem.m_szName, "MapleTree02" );
			}			

			if(	bEventFlag == TRUE )
				modelElem.m_fScale = 1.0f;	
#endif //__EVENT_FALL			
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
#ifdef __JAPAN_SAKURA
			BOOL bEventFlag = FALSE;
			
			if( stricmp(modelElem.m_szName, "MaCoPrTr01") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr03") == 0 ||
				stricmp(modelElem.m_szName, "MaCoPrTr10") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr20") == 0 ||
				stricmp(modelElem.m_szName, "MaCoPrTr14") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr11") == 0 )
			{
				bEventFlag = TRUE;
				_tcscpy( modelElem.m_szName, "MaCoPrTr16" );
			}
			
			if( stricmp(modelElem.m_szName, "MaCoPrTr04") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr05") == 0 ||
				stricmp(modelElem.m_szName, "MaCoPrTr12") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr15") == 0 ||
				stricmp(modelElem.m_szName, "MaCoPrTr13") == 0 || stricmp(modelElem.m_szName, "MaCoPrTr02") == 0 )
			{
				bEventFlag = TRUE;
				_tcscpy( modelElem.m_szName, "MaCoPrTr17" );
			}			

			if(	bEventFlag == TRUE )
			{
				modelElem.m_fScale = 1.0f;
			}
#endif //__JAPAN_SAKURA			

#endif // __ENVIRONMENT_EFFECT
//////////////////////////////////////////////////////////
			
		#ifdef __WORLDSERVER
			if( iType != OT_SFX )	// sfx는 서버에서 skip
				apModelElem->SetAtGrow( iObject, &modelElem );
		#else
			apModelElem->SetAtGrow( iObject, &modelElem );
		#endif

		} // while( nBrace )

		script.GetToken(); // type name or }
		apModelElem->Optimize();
	}	// while( script.tok != FINISHED )

	return TRUE;
}