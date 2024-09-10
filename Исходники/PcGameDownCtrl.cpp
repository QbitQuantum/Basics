void PcGameDownCtrl::OnTimer(UINT nIDEvent)
{
/*
	DWORD dwRet = WaitForMultipleObjects (MAX_PATH, m_eDecompress, FALSE, 0);
	if (dwRet != WAIT_TIMEOUT && dwRet < MAX_PATH)
	{
		DWORD dwIndex = dwRet - WAIT_OBJECT_0;

		map<DWORD, pair<string, DecompressOperator> >::iterator itDecompress = m_DecompressCache.find (dwIndex);
		if (itDecompress != m_DecompressCache.end ())
		{
			string strGameID = itDecompress->second.first;
			GLOBAL_DOWNDATA->LockDownInfoList ();
			ExeDownInfo * pInfo = const_cast<ExeDownInfo*> (GLOBAL_DOWNDATA->GetDownInfo (strGameID));
			GLOBAL_DOWNDATA->UnlockDownInfoList ();

			switch (itDecompress->second.second)
			{
			case DO_QUICKPLAY:
				// 填充游戏的可执行文件的路径
				if (pInfo != NULL)
				{
					pInfo->gameInfo.strExePath = pInfo->gameInfo.strDownPath;
					WriteExePath (pInfo->gameInfo.strExePath);
				}
				NotifyDownQuickPlay (strGameID);
				break;
			case DO_FINISH:
				// 填充游戏的可执行文件的路径
				if (pInfo != NULL)
				{
					pInfo->gameInfo.strExePath = pInfo->gameInfo.strDownPath;
					WriteExePath (pInfo->gameInfo.strExePath);
				}
				NotifyDownFinish (strGameID);
				CSingleLock sl( &m_cs );
				sl.Lock ();
				map<string,YL_CHTTPDownFile*>::iterator it3 = m_mapDownThread.find (strGameID);
				if( it3 != m_mapDownThread.end() )
				{
					delete it3->second;
					m_mapDownThread.erase( it3 );
				}
				sl.Unlock ();
				break;
			}

			m_DecompressCache.erase (itDecompress);
			ResetEvent (m_eDecompress[dwIndex]);
		}
	}
*/
	if( nIDEvent == TIMER_CHECK_DOWN_STATE )
	{
		CSingleLock sl( &m_cs );
		sl.Lock();
		if( m_mapDownThread.size() == 0 )
			KillTimer( TIMER_CHECK_DOWN_STATE ); 

		vector<string> vecGidFinish; //要从任务中删除的gid
		vector<string> vecStartDownSecPart;

		for( map<string,YL_CHTTPDownFile*>::iterator it1 = m_mapDownThread.begin();
			it1 != m_mapDownThread.end(); it1++ )
		{
			string strGid = it1->first;
			YL_CHTTPDownFile* pHttpDownFile = it1->second;
			if( pHttpDownFile->IsDownloadFailed() )
			{
				//获取下载失败的原因
				NotifyDownFailed( strGid, pHttpDownFile->GetFailedReason() );
				vecGidFinish.push_back( strGid );
			}else
			{
				double dDownPercentage = pHttpDownFile->GetCurrentDownloadStatus();
				if( dDownPercentage < 1 )
				{
					NotifyDownProgress( strGid, dDownPercentage,
						pHttpDownFile->GetFileSize(), pHttpDownFile->GetSpeed());
				}else
				{
GLOBAL_DOWNDATA->LockDownInfoList ();
					ExeDownInfo * pInfo = const_cast<ExeDownInfo*> (GLOBAL_DOWNDATA->GetDownInfo (strGid));
GLOBAL_DOWNDATA->UnlockDownInfoList ();

					if (pInfo == NULL)
						continue;

					if (pInfo->dnc == DNC_DECOMPRESS)
					{
						DWORD dwRet = WaitForSingleObject (pInfo->hEventDecompress, 0);
						if (dwRet == WAIT_OBJECT_0)
						{
							if (pInfo->gameInfo.uiStartPoint == 0)
							{
								pInfo->dnc = DNC_FINISHED;
								pInfo->dsZip1.dnc = DNC_FINISHED;
							}
							else
							{
								if (pInfo->dsZip1.dnc != DNC_FINISHED)
								{
									pInfo->dsZip1.dnc = DNC_FINISHED;
									pInfo->dnc = DNC_DOWNING;

									pInfo->gameInfo.strExePath = pInfo->gameInfo.strDownPath;
									WriteExePath (pInfo->gameInfo.strExePath);
									NotifyDownQuickPlay (strGid);

									vecStartDownSecPart.push_back (strGid);
									continue;
								}
								else
								{
									pInfo->dnc = DNC_FINISHED;
									pInfo->dsZip1.dnc = DNC_FINISHED;
									pInfo->dsZip2.dnc = DNC_FINISHED;
								}
							}
						}
						else
						{
							NotifyDownCompress (strGid);
							continue;
						}
					}

					if (pInfo->dnc == DNC_FINISHED)
					{
						pInfo->gameInfo.strExePath = pInfo->gameInfo.strDownPath;
						WriteExePath (pInfo->gameInfo.strExePath);
						NotifyDownFinish (strGid);

						vecGidFinish.push_back (strGid);
					}
					else
					{
// 						if (pInfo->dsZip1.dnc != DNC_FINISHED)
// 						{
							pInfo->dnc = DNC_DECOMPRESS;

							DWORD   dwThreadID;	
							DecompressThreadParam * param = new DecompressThreadParam ();

							if (pInfo->dsZip1.dnc != DNC_FINISHED)
								param->strSrc = pInfo->gameInfo.strDownPath + "\\zip1";
							else
								param->strSrc = pInfo->gameInfo.strDownPath + "\\zip2";

							string::size_type pos = pInfo->gameInfo.strDownPath.find ("downCache");
							if (pos != string::npos)
							{
								param->strDes = pInfo->gameInfo.strDownPath.substr (0, pos);
								param->pDownCtrl = this;

								pInfo->hEventDecompress = CreateEvent (NULL, TRUE, FALSE, NULL);
								param->hEvent = pInfo->hEventDecompress;

								CloseHandle (CreateThread(NULL, 0,
									(LPTHREAD_START_ROUTINE)Decompress, (LPVOID)param, 0, &dwThreadID));
							}
// 						}
// 						else
// 						{
// 						}
					}
				}
			}
		}
		
		vector<string>::iterator itFinish = vecGidFinish.begin ();
		for (; itFinish != vecGidFinish.end (); itFinish++)
		{
			map<string,YL_CHTTPDownFile*>::iterator it = m_mapDownThread.find (*itFinish);
			if( it != m_mapDownThread.end() )
			{
				delete it->second;
				m_mapDownThread.erase (it);
			}
		}

		sl.Unlock();

		for (vector<string>::iterator itSecPart = vecStartDownSecPart.begin (); 
			itSecPart != vecStartDownSecPart.end (); itSecPart++)
		{
			sl.Lock ();
			map<string,YL_CHTTPDownFile*>::iterator itTmp = m_mapDownThread.find (*itSecPart);
			if( itTmp != m_mapDownThread.end() )
			{
				delete itTmp->second;
				m_mapDownThread.erase( itTmp );
			}
			sl.Unlock ();

			StartDown (*itSecPart);
		}
	}

	CWnd::OnTimer(nIDEvent);
}