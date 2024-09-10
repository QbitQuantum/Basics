CProcessTemplate* GetProcessTemplate()
#endif // hab270
{
	USES_CONVERSION;
	return new CProcessTemplate(
		RUNTIME_CLASS(CJoinCompProcess),
		A2CT(JOINCOMPDISPLAYNAME),
		CJoinCompProcess::INPUT_TYPE_DISPLAY(),
		CJoinCompProcess::OUTPUT_TYPE_DISPLAY(),
		A2CT(CJoinCompProcess::ID()),
		CProcess::kAnalysis,
		0);	// to do: figure out what the version number really should mean
}