// IUnknown
IFACEMETHODIMP CExplorerCommandImpl::QueryInterface(REFIID riid, void ** ppv)
{
	static const QITAB qit[] =
	{
		QITABENT(CExplorerCommandImpl, IExplorerCommand),
		{0},
	};
	return QISearch(this, qit, riid, ppv);
}