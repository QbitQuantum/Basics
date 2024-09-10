void CColosseumCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	// TODO: Call PX_ functions for each persistent custom property.
	
	
	PX_String(pPX, _T("server"), m_server, _T("http://localhost:2222/Service1.svc"));
	//PX_Long(pPX, _T("File"), m_fileNumber);
	
	parseParameters(std::string((LPCSTR)m_server));

	///Create a temporary file using a unique timestamp
	TCHAR temp_path[MAX_PATH];
	///Get the temp path
	DWORD retValue = GetTempPath(MAX_PATH, temp_path);
	//If the returned number is greater than the number of MAX_PATH then stop execution
	if(retValue > MAX_PATH)
		ASSERT(1==0);
	std::stringstream ss;
	unsigned __int64 time_stamp;
	/* Initialize the file streams in the endpoint model vector*/
	for(size_t i = 0; i < m_endpointModelVector.size(); i++) {
		time_stamp = __rdtsc();
		ss << temp_path << "temp" << time_stamp + i << ".ifc";
		m_endpointModelVector[i]->setFileName(ss.str());
		m_endpointModelVector[i]->openFile(ss.str());
		ss.str("");
	}
	
}