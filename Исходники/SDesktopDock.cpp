void SDesktopDock::OnLButtonUp(UINT nFlags, CPoint point)
{
	for (int i=0; i<MAX_COUNT; i++)
	{
		if (m_RTRect[i].PtInRect(point))
		{
			TCHAR chTemp[MAX_PATH]=_T("");
			wsprintfW(chTemp,TEXT("索引===%d号"), i);
			SMessageBox(NULL,chTemp,L"多点WIFI",MB_OK);
			if (i==0){
				ShellExecute(NULL, L"open",L"http://www.wf06.com", NULL, NULL, SW_SHOWNORMAL);

			}else if (i==1){

				ShellExecute(NULL, L"open",L"http://www.sk53.com", NULL, NULL, SW_SHOWNORMAL);
			}


			return ;
		}
	}
}