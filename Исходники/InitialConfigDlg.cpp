void CInitialConfigDlg::OnBnClickedButtonOK()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	const CString notFound=_T("");
	const CString sectionNode=_T("NodeInfo");
	const CString sectionTrack=_T("TrackInfo");
	const CString sectionProtocol=_T("Protocol");
	const CString sectionTimeSeq=_T("TimeSeqence");
	const CString sectionLink=_T("Link");
	const CString sectionBaseband=_T("Baseband");
	CFileFind finder;
	
	m_EditNodeIDStr.Trim();
	CString configPath=_T(".\\config[")+m_EditNodeIDStr+_T("].ini");//获取文件名
	if(!finder.FindFile(configPath))
	{
		CFile fileConfig;
		try
		{
			fileConfig.Open(configPath,CFile::modeCreate|CFile::modeWrite);//如没有文件则新建一个
			fileConfig.Close();
		}
		catch(CFileException *e)
		{
			CString errStr;
			errStr.Format(_T("文件创建失败:%d"),e->m_cause);
			MessageBox(errStr);
			fileConfig.Abort();
			e->Delete();
		}
	}
	CString valueStr;
	
	//NodeInfo
	//NodeType
	::WritePrivateProfileString(sectionNode,_T("NodeType"),m_ComboNodeTypeStr,configPath);
	//NodeID
	::WritePrivateProfileString(sectionNode,_T("NodeID"),m_EditNodeIDStr,configPath);
	//IntfMac
	CString intfMAC;
	intfMAC.Format(_T("%d"),0x000000000001+_ttoi(m_EditNodeIDStr));
	::WritePrivateProfileString(sectionNode,_T("IntfMac"),intfMAC,configPath);

	//TrackInfo
	float Longt,Lat,Ht;
	CString PositionStr;
	//InitialPosition
	Longt=_ttof(m_EditInitPos_LongtStr);
	Lat=_ttof(m_EditInitPos_LatStr);
	Ht=_ttof(m_EditInitPos_HtStr);
	PositionStr.Format(_T("(%.2f,%.2f,%.2f)"),Longt,Lat,Ht);
	::WritePrivateProfileString(sectionTrack,_T("InitialPositon"),PositionStr,configPath);
	//DestinatePosition
	Longt=_ttof(m_EditDstPos_LongtStr);
	Lat=_ttof(m_EditDstPos_LatStr);
	Ht=_ttof(m_EditDstPos_HtStr);
	PositionStr.Format(_T("(%.2f,%.2f,%.2f)"),Longt,Lat,Ht);
	::WritePrivateProfileString(sectionTrack,_T("DestinatePositon"),PositionStr,configPath);
	//TrackType
	::WritePrivateProfileString(sectionTrack,_T("TrackType"),m_ComboTrackTypeStr,configPath);
	//VelocityRange
	float Vinf=_ttof(m_EditVinfStr);
	float Vsup=_ttof(m_EditVsupStr);
	CString VStr;
	VStr.Format(_T("(%.2f,%.2f"),Vinf,Vsup);
	::WritePrivateProfileString(sectionTrack,_T("Velocity"),VStr,configPath);
	//RuleOfVelocityChange
	::WritePrivateProfileString(sectionTrack,_T("VRule"),m_ComboVRuleStr,configPath);
		
	//ProtocolInfo
	//MessageFormat
	::WritePrivateProfileString(sectionProtocol,_T("MessageFormat"),m_ComboMsgFormatStr,configPath);
	::WritePrivateProfileString(sectionProtocol,_T("isRelayTransmission"),m_ComboRelayTranStr,configPath);
	//ScheduleAlgorithm
	::WritePrivateProfileString(sectionProtocol,_T("ScheduleAlgorithm"),m_ComboScheAlgoStr,configPath);
	//NetworkManage
	::WritePrivateProfileString(sectionProtocol,_T("NetworkManage"),m_ComboNetworkManageStr,configPath);
	//isErrorControl
	::WritePrivateProfileString(sectionProtocol,_T("isErrorControl"),m_ComboErrCtrlStr,configPath);

	//TimeSequenceInfo
	//TimeSlot
	::WritePrivateProfileString(sectionTimeSeq,_T("TimeSlot"),m_ComboTimeSlotStr,configPath);
	//numSlots
	::WritePrivateProfileString(sectionTimeSeq,_T("numSlots"),m_ComboNumSlotStr,configPath);
	//numNetworks
	::WritePrivateProfileString(sectionTimeSeq,_T("numNetworks"),m_ComboNumNetworkStr,configPath);
	//SlotsDistribution
	::WritePrivateProfileString(sectionTimeSeq,_T("SlotsDistribution"),m_ComboSlotDistStr,configPath);
	//SubSlotValue
	::WritePrivateProfileString(sectionTimeSeq,_T("SubSlotValue"),m_ComboSlotValueStr,configPath);

	//LinkInfo
	//LinkType
	::WritePrivateProfileString(sectionLink,_T("LinkType"),m_ComboLinkTypeStr,configPath);
	//ServiceSource
	::WritePrivateProfileString(sectionLink,_T("ServiceSource"),m_ComboServiceSrcStr,configPath);

	numNodes=_ttoi(m_EditNodeIDStr);
	m_EditNodeIDStr.Format(_T("%d"),++numNodes);
	_CEditSetText(IDC_EDIT_Config_Node_ID,m_EditNodeIDStr);
}