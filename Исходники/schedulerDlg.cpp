int CschedulerDlg::storeNote(void)
{
// 	FILE	*f;
// 	char	abuff[KS_MAX_NOTE];
// 	TCHAR	wbuff[KS_MAX_NOTE];
// 	int		count,i;
// 	CString tempstr;
// 
// 	fopen_s(&f,KS_CONF_FILE,"w+");
// 	if(f!=0)
// 	{
// 		count=m_list.GetItemCount();
// 		fprintf(f,"%d\n",count);
// 		for(i=0;i<count;i++)
// 		{	
// 			abuff[0]=0;
// 			tempstr=m_list.GetItemText(i,0);
// 			tempstr.Replace(' ','*');
// 			WideCharToMultiByte(CP_UTF8,0,tempstr,-1,abuff,KS_MAX_NOTE,0,0);
// 			fprintf(f,"%s\n",abuff);
// 
// 			abuff[0]=0;
// 			//m_list.GetItemText(i,1,wbuff,KS_MAX_NOTE);			
// 			//WideCharToMultiByte(CP_UTF8,0,wbuff,-1,abuff,KS_MAX_NOTE,0,0);
// 			tempstr=m_list.GetItemText(i,1);
// 			tempstr.Replace(' ','*');
// 			WideCharToMultiByte(CP_UTF8,0,tempstr,-1,abuff,KS_MAX_NOTE,0,0);
// 			fprintf(f,"%s\n",abuff);
// 
// 			abuff[0]=0;
// // 			m_list.GetItemText(i,2,wbuff,KS_MAX_NOTE);			
// // 			WideCharToMultiByte(CP_UTF8,0,wbuff,-1,abuff,KS_MAX_NOTE,0,0);
//  			tempstr=m_list.GetItemText(i,2);
// 			tempstr.Replace(' ','*');
// 			WideCharToMultiByte(CP_UTF8,0,tempstr,-1,abuff,KS_MAX_NOTE,0,0);
// 			fprintf(f,"%s\n",abuff);
// 		}
// 		fclose(f);
// 		return 1;
// 	}

	CStdioFile iof;
	int count;
	CString tempstr;
	TCHAR wbuff[KS_MAX_NOTE];	

	if(iof.Open(_T(KS_CONF_FILE),
		CFile::modeCreate |CFile::modeWrite|CFile::typeText))
	{
	count=m_list.GetItemCount();
	_itow_s(count,wbuff,KS_MAX_NOTE,10);
	iof.WriteString(wbuff);
	iof.WriteString(_T("\n"));

	for (int i=0;i<count;i++)
	{
		tempstr=m_list.GetItemText(i,0);
		iof.WriteString(tempstr);
		iof.WriteString(_T("\n"));

		tempstr=m_list.GetItemText(i,1);
		iof.WriteString(tempstr);
		iof.WriteString(_T("\n"));

		tempstr=m_list.GetItemText(i,2);
		iof.WriteString(tempstr);
		iof.WriteString(_T("\n"));
	}
	iof.Close();
	return 1;
	}
	iof.Close();
	return 0;
}