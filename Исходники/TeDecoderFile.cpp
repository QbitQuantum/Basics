bool
TeDecoderFile::create()
{
	m_hFile = CreateFileA(
		params_.fileName_.c_str(),	// File name
		GENERIC_READ | GENERIC_WRITE,	// Read-write
		FILE_SHARE_READ
		| FILE_SHARE_WRITE,		// Allow sharing-- we're only doing a quick scan
		NULL,					// No security attributes
		CREATE_NEW,			    // Open a new file
		0,						// Ignore file attributes
		NULL);					// Ignore hTemplateFile
  
	if ( m_hFile == INVALID_HANDLE_VALUE) 
		return false;		// could not open file

	char			lpBuffer[1024];
	unsigned long	nNumberOfBytesToWrite=(long)params_.nBands() * (long)params_.ncols_ * (long)params_.nlines_;    // number of bytes to write
	nNumberOfBytesToWrite *= (long)params_.nbitsperPixel_[0]/8;    // number of bytes to write
	unsigned long	nNumberOfBytesWritten;  // pointer to number of bytes written

	for (;nNumberOfBytesToWrite > 1024; nNumberOfBytesToWrite-=1024)
	{
		if ( !WriteFile(
			m_hFile,                // handle to file to write to
			lpBuffer,               // pointer to data to write to file
			1024,					// number of bytes to write
			&nNumberOfBytesWritten,  // pointer to number of bytes written
			NULL					// pointer to structure for overlapped I/O
			))
 			return false;			// could not write to file
	}

	if ( !WriteFile(
		m_hFile,                // handle to file to write to
		lpBuffer,               // pointer to data to write to file
		nNumberOfBytesToWrite,	// number of bytes to write
		&nNumberOfBytesWritten,  // pointer to number of bytes written
		NULL					// pointer to structure for overlapped I/O
		))
 		return false;			// could not write to file
	
	SetFilePointer (m_hFile, NULL, NULL, FILE_BEGIN);

// Allocate buffer to get raster line from file

	switch (params_.dataType_[0]) {
	case (TeUNSIGNEDCHAR):
		m_buffer = new unsigned char[params_.ncols_];
		break;
	case (TeCHAR) :
		m_buffer = new char[params_.ncols_];
		break;
	case (TeUNSIGNEDSHORT):
		m_buffer = new unsigned short[params_.ncols_];
		break;
	case (TeSHORT):
		m_buffer = new short[params_.ncols_];
		break;
	case (TeUNSIGNEDLONG):
		m_buffer = new unsigned long[params_.ncols_];
		break;
	case (TeLONG):
		m_buffer = new long[params_.ncols_];
		break;
	case (TeFLOAT):
		m_buffer = new float[params_.ncols_];
		break;
	case (TeDOUBLE):
		m_buffer = new double[params_.ncols_];
		break;
    default:
        break;
	}

	if ( m_buffer == NULL )
		return false;

	if (params_.dummy_[0])
	{
		for (int b=0; b<params_.nBands();b++)
			for (int l=0; l<params_.nlines_;l++)
				for (int c=0; c<params_.ncols_;c++)
					setElement ( c, l, params_.dummy_[0], b);
	}
	return true;
}