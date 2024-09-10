ULONG_PTR __fastcall HostAddRef( )
{
	LPUNKNOWN pUnknown;

	if (SHGetInstanceExplorer(&pUnknown) == S_OK)
		return((ULONG_PTR)pUnknown);
	else
		return(0);
}