void CConfigFileHandler::WriteToCfgFile(
	const CString& HexFileName,
	const CString& FlashMethod,
	const CString& DeviceID,
	const CString& COMPORT,
	const CString& Baudrate,
	const CString& IP,
	const CString& IPPort,
	const CString& subnot,
	const CString& subID)
{
//	m_szCfgFile[CV_Installdir] = (CString(c_strCfgDefaultInstalldirItem) + g_strExePath);	
//
//	// hex file path
//	CString strHexFilePath = HexFileName;
//	m_szCfgFile[CV_TstatLastFlashFile] = ( CString(c_strCfgLastFlashFileItem) + strHexFilePath);	
//	// method
//	m_szCfgFile[CV_TstatLastFlashMethod] =(CString(c_strCfgLastFlashMethodItem) + FlashMethod );		
//	// flash page
////	m_szCfgFile[CV_TstatLastFlashPage] =(CString(c_strCfgLastFlashTypePageItem) + strFlashTypePage);			
//	// id
//	m_szCfgFile[CV_TstatDeAddr] =(CString(c_strCfgDefaultAddrItem) + DeviceID );	
//	// com port
//	m_szCfgFile[CV_TstatDeCOM] =(CString(c_strCfgDefaultComItem) + COMPORT);	
//	// Baudrate
//	m_szCfgFile[CV_TstatDeBaudrate] =(CString(c_strCfgDefaultBaudrateItem) + Baudrate);
//	m_szCfgFile[CV_NCDeIP] =(CString(c_strCfgDefaultIPItem) + IP);
//	m_szCfgFile[CV_NCDeIPPort] =(CString(c_strCfgDefaultIPPortItem) + IPPort);
//
//	m_szCfgFile[CV_SubNot] =(CString(c_strCfgNote) +CString(subnot));
//	m_szCfgFile[CV_Sub_ID] =(CString(c_strCfgSubID) +CString(subID));

	//WriteToCfgFile();
	
	WritePrivateProfileStringW(m_ISPTool_Section,CString(c_strCfgLastFlashFileItem),HexFileName,m_configfile_path);
	WritePrivateProfileStringW(m_ISPTool_Section,CString(c_strCfgLastFlashMethodItem),FlashMethod,m_configfile_path);
	WritePrivateProfileStringW(m_ISPTool_Section,CString(c_strCfgDefaultAddrItem),DeviceID,m_configfile_path);
	WritePrivateProfileStringW(m_ISPTool_Section,CString(c_strCfgDefaultComItem),COMPORT,m_configfile_path);
	WritePrivateProfileStringW(m_ISPTool_Section,CString(c_strCfgDefaultIPItem),IP,m_configfile_path);
	WritePrivateProfileStringW(m_ISPTool_Section,CString(c_strCfgDefaultIPPortItem),IPPort,m_configfile_path);
	WritePrivateProfileStringW(m_ISPTool_Section,CString(c_strCfgDefaultBaudrateItem),Baudrate,m_configfile_path);
	WritePrivateProfileStringW(m_ISPTool_Section,CString(c_strCfgNote),subnot,m_configfile_path);
	WritePrivateProfileStringW(m_ISPTool_Section,CString(c_strCfgSubID),subID,m_configfile_path);
}