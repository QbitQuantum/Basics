static long TestReadShortFile(CReader & oReader, const std::string & csPath)
{
	long lErrors = 0;

	printf("\nTesting CReader::ReadFile() for short files\n");

	try
	{
		CByteArray oFullData = oReader.ReadFile(csPath, 0, FULL_FILE);

		CByteArray oData1 = oReader.ReadFile(csPath, 2, FULL_FILE);
		if (oData1.Size() + 2 != oFullData.Size() ||
			memcmp(oData1.GetBytes(), oFullData.GetBytes() + 2, oData1.Size()) != 0)
		{
			ERR_LOG("ERR: CReader::ReadFile(offset != 0) failed\n", lErrors);
		}

		CByteArray oData2 = oReader.ReadFile(csPath, 2, oFullData.Size() - 3);
		if (oData2.Size() + 3 != oFullData.Size() ||
			memcmp(oData2.GetBytes(), oFullData.GetBytes() + 2, oData2.Size()) != 0)
		{
			ERR_LOG("ERR: CReader::ReadFile(length != FULL_FILE) failed\n", lErrors);
		}

		CByteArray oData3 = oReader.ReadFile(csPath, 0, oFullData.Size() + 1);
		if (!oData3.Equals(oFullData))
			ERR_LOG("ERR: CReader::ReadFile(length = too long) returned a wrong data\n", lErrors);

		bool bExceptionCaught = false;
		try
		{
			CByteArray oData4 = oReader.ReadFile(csPath, oFullData.Size() + 1, 1);
		}
		catch(CMWException & e) {
			bExceptionCaught = true;
			if ( (unsigned) e.GetError() != EIDMW_ERR_PARAM_RANGE)
			ERR_LOG("ERR: CReader::ReadFile(offset = too long) has thrown the wrong exception\n", lErrors);
		}
		if (!bExceptionCaught)
			ERR_LOG("ERR: CReader::ReadFile(offset = too long) didn't throw an exception\n", lErrors);

		CByteArray oData5 = oReader.ReadFile(csPath, 0, oFullData.Size());
		if (!oData5.Equals(oFullData))
			ERR_LOG("ERR: CReader::ReadFile(length = file size) failed\n", lErrors);
	}
	catch(const CMWException &e)
	{
		ERR_LOG("ERR: CReader::ReadFile() threw an MWException\n", lErrors);
		printf("   MWException code: 0x%0x\n", (unsigned) e.GetError());
	}
	catch (...)
	{
		ERR_LOG("ERR: CReader::ReadFile() threw an Exception\n", lErrors);
	}

	return lErrors;
}