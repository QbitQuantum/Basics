int WINAPI GetData(HINTERNET hResource, LPBYTE& lpData, DWORD& pdwDataLength)
{
	LPBYTE lpBuf;       // buffer for the data
	DWORD dwSize;       // size of the data available
	DWORD  dwDownloaded; // size of the downloaded data
	DWORD  dwSizeSum=0;  // size of the data in the textbox
	LPBYTE lpHolding;    // buffer to merge the data and buffer

	// This loop handles reading the data.  
	do
	{
		// The call to InternetQueryDataAvailable determines the
		// amount of data available to download.
		if (!InternetQueryDataAvailable(hResource,&dwSize,0,0))
		{
			//printf("InternetQueryDataAvailable failed (%d)\n", GetLastError());
			return FALSE;
		}
		else
		{
			if (dwSize == 0)
			{
				break;
			}

			// Allocate a buffer of the size returned by
			// InternetQueryDataAvailable.
			lpBuf = new BYTE[dwSize];

			// Read the data from the HINTERNET handle.
			if(!InternetReadFile(hResource,
				(LPVOID)lpBuf,
				dwSize,
				&dwDownloaded))
			{
				//printf("InternetReadFile failed (%d)\n", GetLastError());
				delete[] lpBuf;
				break;
			}
			else
			{
				// Allocate the holding buffer.
				lpHolding = new BYTE[dwSizeSum + dwDownloaded];

				// current holding buffer position
				size_t pos = 0;

				// Check if there has been any data written,
				// save it to holding then delete.
				if (dwSizeSum != 0)
				{
					memcpy(lpHolding, lpData, dwSizeSum);
					pos = dwSizeSum;
					delete[] lpData;
				}

				// concat downloaded data to holding buffer
				memcpy(lpHolding+pos, lpBuf, dwDownloaded);

				// save holding pointer to our return param
				lpData = lpHolding;

				// Add the size of the downloaded data to the 
				// data size.
				dwSizeSum = dwSizeSum + dwDownloaded;

				// remove temp download buffer
				delete[] lpBuf;
			}
		}  
	}  
	while(TRUE);
	// enable these printf statements if you want but shouldn't be needed
	// printf("Finished. Downloaded %d bytes.", dwSizeSum);
	 pdwDataLength = dwSizeSum;

	return TRUE;
}