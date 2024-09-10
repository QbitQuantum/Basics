	/////////////////////////////////////////////////////////
	//close Avi file. Close all avi streams
	/////////////////////////////////////////////////////////
	CAviMan::CloseAviFile()
	{
		if(m_aviGetFrame)
			AVIStreamGetFrameClose(m_aviGetFrame);			//close get frame info

		for (DWORD i = 0; i < m_dwNumStreams; i++)
		{
			if(m_aviStream[i])
				AVIStreamRelease(m_aviStream[i]);
		}

		if (m_aviFile) AVIFileRelease(m_aviFile);

		m_aviFile = NULL;
		m_aviVideoStream = NULL;
		m_aviGetFrame = NULL;

		m_dwNumStreams = MAX_AVI_STREAM-1;


	}