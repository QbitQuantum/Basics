//	Function updates the HotLap screen for HPDE's and track days, based upon user choices for Race Sessions selected
DWORD* CDlgTimingScoring::TimingScoringProc(LPVOID pv, HWND hWnd)
{
  LPCTSTR lpszPath = (LPCTSTR)pv;
  CSfArtSQLiteDB sfDB;
  vector<wstring> lstTables;
//  HL_hWnd = GetDlgItem(hWnd, IDC_TIMINGSCORING);
  if(SUCCEEDED(sfDB.Open(lpszPath, lstTables, true)))
  {
	  //	Race ID's are stored in the sfResult.m_RaceId structure
	  int z = 0;
	  int z_RaceId[50] = {-1};
	  while (m_sfResult->m_RaceId[z] >= 0 && z < 50)
	  {
		z_RaceId[z] = m_sfResult->m_RaceId[z];
		z++;
	  }
	  vector<wstring> lstPos;
      vector<wstring> lstRaceName;
      vector<wstring> lstComment;
	  vector<wstring> lstLapTimes;
      CSfArtSQLiteQuery sfQuery(sfDB);
	  TCHAR szTmp[1080] = {NULL};
	  //	Now cycle through all selected RaceId's and get their laptimes and sort them
	  TCHAR szTemp[1080] = L"select races.name,laps.laptime,extras.comment from laps,races left join extras on extras.lapid = laps._id where laps.raceid=races._id and (";
	  for (int y = 0; y < z; y++)
	  {
			int s_RaceId = z_RaceId[y];
			if (s_RaceId != 0)
			{
				_snwprintf(szTemp, NUMCHARS(szTemp), L"%sraces._id = %i or ", szTemp, s_RaceId);
			}
	  }
	  swprintf(szTmp, wcslen(szTemp) - 3, L"%s", szTemp);
	  _snwprintf(szTemp, NUMCHARS(szTemp), L"%s) order by laptime asc limit 40", szTmp);
	  if(sfQuery.Init(szTemp))
	  {
			SYSTEMTIME st;
			GetSystemTime(&st);
			int z = 1;
			TCHAR szPos[MAX_PATH] = {NULL};
			TCHAR szRaceName[300] = {NULL};
			TCHAR szComment[300] = {NULL};
			TCHAR szLap[300] = {NULL};
			//	Load up all of the HL vectors with data from the database
			while(sfQuery.Next())
			{
			  float flLapTime = 0;
			  sfQuery.GetCol(0,szRaceName,NUMCHARS(szRaceName));
			  sfQuery.GetCol(1,&flLapTime);
			  sfQuery.GetCol(2,szComment,NUMCHARS(szComment));

			  ::FormatTimeMinutesSecondsMs(flLapTime,szLap,NUMCHARS(szLap));
			  _snwprintf(szPos,NUMCHARS(szPos),L"%i",z);
			  lstPos.push_back(szPos);
			  lstRaceName.push_back(szRaceName);
			  lstComment.push_back(szComment);
			  lstLapTimes.push_back(szLap);
			  z++;
			}
//			HWND HL_hWnd = GetDlgItem(hWnd, IDC_TIMINGSCORING);
			ListView_DeleteAllItems(HL_hWnd);	//	Clear the list before displaying the update
			ClearHotLaps();	//	Clear the Top 40 Hot Laps list before updating
			TCHAR szText[MAX_PATH] = {NULL};

			// set up list view items
			int nItem;
//			LVITEM p_HLlvi;
			LPWSTR result;
			for (nItem = 0; nItem < z - 1; ++nItem)
			{
				p_HLlvi.mask = LVIF_TEXT | LVIF_PARAM;
				p_HLlvi.iItem = nItem;
				p_HLlvi.iSubItem = 0;
				p_HLlvi.lParam = nItem;
				std::wstring strPos(lstPos[nItem]);
				result = (LPWSTR)strPos.c_str();		  
				p_HLlvi.pszText = result;
				p_HLlvi.cchTextMax = wcslen(result);
				ListView_InsertItem(HL_hWnd, &p_HLlvi);

				// set up subitems
				p_HLlvi.mask = LVIF_TEXT;
				p_HLlvi.iItem = nItem;

				p_HLlvi.iSubItem = 1;
				std::wstring strRace(lstRaceName[nItem]);
				result = (LPWSTR)strRace.c_str();		  
				//From TCHAR to DWORD.
//				DWORD dwSomeNum;
//				dwSomeNum = wcstod(result, _T('\0'));
//				p_HLlvi.lParam = (LPARAM) dwSomeNum;	//	Try this for LPARAM
				p_HLlvi.lParam = nItem;
				p_HLlvi.pszText = result;
				p_HLlvi.cchTextMax = wcslen(result);
				ListView_SetItem(HL_hWnd, &p_HLlvi);

				p_HLlvi.iSubItem = 2;
				std::wstring strComment(lstComment[nItem]);
				result = (LPWSTR)strComment.c_str();		  
				//From TCHAR to DWORD.
//				dwSomeNum = wcstod(result, _T('\0'));
//				p_HLlvi.lParam = (LPARAM) dwSomeNum;	//	Try this for LPARAM
				p_HLlvi.lParam = nItem;
				p_HLlvi.pszText = result;
				p_HLlvi.cchTextMax = wcslen(result);
				ListView_SetItem(HL_hWnd, &p_HLlvi);

				p_HLlvi.iSubItem = 3;
				p_HLlvi.pszText = (LPWSTR)&lstLapTimes[nItem];
				std::wstring strLapTimes(lstLapTimes[nItem]);
				result = (LPWSTR)strLapTimes.c_str();		  
				//From TCHAR to DWORD.
//				dwSomeNum = wcstod(result, _T('\0'));
//				p_HLlvi.lParam = (LPARAM) dwSomeNum;	//	Try this for LPARAM
				p_HLlvi.lParam = nItem;
				p_HLlvi.pszText = result;
				p_HLlvi.cchTextMax = wcslen(result);
				ListView_SetItem(HL_hWnd, &p_HLlvi);
			}
	  
			//	Now load the RACERESULTS vectors with the Top 40 Hot Laps for saving to a text file
			for (int y = 0; y < z -1; y++)
			{
				std::wstring strPos(lstPos[y]);
				result = (LPWSTR)strPos.c_str();		  
				_snwprintf(m_ScoringData[y].lstPos, NUMCHARS(m_ScoringData[y].lstPos), result);

				std::wstring strRace(lstRaceName[y]);
				result = (LPWSTR)strRace.c_str();		  
				_snwprintf(m_ScoringData[y].lstRaceName, NUMCHARS(m_ScoringData[y].lstRaceName), result);

				std::wstring strComment(lstComment[y]);
				result = (LPWSTR)strComment.c_str();		  
				_snwprintf(m_ScoringData[y].lstComment, NUMCHARS(m_ScoringData[y].lstComment), result);

				std::wstring strLapTimes(lstLapTimes[y]);
				result = (LPWSTR)strLapTimes.c_str();		  
				_snwprintf(m_ScoringData[y].lstLapTimes, NUMCHARS(m_ScoringData[y].lstLapTimes), result);
			}
	  }
	  lstPos.clear();
	  lstRaceName.clear();
	  lstComment.clear();
	  lstLapTimes.clear();
	  sfDB.Close();
  }
  return 0;
}