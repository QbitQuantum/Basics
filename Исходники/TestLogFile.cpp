void TestLogFileMultipleReadsAfterOpens(void)
{
	CLogFile*		pcLogFile;
	CDiskFile*		pcDiskFile;
	CFileBasic		cFile;
	CFileUtil		cFileUtil;
	char			szSource[] = {"The Name of the Wise Man"};
	int				iSourcelen;
	char			szResult[50];
	char			szWrite[] = {"Cat Catt ct... "};
	int				iWriteLen;
	char			szA[] = {"A"};

	cFileUtil.RemoveDir("Output/LogFile2");
	cFileUtil.MakeDir("Output/LogFile2");
	pcDiskFile = DiskFile("Output/LogFile2/OpenClose.txt");
	pcDiskFile->Open(EFM_ReadWrite_Create);
	iSourcelen = (int)strlen(szSource);
	pcDiskFile->Write(szSource, iSourcelen + 1, 1);
	pcDiskFile->Close();
	AssertTrue(cFileUtil.Exists("Output/LogFile2/OpenClose.txt"));

	pcLogFile = LogFile(pcDiskFile);
	cFile.Init(pcLogFile);
	pcLogFile->Begin();

	AssertTrue(cFile.Open(EFM_Read));
	AssertInt(iSourcelen + 1, (int)cFile.GetFileSize());
	cFile.ReadData(szResult, iSourcelen + 1);
	AssertString(szSource, szResult);
	cFile.Close();

	cFile.Open(EFM_ReadWrite_Create);
	iWriteLen = (int)strlen(szWrite);
	cFile.WriteData(szWrite, iWriteLen);
	AssertInt(iSourcelen + 1, (int)cFile.GetFileSize());
	pcLogFile->Close();

	cFile.Delete();
	AssertTrue(cFileUtil.Exists("Output/LogFile2/OpenClose.txt"));
	AssertInt(0, (int)cFile.GetFileSize());

	cFile.Open(EFM_ReadWrite_Create);
	cFile.Write(szA, 2, 1);
	AssertInt(2, (int)cFile.GetFileSize());

	cFile.Close();

	pcLogFile->Commit();
	cFile.Kill();

	AssertTrue(cFileUtil.Exists("Output/LogFile2/OpenClose.txt"));
	AssertInt(2, cFileUtil.Size("Output/LogFile2/OpenClose.txt"));

	pcDiskFile = DiskFile("Output/LogFile2/OpenClose.txt");
	pcLogFile = LogFile(pcDiskFile);
	cFile.Init(pcLogFile);
	pcLogFile->Begin();

	AssertTrue(cFile.Open(EFM_Read));
	cFile.ReadData(szResult, 2);
	AssertString("A", szResult);

	cFile.Seek(0);
	cFile.ReadData(szResult, 2);
	AssertString("A", szResult);

	cFile.Close();

	cFile.Delete();
	pcLogFile->Commit();
	cFile.Kill();

	AssertFalse(cFileUtil.Exists("Output/LogFile2/OpenClose.txt"));
}