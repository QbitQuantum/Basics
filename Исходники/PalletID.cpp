void CPalletID::NoRootFunction(void)
{
	bool res = true;
	CString cProduceName;
	CString cSerialNumber;
	CString cName;
	CString cID;
	CString cBoardNumber;
	CString cCustomer;
	//GetDlgItemText(IDC_EDIT_PRODUCTNAME_ID,cProduceName);
	GetDlgItemText(IDC_EDIT_SERIALNUMBER_ID,cSerialNumber);
	GetDlgItemText(IDC_EDIT_NAME_ID,cName);
	GetDlgItemText(IDC_EDIT_CARDID_ID,cID);
	GetDlgItemText(IDC_EDIT_BOARDNUMBER_ID,cBoardNumber);
	//卡板数量
	int iBoardNumber = _ttoi(cBoardNumber);
	if (cSerialNumber.GetLength() <=0 ||
		cName.GetLength() <=0 || cID.GetLength() <=0 || cBoardNumber.GetLength() <= 0 || iBoardNumber == 0)
	{
		AfxMessageBox(L"请输入产品名称/序列号/姓名/工号/卡板数量");
		return;
	}

	int nIndex = m_DataBasePalletID.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个数据库");
		return;
	}
	m_DataBasePalletID.GetLBText(nIndex,cProduceName);

	nIndex = m_customerPalletID.GetCurSel();
	if (nIndex < 0)
	{
		AfxMessageBox(L"你需要选择一个客户");
		return;
	}
	m_customerPalletID.GetLBText(nIndex,cCustomer);

	if (m_dbDemo.IsConnecting())
	{
		m_dbDemo.CloseConnection();
	}

