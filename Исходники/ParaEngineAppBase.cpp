void ParaEngine::CParaEngineAppBase::VerifyCommandLine(const char* sCommandLine, std::string &strCmd)
{
	if (sCommandLine)
		strCmd = sCommandLine;
	if (strCmd.find("bootstrapper") == string::npos)
	{
		// if no bootstrapper is specified, try to find the config.txt in current directory. 
		CParaFile configFile;
		if (configFile.OpenFile("config.txt"))
		{
			std::string sCmdLine;
			configFile.GetNextAttribute("cmdline", sCmdLine);
			configFile.close();
			if (sCmdLine.find("bootstrapper") != string::npos)
			{
				strCmd = strCmd + " " + sCmdLine;
			}
		}
		else
		{
			// just in case, user has specified XXX.lua instead of bootstrapper=XXX.lua in the command line. 
			auto nPos = strCmd.find(".lua");
			if (nPos != string::npos)
			{
				auto nFilenameFromPos = strCmd.rfind(" ", nPos);
				if (nPos != string::npos)
				{
					strCmd = strCmd.substr(0, nFilenameFromPos + 1) + std::string("bootstrapper=") +
						strCmd.substr(nFilenameFromPos + 1, nPos - nFilenameFromPos + 3) + strCmd.substr(nPos + 4);
				}
			}
		}
	}
}