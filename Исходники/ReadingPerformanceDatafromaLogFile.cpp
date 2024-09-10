int __cdecl _tmain (int argc, TCHAR **argv)
{

	HQUERY          hQuery;
	PDH_STATUS      pdhStatus;
	DWORD           dwFormat = PDH_FMT_DOUBLE; 
	PDH_FMT_COUNTERVALUE  ItemBuffer;
	HCOUNTER        hCounter;
	TCHAR           szCounterPath[45] = 
		TEXT("\\Processor(0)\\% Processor Time");

	if (argc != 2) 
	{
		DisplayCommandLineHelp ();
		return -1;
	}

	// Open a query object.
	pdhStatus = PdhOpenQuery (argv[1],
		0,
		&hQuery);

	if( pdhStatus != ERROR_SUCCESS )
	{
		_tprintf(TEXT("PdhOpenQuery failed with %ld\n"), pdhStatus);
		goto cleanup;
	}

	// Add the counter that created the data in the log file.
	pdhStatus = PdhAddCounter (hQuery,
		szCounterPath,
		0,
		&hCounter);
	if( pdhStatus != ERROR_SUCCESS )
	{
		_tprintf(TEXT("PdhAddCounter failed with %ld\n"), pdhStatus);
		goto cleanup;
	}

	// Read a performance data record.
	pdhStatus = PdhCollectQueryData(hQuery);
	if( pdhStatus != ERROR_SUCCESS )
	{
		if ( pdhStatus !=  PDH_NO_MORE_DATA )
		{
			_tprintf(TEXT("PdhCollectQueryData failed with %ld\n"), pdhStatus);
		}
	}

	while (pdhStatus == ERROR_SUCCESS) 
	{ 
		// Format the performance data record.
		pdhStatus = PdhGetFormattedCounterValue (hCounter,
			dwFormat,
			(LPDWORD)NULL,
			&ItemBuffer);

		if (pdhStatus == ERROR_SUCCESS)
		{
			// Print the performance data record.
			_tprintf(TEXT("\nLog Record Value = %4.8f\n"), 
				ItemBuffer.doubleValue);
		}
		else
		{
			_tprintf(TEXT("\nPdhGetFormattedCounterValue failed with %ld.\n"), pdhStatus);
			goto cleanup;
		}

		// Read the next record
		pdhStatus = PdhCollectQueryData(hQuery);
		if( pdhStatus != ERROR_SUCCESS )
		{
			if ( pdhStatus !=  PDH_NO_MORE_DATA )
			{
				_tprintf(TEXT("PdhCollectQueryData failed with %ld\n"), pdhStatus);
			}
		}
	}

cleanup:
	// Close the query.
	if (hQuery)
		PdhCloseQuery (hQuery);

	return pdhStatus;
}