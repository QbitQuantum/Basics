//-------------------------------------------------------------------
// Open a file for writing and prepare the sink writer
//
HRESULT VidWriter::initSinkWriter(WCHAR *filename)
{
    HRESULT hr = S_OK;
	IMFMediaType *pMediaTypeOut = NULL;   
    IMFMediaType *pMediaTypeIn = NULL;   
   
	// Create the sink writer
	SafeRelease(&m_pWriter);
	hr = MFCreateSinkWriterFromURL(filename, NULL, NULL, &m_pWriter);
	if (FAILED(hr)) goto done;

	// Create the output media type
	hr = MFCreateMediaType(&pMediaTypeOut);   
	if (FAILED(hr)) goto done;

	// Configure it
	hr = configureOutput(pMediaTypeOut);
	if (FAILED(hr)) goto done;

	// Add it to the sink writer
	hr = m_pWriter->AddStream(pMediaTypeOut, &m_streamIndex);   
	if (FAILED(hr)) goto done;

	// Create the input media type
	hr = MFCreateMediaType(&pMediaTypeIn);   
	if (FAILED(hr)) goto done;
	
	// Configure it
	hr = configureInput(pMediaTypeIn);
	if (FAILED(hr)) goto done;

	// Add it to the sink writer
	hr = m_pWriter->SetInputMediaType(m_streamIndex, pMediaTypeIn, NULL);   
   	if (FAILED(hr)) goto done;  

    // Tell the sink writer to start accepting data
	hr = m_pWriter->BeginWriting();

	// Reset the frame timer
	m_rtStart = 0;

done:    
	SafeRelease(&pMediaTypeOut);
    SafeRelease(&pMediaTypeIn);
    return hr;
}