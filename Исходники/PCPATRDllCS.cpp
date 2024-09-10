CProcessTemplate* GetProcessTemplate()
#endif // hab270
{
	USES_CONVERSION;
	return new CProcessTemplate(
		RUNTIME_CLASS(CPCPATRDllProcess),
		_T("PC-PATR DLL"),
		CPCPATRDllProcess::INPUT_TYPE_DISPLAY(),
		CPCPATRDllProcess::OUTPUT_TYPE_DISPLAY(),
		A2CT(CPCPATRDllProcess::ID()),
#ifndef hab245
		CProcess::kAnalysis | CProcess::kInterlinear | CProcess::kTransfer | CProcess::kSynthesis,
#else // hab245
		CProcess::kAnalysis,
#endif // hab245
		0);	// to do: figure out what the version number really should mean
}