#if 1
	bool isFindSerial = false;
	CString *pStr;
	int iSubStrs=0;
	pStr = SplitString(cSerialNumber,';',iSubStrs);
	if (!pStr)
	{
		AfxMessageBox(L"你的序列号不正确，请检查");
		PalletIDStatus = 2;
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
		GetDlgItem(IDC_EDIT_SERIALNUMBER_ID)->SetWindowText(cSerialNumber);
	}
	else
	{
		AfxMessageBox(L"你的序列号不正确，请检查");
		PalletIDStatus = 2;
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

	//1.连接数据库,DemoTable是数据库的名称
	res = m_dbDemo.OpenRecordset("SELECT * FROM DemoTable");
	if (!res)
	{
		AfxMessageBox(m_dbDemo.m_strErrorMsg);
		return;
	}

	cSerialNumber = cCustomer + L"-" + cSerialNumber;
	m_dbDemo.MoveToFirst();
	//1:首先获取要打印的序列号的最小root值
	vector<CString>dataBaseAll;
	CString csError;
	CString strData;
	CString cstemprootMinum;
	CString cstemprootMinumNumber;
	bool isExit = false;
	int tempRootMinum = 0;
	int tempRootMinumNumber = 0;
	int maxvalue = 999999;
	isExit = false;
	m_dbDemo.MoveToFirst();
	for (int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
		dataBaseAll.push_back(strData);
		if (cSerialNumber == strData)
		{
			m_dbDemo.GetFieldValue(_T("PalletID界面-Time"), strData);
			if(strData == L"NULL")
			{
				m_dbDemo.GetFieldValue(_T("RootTimes"), strData);
				tempRootMinum = _ttoi(strData);
				if (tempRootMinum < maxvalue)
				{
					cstemprootMinum = strData;
					maxvalue = tempRootMinum;
					m_dbDemo.GetFieldValue(_T("个数"), strData);
					cstemprootMinumNumber = strData;
				}
			}
			else
			{
				csError.Format(L"%s该序列号已经做过了",cSerialNumber);
				AfxMessageBox(csError);
				PalletIDStatus = 2;
				Invalidate(TRUE);
				return;
			}
			isExit = true;
		}
		m_dbDemo.MoveToNext();
	}
	if (!isExit)
	{
		csError.Format(L"%s该序列号不存在",cSerialNumber);
		AfxMessageBox(csError);
		PalletIDStatus = 2;
		Invalidate(TRUE);
		return;
	}

	
	//3:首先获取数据中所有的序列号
	int maxValue = -9999;
	int iRealBoardNum = -1;  //实际的卡板编号
	int maxCount = 0;
	CString csRealBoardNum;
	m_dbDemo.MoveToFirst();
	//vector<CString>digital;
	CString boardNumber;
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		m_dbDemo.GetFieldValue(_T("卡板编号"), boardNumber);
		//digital.push_back(boardNumber);
		if (_ttoi(boardNumber) > maxValue)
		{
			maxValue = _ttoi(boardNumber);
			maxCount = 1;
		}
		else if(maxValue == _ttoi(boardNumber))
		{
			maxCount += 1;
		}
		m_dbDemo.MoveToNext();
	}


	int iPrinterNumber;
	bool isNeddPrint = false;
	if (iBoardNumber == 1)
	{
		if (maxValue == -1)
		{
			maxValue = 1;
		}
		else
		{
			maxValue += 1;
		}
		iRealBoardNum = maxValue;
		PrintBarCode(iRealBoardNum,csRealBoardNum,false);
		isNeddPrint = true;

		iPrinterNumber = iRealBoardNum;
	}
	else
	{
		if (maxValue == -1)
		{
			iRealBoardNum = 1;
		}
		else if ((maxValue != -1) && maxCount < (iBoardNumber-1))
		{
			iRealBoardNum = maxValue;
		}
		else if((maxValue != -1) && maxCount == (iBoardNumber-1))
		{
			iRealBoardNum = maxValue;
			isNeddPrint = true;
			iPrinterNumber = iRealBoardNum;
		}
		else
		{
			iRealBoardNum = maxValue + 1;
		}
		PrintBarCode(iRealBoardNum,csRealBoardNum,false);
	}
	GetDlgItem(IDC_EDIT_BOARDNUMBER_ID_TWO)->SetWindowText(csRealBoardNum);

	//4:匹配数据库
	bool isOK = false;
	CString matchingStr;
	for (int i=0; i<dataBaseAll.size(); i++)
	{
		if (dataBaseAll.at(i) == cSerialNumber)
		{
			matchingStr = dataBaseAll.at(i);
			isOK = TRUE;
			break;
		}
	}
	if(!isOK)
	{
		PalletIDStatus = 2;
		AfxMessageBox(L"数据库没有这个编号，请注意查询");
		Invalidate(TRUE);
		return;
	}

	//2:判断前面的工站是否有测试过
	CString lastItem;
	res = m_dbDemo.CheckStation(itemName,L"PalletID",lastItem);
	if(!res)
	{
		AfxMessageBox(L"没有激活的测试项目，请返回检查");
		PalletIDStatus = 2;
		Invalidate(TRUE);
		return;
	}
	

	m_dbDemo.MoveToFirst();
	bool isFind = false;
	for(int i=0; i<m_dbDemo.GetRecordCount(); i++)
	{
		CString	strData;
		m_dbDemo.GetFieldValue(_T("个数"), strData);
		if (strData == cstemprootMinumNumber)
		{
			m_dbDemo.GetFieldValue(_T("SerialNum"), strData);
			if (strData ==cSerialNumber)
			{
				CString	strTemp;
				m_dbDemo.GetFieldValue(lastItem, strTemp);
				if(_tcsstr(strTemp,L"OK"))
				{
					//m_dbDemo.GetFieldValue(_T("个数"), strData);
					//if (strData == cstemprootMinumNumber)
					{										//打印模板
						if (isNeddPrint)
						{
							CString temp;
							if(!PrintBarCode(iPrinterNumber,temp,true))
							{
								PalletIDStatus = 2;
								Invalidate(TRUE);
								return;
							}
						}
						CString time;
						GetMyCurrentTime(time);
						CString csTotal;
						csTotal = time + L"_" + cName +  L"_"+ cID;
						CString	strSQL;
						strSQL.Format(_T("UPDATE DemoTable SET [PalletID界面-Time] = '%s' WHERE [个数] = '%s'"),csTotal,cstemprootMinumNumber);
						if(m_dbDemo.Execute(strSQL))
						{
							strSQL.Format(_T("UPDATE DemoTable SET [PalletID界面] = 'OK_%s' WHERE [个数] = '%s'"),cBoardNumber,cstemprootMinumNumber);
							if(m_dbDemo.Execute(strSQL))
							{
								strSQL.Format(_T("UPDATE DemoTable SET [卡板编号] = '%d' WHERE [个数] = '%s'"),iRealBoardNum,cstemprootMinumNumber);
								if(m_dbDemo.Execute(strSQL))
								{
									strSQL.Format(_T("UPDATE DemoTable SET [卡板序号] = '%s' WHERE [个数] = '%s'"),csRealBoardNum,cstemprootMinumNumber);
									if(m_dbDemo.Execute(strSQL))
									{
										PalletIDStatus = 1;
										Invalidate(TRUE);
										isFind = true;

										m_resultList.InsertItem(GlobalTotalCount,matchingStr);
										m_resultList.SetItemText(GlobalTotalCount,1, csRealBoardNum);
										GlobalTotalCount++;
									}
								}
								else
								{
									PalletIDStatus = 2;
									Invalidate(TRUE);
									AfxMessageBox(m_dbDemo.GetLastError());
									return;
								}

							}
							else
							{
								PalletIDStatus = 2;
								Invalidate(TRUE);
								AfxMessageBox(m_dbDemo.GetLastError());
								return;
							}
						}
						else
						{
							PalletIDStatus = 2;
							Invalidate(TRUE);
							AfxMessageBox(m_dbDemo.GetLastError());
							return;
						}
						break;
					}
				}
				else if(strTemp == L"NULL")
				{
					PalletIDStatus = 2;
					CString error;
					error.Format(L"你的上一站%s没有测试",lastItem);
					AfxMessageBox(error);
					Invalidate(TRUE);
					return;
				}
				else if(strTemp == L"NG")
				{
					PalletIDStatus = 2;
					CString error;
					error.Format(L"OQC设置该DUT为NG",lastItem);
					AfxMessageBox(error);
					Invalidate(TRUE);
					return;
				}
			}
		}
		m_dbDemo.MoveToNext();
	}

	if (!isFind)
	{
		PalletIDStatus = 2;
		AfxMessageBox(L"序列号或者产品不正确");
		Invalidate(TRUE);
	}
}