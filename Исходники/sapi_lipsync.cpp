/**
	This method uses the sapi helpers to create an ISpStream object
	given an audio file
	@param audioFile - [in] path to audio file
	@return true if successful, false if not. Sets an appropriate error code
**/
bool sapi_lipsync::loadAudio(const std::wstring& audioFile)
{
    HRESULT hr = S_OK;

	this->m_strAudioFile = audioFile;
    try
    {
        m_bDone = false;
		
        hr = SPBindToFile(audioFile.c_str(), SPFM_OPEN_READONLY, &this->m_audioStream);
        if (hr != S_OK)
        {
            m_err = L"Error: Can't open audio file";
            throw(hr);
        }
        GUID guid; // unused
        hr = this->m_audioStream->GetFormat(&guid, &m_pWaveFmt);
        if (hr != S_OK)
        {
            m_err = L"Error: cannot get audio formatting information";
            throw (hr);
        }
        
        /// set the input stream to our newly created audio file
        hr = this->m_recog->SetInput(this->m_audioStream, TRUE);
        if (hr != S_OK)
        {
            m_err = L"Error: cannot set the input stream for ASR";
            throw (hr);
        }
    }
    catch (HRESULT& _hr)
    {
        hr = _hr;
    }
    return (hr == S_OK);

}