HRESULT CUnknownImpl::QueryInterfaceImpl(REFIID riid, void ** ppvObject)
{
	static const QITAB qitab[] = { {0} };
	const QITAB* pqitab = getQITAB();
	return QISearch(this, pqitab ? pqitab : qitab, riid, ppvObject);
}