SQLRETURN SendLongData(void)
{
	// Declare The Local Memory Variables

	SQLPOINTER Value;
	SQLCHAR Buffer[20];
	SQLCHAR InputParam[] = "Special Instructions";
	size_t DataSize = 0;
	unsigned char in_data[200];
	int i;
	for (i = 0; i < BUFSIZE; i++)
		in_data[i] = (unsigned char)(BUFSIZE - 1 - i);
	// Start The Data-At-Execution Sequence By Calling 
	// SQLParamData()
	rc = SQLParamData(StmtHandle, (SQLPOINTER *) & Value);
	VERBOSE("returned a value of  %s\n", (const char *)Value);
	// Examine The Contents Of Value (Returned By SQLParamData())
	// To Determine Which Data-At-Execution Parameter Currently
	// Needs Data
	if (strcmp((const char *)Value, (const char *)InputParam) == 0
	    && rc == SQL_NEED_DATA) {
		// As Long As Data Is Available For The Parameter, Retrieve
		// Part Of It From The External Data File And Send It To The
		// Data Source
		// while (InFile.get(Buffer, sizeof(Buffer)))
		//{
		while (DataSize < BUFSIZE) {
			for (i = DataSize; i < DataSize + CHUNKSIZE; i++) {
				Buffer[i - DataSize] = in_data[i];
				VERBOSE("Buffer[%d]=in_data[%d]=%d\n",
					i - DataSize, i, in_data[i]);
			}

			rc = SQLPutData(StmtHandle, (SQLPOINTER) Buffer,
					CHUNKSIZE);
			assert(rc == SQL_SUCCESS
			       || rc == SQL_SUCCESS_WITH_INFO);
			DataSize = DataSize + CHUNKSIZE;

			// If The Amount Of Data Retrieved Exceeds The Size Of 
			// The Column (Which Is 200 Bytes), Call The SQLCancel() 
			// Function To Terminate The Data-At-Execution 
			// Sequence And Exit
			if (DataSize > BUFSIZE) {
				rc = SQLCancel(StmtHandle);
				return (SQL_ERROR);
			}
		}

		// Call SQLParamData() Again To Terminate The 
		// Data-At-Execution Sequence
		rc = SQLParamData(StmtHandle, (SQLPOINTER *) & Value);

		// Display A Message Telling How Many Bytes Of Data Were Sent
		if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
			VERBOSE("Successfully inserted %d\n", DataSize);
			VERBOSE(" bytes of data into the database.\n");
		}

	}
	// Close The External Data File
	//InFile.close();

	// Return The ODBC API Return Code To The Calling Function 
	return (rc);
}