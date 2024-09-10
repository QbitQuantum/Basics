void CScriptThread::DoExecute()
{
#ifdef _WIN32
	if ( _configthreadlocale(_ENABLE_PER_THREAD_LOCALE) == -1 )
		GenErr("_configthreadlocale failed.");
#endif

	SetAltSigStackEnabled(true);

	CBaseScriptApp::InitCfgTableTlsValue();
	CBaseScriptApp::InitStrIndexTlsValue();
	CBaseScriptApp::InitStr64IndexTlsValue();

#ifdef _WIN32
	_set_se_translator(TransESHFun);
#endif

	AddWatchCpuThreadID("ScriptThread",GetCurTID());
	HTHREADID id = GetCurTID();
	m_pScript->SetRunningThread(id);

#ifndef _WIN32
	SetLogCallBackFunc(CScriptThread::OnErrLogCallBack);
#endif

	RegistThreadCoreServer(*m_pScript);

	TLS_SetValue(m_pThreadMgr->m_tlsThreadKey, this);

	CPkgFile::InitTLSData();

	stringstream strm;

	strm<<"engine_require(\"server/thread/ThreadCoreServer\")\n"
		"ThreadCoreServer.Run(\""<<m_strRunFile.c_str()<<"\")";

	string sError = m_pScript->RunString(strm.str().c_str(),NULL);
	if (!sError.empty())
	{
		LogErr(sError.c_str());
	}

	CPkgFile::UnitTLSData();

	TLS_SetValue(m_pThreadMgr->m_tlsThreadKey, NULL);

	CBaseScriptApp::UnInitCfgTableTlsValue();
	CBaseScriptApp::UnInitStrIndexTlsValue();
	CBaseScriptApp::UnInitStr64IndexTlsValue();

#ifndef _WIN32	
	SetLogCallBackFunc(NULL);
#endif

	m_pScript->DetachRunningThread();

	SetAltSigStackEnabled(false);

}