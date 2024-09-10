CMultipleResult::~CMultipleResult()
{
	ATLTRACE2(atlTraceDBProvider, 2, _T("CMultipleResult::~CMultipleResult()\n"));
	this->GetSessionPtr()->AutoCommit(NULL);
	if(m_spUnkSite)
		GetSessionPtr()->RegisterTxnCallback(this, false);
}