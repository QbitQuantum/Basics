	bool qConsole::writeMessagesToFile(string strFilename)
	{
		ofstream fOutputFile(strFilename.c_str(), ios::app);
		if(!fOutputFile)
		{
			setMessage(MSG_ERROR, "qConsole", "writeMessagesToFile : Cannot open file '" + strFilename + "' for console output");
			return false;
		}

		/* _ftime stuff ripped out of MSDN entry for time -> getting current */

  		struct __timeb64 timebuffer;
		char *timeline;
		char *test = (char*)malloc(sizeof(char) * 100);
		_ftime64( &timebuffer );
		timeline = _ctime64( & ( timebuffer.time ) );

		sprintf(test, "%.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20] );

		fOutputFile << "qConsole Console Output (Messages/Errors) for run at " << test;
		for(unsigned int i = 0; i < m_vMessageBuffer.size(); ++i)
		{
			fOutputFile << m_vMessageBuffer[i] << endl;
		}
		fOutputFile <<"--------------------------------------------"<<endl;
		free(test);
		fOutputFile.close();
		return true;
	}