void CPCBA::NoRootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cCustomer;
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_PCBA,cSerialNumber);
	GetDlgItemText(IDC_EDIT_CARDID_PCBA,cID);
	if (cSerialNumber.GetLength() <0 || cID.GetLength() <=0)
	{
		AfxMessageBox(L"请输入正确的序列号/姓名/工号");
		return;
	}

	int nIndex = m_dataBaseName.GetCurSel();
	if(nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个产品名称");
		return;
	}
	m_dataBaseName.GetLBText(nIndex,cProduceName);

	nIndex = m_customer.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个客户");
		return;
	}
	m_customer.GetLBText(nIndex,cCustomer);

	string sID;
	sID = CStringA(cID);
	COperateINIFile operateFile;
	res = operateFile.CheckName("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\姓名库\\PCBAName.dat",sID,cName);
	if (!res)
	{
		AfxMessageBox(L"你没有权限");
		return;
	}
	GetDlgItem(IDC_EDIT_NAME_PCBA)->SetWindowText(cName);


#if 1
	//分离序列号
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"你的序列号不正确，请检查");
		PCBAIDStatus = 2;
		Invalidate(TRUE);
		return;
	}
	CString tempStr;
	for (int i=0; i<iSubStrs; i++)
	{
		CString temp = pStr[i];
		temp.MakeUpper();
		if (_tcsstr(temp,L"SERIAL") || _tcsstr(temp,L"S/N"))
		{
			tempStr = pStr[i];
			isFindSerial = true;
			break;
		}
	}
#else
	bool isFindSerial = false; 
	isFindSerial = true;
#endif

	if (isFindSerial)
	{
		cSerialNumber = cSerialNumber.Mid(cSerialNumber.GetLength()-6,cSerialNumber.GetLength());
		GetDlgItem(IDC_EDIT_SERIALNUMBER_PCBA)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"你的序列号不正确，请检查");
		PCBAIDStatus = 2;
		Invalidate(TRUE);
		return;
	}

	if (m_dbDemo.IsConnecting())
	{
		m_dbDemo.CloseConnection();
	}

	//打开数据库
	res = OpenDataBase(cProduceName);
	if (!res)
	{
		AfxMessageBox(L"打开数据库失败");
		return;
	}

	//bool res = false;
	CString str;
	//COperateINIFile operateFile;
	res = operateFile.CheckDataisBusy("\\\\172.20.0.8\\1.公司会议资料\\博杰生产管理软件\\Debug\\busy.txt",6,str);
	if (!res)
	{
		AfxMessageBox(str);
		return;
	}

	//1.连接数据库,DemoTable是数据库的名称
	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		PCBAIDStatus = 2;
		Invalidate(TRUE);
		return;
	}
	cSerialNumber = cCustomer + L"-" + cSerialNumber;

	//1:首先获取要打印的序列号的最小root值
	CString strError;
	CString strData;
	CString cstemprootMinum;
	CString cstemprootMinumNumber;
	bool isExit = false;
	{
		int tempRootMinum = 0;
		int tempRootMinumNumber = 0;
		m_dbDemo.MoveToFirst();
		for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
			if (cSerialNumber == strData)
			{
				m_dbDemo.GetFieldValue(_T("RootTimes"), strData);
				if(strData == L"0")
				{
					m_dbDemo.GetFieldValue(_T("PCBA界面"), strData);
					if (strData != L"NULL")
					{
						strError.Format(L"%s该序列号已经做过了",cSerialNumber);
						AfxMessageBox(strError);
						PCBAIDStatus = 2;
						Invalidate(TRUE);
						return;
					}
					else
					{
						m_dbDemo.GetFieldValue(_T("个数"), cstemprootMinumNumber);
						isExit = true;
						break;
					}
				}
			}
			m_dbDemo.MoveToNext();
		}
		if (!isExit || cstemprootMinumNumber.GetLength() <= 0)
		{
			CString temp;
			temp.Format(L"%s该序列号不存在 ",cSerialNumber);
			AfxMessageBox(temp);
			PCBAIDStatus = 2;
			Invalidate(TRUE);
			return;
		}
	}

	m_dbDemo.MoveToFirst();
	CString csTotalKeyInformation;//总的关键物料信息
	CString tempTextData;
	for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		if (strData == cSerialNumber)
		{
			m_dbDemo.GetFieldValue(_T("个数"), strData);
			if (strData == cstemprootMinumNumber)
			{
				CString time;
				GetMyCurrentTime(time);
				CString csTotal;
				csTotal = time + L"_" + cName +  L"_"+ cID;
				CString	strSQL;
				strSQL.Format(_T("UPDATE DemoTable SET [PCBA界面-Time] = '%s' WHERE [个数] = '%s'"),csTotal,cstemprootMinumNumber);
				if(m_dbDemo.Execute(strSQL))
				{
					strSQL.Format(_T("UPDATE DemoTable SET [PCBA界面] = 'OK' WHERE [个数] = '%s'"),cstemprootMinumNumber);
					if(m_dbDemo.Execute(strSQL))
					{
						/***********************************************************/
						GetDlgItemText(IDC_EDIT_PCBA_ONE,tempTextData);
						csTotalKeyInformation = tempTextData + L"-";
						GetDlgItemText(IDC_NUM_PCBA_ONE,tempTextData);
						csTotalKeyInformation += tempTextData;
						strSQL.Format(_T("UPDATE DemoTable SET [PCBA1] = '%s' WHERE [个数] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);

						/***********************************************************/
						GetDlgItemText(IDC_EDIT_PCBA_TWO,tempTextData);
						csTotalKeyInformation = tempTextData + L"-";
						GetDlgItemText(IDC_NUM_PCBA_TWO,tempTextData);
						csTotalKeyInformation += tempTextData;
						strSQL.Format(_T("UPDATE DemoTable SET [PCBA2] = '%s' WHERE [个数] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);

						/***********************************************************/
						GetDlgItemText(IDC_EDIT_PCBA_THREE,tempTextData);
						csTotalKeyInformation = tempTextData + L"-";
						GetDlgItemText(IDC_NUM_PCBA_THREE,tempTextData);
						csTotalKeyInformation += tempTextData;
						strSQL.Format(_T("UPDATE DemoTable SET [PCBA3] = '%s' WHERE [个数] = '%s'"),csTotalKeyInformation,cstemprootMinumNumber);
						m_dbDemo.Execute(strSQL);

						break;
					}
					else
					{
						AfxMessageBox(m_dbDemo.GetLastError());
						PCBAIDStatus = 2;
						Invalidate(TRUE);
						return ;
					}
				}
			}
		}
		m_dbDemo.MoveToNext();
	}
	PCBAIDStatus = 1;
	Invalidate(TRUE);
}