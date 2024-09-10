HRESULT CHveDbController::SaveDBElement(RESULT_ELEMENT* pElement)
{
	HRESULT hr = S_OK;
	if(!m_fIsConnecting)
	{
		SaveLog("数据库连接已经断开，尝试重新连接...");
		hr = ConnectDB();
	}

	if(!m_fIsConnecting)
	{
		char szOutPutInfo[100];
		sprintf(szOutPutInfo, "连接数据库失败，保存%s结果失败...错误码:%d", pElement->szPlateNo, GetLastError());
		SaveLog(szOutPutInfo);
		OutPutMessage(szOutPutInfo);
		return E_FAIL;
	}
	_variant_t RecordsAffected;

	CTime cTime(pElement->dw64TimeMs / 1000);
	CString strTime = cTime.Format("%Y-%m-%d %H:%M:%S");
	CString strCurTable = cTime.Format("Hve_Data_%Y%m%d");

	//int iMinute = cTime.GetMinute(); 
	//CString strTmp = cTime.Format("Hve_Data_%Y%m%d%H");
	//strCurTable.Format("%s_%d",strTmp.GetBuffer(), iMinute/10); // 10分钟一张表
	//strTmp.ReleaseBuffer();

	if(m_strLastTable != strCurTable)
	{
		char szCmdText[1024] = {0};

		//try
		//{
		//	sprintf(szCmdText, "Create TABLE %s(Record_Id bigint primary key IDENTITY   (1,   1)   NOT   NULL,\
		//					   Location_Id int NOT NULL,Pass_Time datetime NOT NULL, Plate_No char(20), Road_No int,\
		//					   Car_Speed int, Obj_Id int, Time_Headway int, Over_Line int, Cross_Line int,\
		//					   Emergency_Stop int, Reverse_Run bit, Special_Result bit, big_image_1_path char(256),\
		//					   big_image_2_path char(256), big_image_3_path char(256), big_image_4_path char(256),\
		//					   big_image_5_path char(256), small_image_path char(256), bin_image_path char(256),\
		//					   video_path char(256))", strCurTable.GetBuffer());
		//	m_pConnection->Execute((_bstr_t)szCmdText, &RecordsAffected, adCmdText);
		//	sprintf(szCmdText, "CREATE INDEX [Pass_Time] ON [dbo].[%s] ([Pass_Time])", strCurTable.GetBuffer());
		//	m_pConnection->Execute((_bstr_t)szCmdText, &RecordsAffected, adCmdText);
		//	sprintf(szCmdText, "CREATE INDEX [Obj_Id] ON [dbo].[%s] ([Obj_Id])", strCurTable.GetBuffer());
		//	m_pConnection->Execute((_bstr_t)szCmdText, &RecordsAffected, adCmdText);
		//	sprintf(szCmdText, "CREATE INDEX [Special_Result] ON [dbo].[%s] ([Special_Result])", strCurTable.GetBuffer());
		//	m_pConnection->Execute((_bstr_t)szCmdText, &RecordsAffected, adCmdText);
		//}

		//表存在则不创建
		try
		{
			sprintf(szCmdText, "if not exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[%s]') and OBJECTPROPERTY(id, N'IsUserTable') = 1) \
							   Create TABLE %s(Record_Id bigint primary key IDENTITY   (1,   1)   NOT   NULL,\
							   Location_Id int NOT NULL,Pass_Time datetime NOT NULL, Plate_No char(20), Road_No int, Road_Name char(25),Road_Direct char(10),\
							   Car_Speed int, Obj_Id int, Time_Headway int, Over_Line int, Cross_Line int,\
							   Emergency_Stop int, Reverse_Run bit, Speeding bit, Special_Result bit, big_image_1_path varchar(256),\
							   big_image_2_path varchar(256), big_image_3_path varchar(256), big_image_4_path varchar(256),\
							   big_image_5_path varchar(256), small_image_path varchar(256), bin_image_path varchar(256),\
							   video_path varchar(256))",strCurTable.GetBuffer(),strCurTable.GetBuffer());
			m_pConnection->Execute((_bstr_t)szCmdText, &RecordsAffected, adCmdText);
			sprintf(szCmdText, "if not exists (select * from sysindexes where name='Pass_Time')  CREATE INDEX [Pass_Time] ON [dbo].[%s] ([Pass_Time])", strCurTable.GetBuffer());
			m_pConnection->Execute((_bstr_t)szCmdText, &RecordsAffected, adCmdText);
			sprintf(szCmdText, "if not exists (select * from sysindexes where name='Obj_Id') CREATE INDEX [Obj_Id] ON [dbo].[%s] ([Obj_Id])", strCurTable.GetBuffer());
			m_pConnection->Execute((_bstr_t)szCmdText, &RecordsAffected, adCmdText);
			sprintf(szCmdText, "if not exists (select * from sysindexes where name='Special_Result') CREATE INDEX [Special_Result] ON [dbo].[%s] ([Special_Result])", strCurTable.GetBuffer());
			m_pConnection->Execute((_bstr_t)szCmdText, &RecordsAffected, adCmdText);
		}
		catch (_com_error e)
		{
			m_fIsConnecting = FALSE;
			CString strErrorMessage;
			strErrorMessage.Format("创建表失败!错误信息:%s  错误码:%d", e.ErrorMessage(), GetLastError());
			SaveLog(strErrorMessage.GetBuffer());
			SaveLog(e.Description());
			OutPutMessage("创建数据表失败!");
		}

		///////视图创建 由查询软件创建
		//try
		//{
		//	char szCmdText[1024] = {0};
		//	sprintf(szCmdText, "IF EXISTS (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.VIEWS WHERE TABLE_NAME = N'Hve_Data_View') DROP VIEW Hve_Data_View");
		//	m_pConnection->Execute((_bstr_t)szCmdText, &RecordsAffected, adCmdText);

		//}
		//catch (_com_error e)
		//{
		//	CString strErrorMessage;
		//	strErrorMessage.Format("删除视图失败! 错误信息:%s 错误码:%d", e.ErrorMessage(), GetLastError());
		//	SaveLog(strErrorMessage.GetBuffer());
		//	SaveLog(e.Description());
		//	OutPutMessage("删除视图失败...");
		//}
		
		//bool fIsCreateViewFault = true;
		//int iRetry = 0;
		//while(fIsCreateViewFault)
		//{
		//	if(iRetry++ == 5)
		//	{
		//		exit(1);  //reboot
		//	}

		//	try
		//	{
		//		_RecordsetPtr pPtr;
		//		CString strName;
		//		if(FAILED(pPtr.CreateInstance("ADODB.Recordset")))
		//		{
		//			OutPutMessage("创建ADO数据集失败...");
		//			return E_FAIL;
		//		}

		//		CString strConnectInfo;
		//		strConnectInfo.Format("Driver=SQL Server;Server=%s;DATABASE=%s;UID=%s;PWD=%s",
		//			m_strServerIP, m_strDataBase, m_strUserName, m_strPassword);
		//		CString strCommand = "SELECT name FROM sysobjects WHERE (name LIKE 'Hve_Data_%')";;
		//		if(FAILED(pPtr->Open(_variant_t(strCommand), _variant_t(strConnectInfo), adOpenStatic, adLockOptimistic, adCmdText)))
		//		{
		//			OutPutMessage("获取数据表名字失败...");
		//			pPtr.Release();
		//			return E_FAIL;
		//		}
		//		while(!pPtr->GetadoEOF())
		//		{
		//			CString strTmp = (char*)_bstr_t(pPtr->GetCollect("name"));
		//			strTmp.TrimRight();
		//			if(strName == "")
		//			{
		//				strName.Format("(SELECT * FROM %s)", strTmp);
		//			}
		//			else
		//			{
		//				strName.AppendFormat("union (SELECT * FROM %s)", strTmp);
		//			}
		//			pPtr->MoveNext();
		//		}
		//		pPtr->Close();
		//		pPtr.Release();

		//		char szCmdText[1024] = {0};
		//		sprintf(szCmdText,  "CREATE VIEW Hve_Data_View AS %s", strName);
		//		m_pConnection->Execute((_bstr_t)szCmdText, &RecordsAffected, adCmdText);
		//		fIsCreateViewFault = false;
		//	}
		//	catch (_com_error e)
		//	{
		//		fIsCreateViewFault = true;
		//		CString strErrorMessage;
		//		strErrorMessage.Format("创建视图失败... 错误码:%d", GetLastError());
		//		SaveLog(strErrorMessage.GetBuffer());
		//		SaveLog(e.Description());
		//		OutPutMessage("创建视图失败...");
		//	}
		//}
	
	}