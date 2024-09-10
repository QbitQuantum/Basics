HRESULT CEtsEodServerModule::PreMessageLoop(int nShowCmd)
{
	setlocale(LC_ALL, "English");

	EODCO::CEgTraceManagerPtr spTrace(new EODCO::CEgTraceManager);
	EODCO::CEgTraceManager::s_spTrace = spTrace;
	EODCO::CEgTraceManager::s_spTrace->Start();

	HRESULT hr = __super::PreMessageLoop(nShowCmd);
#if _ATL_VER == 0x0700
	if (SUCCEEDED (hr) && !m_bDelayShutdown)
		hr = CoResumeClassObjects(); 
#endif

	return hr;
}