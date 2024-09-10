scrThread * ScriptEngine::GetActiveThread()
{
	char *moduleTls = *(char**)__readgsqword(88);
	return *reinterpret_cast<scrThread**>(moduleTls + activeThreadTlsOffset);
}