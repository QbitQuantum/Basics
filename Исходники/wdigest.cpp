__kextdll bool __cdecl getWDigestFunctions(mod_pipe * monPipe, vector<wstring> * mesArguments)
{
	wostringstream monStream;
	monStream << L"** wdigest.dll/lsasrv.dll ** ; Research Status : " << (searchWDigestEntryList() ? L"OK :)" : L"KO :(") << endl << endl <<
		L"@l_LogSessList      = " << l_LogSessList << endl <<
		L"@LsaUnprotectMemory = " << SeckPkgFunctionTable->LsaUnprotectMemory << endl;
	return sendTo(monPipe, monStream.str());
}