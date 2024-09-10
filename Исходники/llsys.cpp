LLCPUInfo::LLCPUInfo()
{
	std::ostringstream out;
	CProcessor proc;
	const ProcessorInfo* info = proc.GetCPUInfo();
	// proc.WriteInfoTextFile("procInfo.txt");
	mHasSSE = info->_Ext.SSE_StreamingSIMD_Extensions;
	mHasSSE2 = info->_Ext.SSE2_StreamingSIMD2_Extensions;
	mHasAltivec = info->_Ext.Altivec_Extensions;
	mCPUMhz = (S32)(proc.GetCPUFrequency(50)/1000000.0);
	mFamily.assign( info->strFamily );
	mCPUString = "Unknown";

#if LL_WINDOWS || LL_DARWIN || LL_SOLARIS
	out << proc.strCPUName;
	if (200 < mCPUMhz && mCPUMhz < 10000)           // *NOTE: cpu speed is often way wrong, do a sanity check
	{
		out << " (" << mCPUMhz << " MHz)";
	}
	mCPUString = out.str();
	
#elif LL_LINUX
	std::map< std::string, std::string > cpuinfo;
	LLFILE* cpuinfo_fp = LLFile::fopen(CPUINFO_FILE, "rb");
	if(cpuinfo_fp)
	{
		char line[MAX_STRING];
		memset(line, 0, MAX_STRING);
		while(fgets(line, MAX_STRING, cpuinfo_fp))
		{
			// /proc/cpuinfo on Linux looks like:
			// name\t*: value\n
			char* tabspot = strchr( line, '\t' );
			if (tabspot == NULL)
				continue;
			char* colspot = strchr( tabspot, ':' );
			if (colspot == NULL)
				continue;
			char* spacespot = strchr( colspot, ' ' );
			if (spacespot == NULL)
				continue;
			char* nlspot = strchr( line, '\n' );
			if (nlspot == NULL)
				nlspot = line + strlen( line ); // Fallback to terminating NUL
			std::string linename( line, tabspot );
			std::string llinename(linename);
			LLStringUtil::toLower(llinename);
			std::string lineval( spacespot + 1, nlspot );
			cpuinfo[ llinename ] = lineval;
		}
		fclose(cpuinfo_fp);
	}
# if LL_X86
	std::string flags = " " + cpuinfo["flags"] + " ";
	LLStringUtil::toLower(flags);
	mHasSSE = ( flags.find( " sse " ) != std::string::npos );
	mHasSSE2 = ( flags.find( " sse2 " ) != std::string::npos );
	
	F64 mhz;
	if (LLStringUtil::convertToF64(cpuinfo["cpu mhz"], mhz)
	    && 200.0 < mhz && mhz < 10000.0)
	{
		mCPUMhz = (S32)llrint(mhz);
	}
	if (!cpuinfo["model name"].empty())
		mCPUString = cpuinfo["model name"];
# endif // LL_X86
#endif // LL_LINUX
}