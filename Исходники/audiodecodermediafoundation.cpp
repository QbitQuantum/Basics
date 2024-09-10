int AudioDecoderMediaFoundation::open()
{
    if (sDebug) {
        std::cout << "open() " << m_filename << std::endl;
    }

    //Assumes m_filename is ASCII and converts it to UTF-16 (wide char).
    /*
	int wcFilenameLength = m_filename.size();
	for(std::wstring::size_type i=0; i < m_filename.size(); ++i)
	{
		m_wcFilename[i] = m_filename[i];
	}
	m_wcFilename[wcFilenameLength] = (wchar_t)'\0';

	std::string s;

	std::wstring stemp = s2ws(m_filename); // Temporary buffer is required
	LPCWSTR result = (LPCWSTR)stemp.c_str();
    */
   
    //LPCWSTR result; 
    const char* utf8Str = m_filename.c_str();
    MultiByteToWideChar(CP_ACP, 
                        0, 
                        utf8Str, 
                        -1, //assume utf8Str is NULL terminated and give us back a NULL terminated string
                        (LPWSTR)m_wcFilename,
                        512);
    
    LPCWSTR result = m_wcFilename;

    HRESULT hr(S_OK);
    // Initialize the COM library.
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) {
        std::cerr << "SSMF: failed to initialize COM" << std::endl;
        return AUDIODECODER_ERROR;
    }

    // Initialize the Media Foundation platform.
    hr = MFStartup(MF_VERSION);
    if (FAILED(hr)) {
        std::cerr << "SSMF: failed to initialize Media Foundation" << std::endl;
        return AUDIODECODER_ERROR;
    }

    // Create the source reader to read the input file.
    hr = MFCreateSourceReaderFromURL(/*m_wcFilename*/result, NULL, &m_pReader);
    if (FAILED(hr)) {
        std::cerr << "SSMF: Error opening input file:" << m_filename << ", with error: " << HRESULT_CODE(hr) << std::endl;
        return AUDIODECODER_ERROR;
    }

    if (!configureAudioStream()) {
        std::cerr << "SSMF: Error configuring audio stream." << std::endl;
        return AUDIODECODER_ERROR;
    }

    if (!readProperties()) {
        std::cerr << "SSMF::readProperties failed" << std::endl;
        return AUDIODECODER_ERROR;
    }

    //Seek to position 0, which forces us to skip over all the header frames.
    //This makes sure we're ready to just let the Analyser rip and it'll
    //get the number of samples it expects (ie. no header frames).
    seek(0);

    return AUDIODECODER_OK;
}