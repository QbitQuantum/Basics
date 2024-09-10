void	AppPath(string& outString)
{
	ProcessSerialNumber	psn = { 0, kCurrentProcess };
	ProcessInfoRec info = { 0 };
	FSSpec	spec;
	Str255	name;
	info.processInfoLength = sizeof(info);
	info.processAppSpec = &spec;
	info.processName = name;
	GetProcessInformation(&psn, &info);
	FSSpec_2_String(spec, outString);
}