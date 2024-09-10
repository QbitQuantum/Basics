// Нажали Старт
void CAlsIzmFormView::OnBnClickedStartIzm()
{
	// TODO: добавьте свой код обработчика уведомлений
	// setup update timer (25 - 4hz)2c 1c
/*	timer = timeSetEvent(950,	//  — интервал времени до наступления таймерного события в миллисекундах.
						50,	//  — разрешение таймера при отсчете интервала, в миллисекундах. Нулевое значение требует максимально возможного разрешения 
						0, //  — указатель функции уведомления.
						0, //  — произвольное 32-разрядное значение, передаваемое функции уведомления при вызове в качестве параметра.
						TIME_PERIODIC); // тип таймерного события: TIME_ONESHOT — однократное, TIME_PERIODIC — периодическое.
	*/





	dataObject.MoveFirst();
	/////
	// получить доступ к объекту класса CMainFrame можно так:
///	CMainFrame *pMainFrame = (CMainFrame*)(::AfxGetMainWnd()); 
///	put = &pMainFrame->m_ViewPut;
	sss.Format(L"\xFEFF\r\nМаршрут\t%s\r\n",dataObject.m_ItineraryName);
	//sss =  L'\xFEFF'+ ssf;
	//sss += dataObject.m_ItineraryName;
	//sss += L"\r\n"; //+L"Маршрут\t"
	//sss += _T("\r\n" );
///	put->asimfile.SeekToEnd();
///	put->asimfile.Write(sss,sss.GetLength()*sizeof(TCHAR ));
	
//	dataObject.MoveNext();
	//AfxMessageBox(dataObject.m_ObgectName);
	//m_PK_obgect_start = m_PK_obgect;
	m_PK_obgect = dataObject.m_Pk;
	m_CurSel = 0;


	////
	   	if (FileTok.m_hFile!=(HANDLE)-1)
	{
		sss = L"\r\n";
		//
		CTime time = CTime::GetCurrentTime();
		sss += time.Format("%x %X\t");	   //%Y 
		//
		//sss += L"\t";
		sss += L"Маршрут: ";
		//sss += L"\t";
		sss += dataObject.m_ItineraryName;
		sss += L"\r\n";
		FileTok.SeekToEnd();
		FileTok.Write(sss, sss.GetLength()*sizeof(TCHAR));
 	}



	//Запустить навигацию OziExplorer
	if (m_gOziExplorer_OnOff)
	{
		COziExplorerApi OziExplorer; // Доступ к карте
		if (!OziExplorer.OziExplorerIsRun) return ; // если апи не загружен - выход
		if (OziExplorer.CheckOziExplorerRunning() == -1)
		{
			AfxMessageBox(L" Запуск OziExplorer от имени администратора. \n  Проверьте панель задач для подтверждения");

			////AfxMessageBox(L"OziExplorer Не запущен",0,0);
			//::ShellExecute(NULL, L"Open", m_gstrPathOz,
			//			   NULL,
			//			   m_gstrPathOz.Left(m_gstrPathOz.ReverseFind(_T('\\'))+1),
			//			   SW_SHOWNORMAL);
			//////////////////////////////////////////////////////////////////////////////
			SHELLEXECUTEINFO se;
			se.cbSize =sizeof(se);
			se.fMask = NULL;
			//se.hwnd = GetDesktopWindow();
			se.lpVerb = L"runas";
			se.lpFile = m_gstrPathOz;
			se.lpDirectory = m_gstrPathOz.Left(m_gstrPathOz.ReverseFind(_T('\\'))+1);
			se.nShow = SW_NORMAL;
			//se.lpParameters = 
			::ShellExecuteEx(&se);
			/////////////////////////////////////////////////////////////////////////////
			//Sleep(2000);
			do {}
			while (OziExplorer.CheckOziExplorerRunning());
			Sleep(3000);
			///////////////////////////////////////////////////////////
		}
	   // Получить маршрут
		m_Itinerary.GetLBText(m_Itinerary.GetCurSel(),sss);
		// Удалить старые путевые точки
		OziExplorer.ClearAllWaypoints();
		// Загрузить путевые точки
		if (OziExplorer.LoadWaypoint(&sss))  // 0 при удаче 
		{
			AfxMessageBox (L"Ошибка загрузки путевых точек  " + sss);
			return ;
		}
		// Загрузить маршрут
		//AfxMessageBox (L"Пытаемся загрузить маршрут" + sss);
		if (OziExplorer.LoadRoute(&sss))  // 0 при удаче 
		{
			AfxMessageBox (L"Ошибка загрузки маршрута  " + sss);
			return ;
		}
		//else 

		if (OziExplorer.StartMovingMapSerial()) // запустить навигацию,перед точками НЕ работает
		{
			AfxMessageBox(L"Не удаеться запустить связь с GPS",0,0);
			return ;
		}
		
		OziExplorer.ShowTrack(1); // показать трек

		////Запустить скоростиметр №1
		//////int res = oziOedometer1ON((int*)& Oedometer1);
		//////if (res)
		//////{
		//////	AfxMessageBox(L"Путимер НЕ запущен",0,0);
		//////	return ;			
		//////}
		//double m_gPiket;
		//m_gPiket = NULL;
		//m_gPiket = 333,0;
		//double* m_Pk;
		//m_Pk = & m_gPiket;
		//int mp;
		//mp = NULL;
		//int* mpp;
		//mpp = & mp;
		////if (OziExplorer.OedometerON(1, &m_gPiket, &mp))  // theApp.m_PK_current theApp.m_ipiketkp
		////{
		////	AfxMessageBox(L"Путимер НЕ запущен",0,0);
		////	return ;			
		////}
		////else AfxMessageBox(L"Путимер запущен",0,0);
		//}
	}
		////
	
	SetTimer(10, 500, NULL); //1000
}