// ****************************************************************************************************************
bool CWinProcess::terminateProcessFromModuleName(const std::string &moduleName, uint exitCode)
{
	return terminateProcess(getProcessIdFromModuleFilename(moduleName), exitCode);
}