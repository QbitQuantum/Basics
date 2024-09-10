bool launchMake( const string &i_makefile, const string &i_rule, unsigned int i_nbJobs, const string &i_options, bool i_stopCurrentProgramOnFail )
{
	#ifdef __TRACE_SYSTEM__
		static int iMakefile = 0;
		string makefileCopyName;
		// look for a filename that is not already used
		do{
			if ( iMakefile>999 ) cerr << "WARNING: there is a lot of makefile copies already" << endl;
			stringstream ss;
			ss << "Makefile" << setw(3) << setfill('0') << iMakefile++;
			makefileCopyName = ss.str();
		}
		while ( ELISE_fp::exist_file( makefileCopyName ) );
		cout << "###copying [" << i_makefile << "] to [" << makefileCopyName << "]" << endl;
		ELISE_fp::copy_file( i_makefile, makefileCopyName, true );
		i_nbJobs = __TRACE_SYSTEM__; // no multithreading in trace_system mode
	#endif

	string nbJobsStr( "-j" );
	if ( i_nbJobs!=0 )
	{	
		stringstream ss;
		ss << i_nbJobs;
		nbJobsStr.append( ss.str() );
	}
	std::string aCom = string("\"")+(g_externalToolHandler.get( "make" ).callName())+"\" " + i_rule + " -f \"" + i_makefile + "\" " + nbJobsStr + " " + i_options;
	return ( System(aCom,!i_stopCurrentProgramOnFail)==EXIT_SUCCESS );
}