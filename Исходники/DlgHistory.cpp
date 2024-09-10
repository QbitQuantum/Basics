void CDlgHistory::OnBnClickedButtonExport()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_EXPORT)->EnableWindow(FALSE);
	COleVariant covTrue((short)TRUE),covFalse((short)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR); 
	book.PrintPreview(_variant_t(false));
	CFileDialog FileDialog(FALSE,"xlsx",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("Microsoft Excel 2007(*.xlsx)|*.xlsx|所有文件(*.*)"),this); 
	if(FileDialog.DoModal()!=IDOK) 
	{
		GetDlgItem(IDC_BUTTON_EXPORT)->EnableWindow(TRUE);
		return; 
	}
	CString cStrFile=FileDialog.GetPathName();  //选择保存路径名称
	if(::PathFileExists(cStrFile)) 
		DeleteFile(cStrFile); 
	CString AntID,SensorID,StrStartTime,StrStopTime,tmpData,passWord,StartTime,StopTime,message,strRecordTime,rowCount,strRow,strLimit;
	StrStartTime.Format("%f",m_DataBegin);
	StrStopTime.Format("%f",m_DataEnding);
	CTime m_Startdate;
	m_CtlDateTimeStartTime.GetTime(m_Startdate);
	StartTime.Format("%d%02d%02d",m_Startdate.GetYear(), m_Startdate.GetMonth(),m_Startdate.GetDay());
	_RecordsetPtr m_pRecordsetch;
	m_pRecordsetch.CreateInstance(__uuidof(Recordset));
	books = app.get_Workbooks();
	book = books.Add(covOptional);
	sheets = book.get_Worksheets();
	sheets.Add(vtMissing,vtMissing,vtMissing,vtMissing);
	int nCount;
	char cCell;
	for(int i=1;i<5;i++)
	{
		tmpData.Format("%d",i);
		AntID = "天线"+tmpData; 
		sheet = sheets.get_Item(COleVariant((short)i)); //得到第一个工作表
		sheet.put_Name(AntID);
		for(int j=1;j<13;j++)
		{
			nCount = 3;
			tmpData.Format("%d",j);
			SensorID = "传感器"+tmpData;
			cCell = 'A' + 2*(j-1);
			rowCount.Format(_T("%c"),cCell);
			rowCount+="1";
			range = sheet.get_Range(COleVariant(rowCount),COleVariant(rowCount)); 
			range.put_Value2(COleVariant(SensorID));
			rowCount.Format(_T("%c"),cCell);
			rowCount+="2";
			range = sheet.get_Range(COleVariant(rowCount),COleVariant(rowCount)); 
			range.put_Value2(COleVariant("时间"));
			rowCount.Format(_T("%c"),cCell+1);
			rowCount+="2";
			range = sheet.get_Range(COleVariant(rowCount),COleVariant(rowCount)); 
			range.put_Value2(COleVariant("温度"));
			_bstr_t bstrSQLdata ="SELECT Temperature,RecordTime FROM DB_Data where ReaderID='"+strReader+"' and AntID='"+AntID+"' and SensorID='"+SensorID+"' and RecordTime<"+StrStopTime+" and RecordTime>"+StrStartTime+" and (Notes='正常' or Notes='超限') order by DataID;";
			m_pRecordsetch->Open(bstrSQLdata,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			while(!m_pRecordsetch->adoEOF)
			{
				CString temper=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("Temperature");
				CString time=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("RecordTime");
				COleDateTime t=atof(time);
				strRecordTime=t.Format("%Y-%m-%d %H:%M:%S");
				rowCount.Format(_T("%c"),cCell);
				strRow.Format(_T("%d"),nCount);
				rowCount+=strRow;
				range = sheet.get_Range(COleVariant(rowCount),COleVariant(rowCount));
				range.put_NumberFormat(COleVariant("hh:mm:ss"));
				range.put_Value2(COleVariant(strRecordTime));  //设置时间
				rowCount.Format(_T("%c"),cCell+1);
				rowCount+=strRow;
				range = sheet.get_Range(COleVariant(rowCount),COleVariant(rowCount));  
				range.put_Value2(COleVariant(temper));  //设置温度
				time.ReleaseBuffer();
				temper.ReleaseBuffer();
				m_pRecordsetch->MoveNext();
				nCount++;
			}
			m_pRecordsetch->Close();
		}
		range = sheet.get_Range(COleVariant("A3"),COleVariant("A3"));
		COleVariant vResult =range.get_Value2();
		if(vResult.vt==VT_EMPTY)
		{
			passWord="******";
		}
		else
		{
			SYSTEMTIME st;
			VariantTimeToSystemTime(vResult.date, &st);
			passWord.Format("%d%02d%02d",st.wYear,st.wMonth,st.wDay);
			passWord+="hshiot";
		}
		sheet.Protect(_variant_t(passWord),vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);
	}
	book.SaveCopyAs(COleVariant(cStrFile)); //保存到cStrFile文件
	book.put_Saved(true);
	books.Close();
	book.ReleaseDispatch();
	books.ReleaseDispatch(); 
	app.ReleaseDispatch();
	app.Quit();
	message = "已导出数据，文件位置 :"+cStrFile;
	AfxMessageBox(message);
	GetDlgItem(IDC_BUTTON_EXPORT)->EnableWindow(TRUE);
} 