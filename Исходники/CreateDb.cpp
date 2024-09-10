/*----------------------------------------------------------------------------------------------
	Create the database.  Return 0 if successful, or a nonzero value if an error occurs.
----------------------------------------------------------------------------------------------*/
int CreateDB(const char * pszServer, const char * pszDB, const char * pszOutputDir,
	const char * pszInitScript,	bool fForceCreate)
{
	HRESULT hr;

	static const wchar szwMaster[] = L"master";
	StrUniBuf stubServer(pszServer);
	StrUniBuf stubDatabase(pszDB);

	if (stubServer.Overflow() || stubDatabase.Overflow())
	{
		fprintf(stderr, "Out of memory filling static buffers??\n");
		return __LINE__;
	}
	try
	{
		SqlDb sdb;
		SqlStatement sstmt;
		StrAnsiBufBig stabCmd;
		hr = sdb.Open(stubServer.Chars(), stubDatabase.Chars());
		if (SUCCEEDED(hr))
		{
			sdb.Close();
			if (fForceCreate)
			{
				// osql /U sa /E /n /b /Q "DROP DATABASE %1"
				hr = sdb.Open(stubServer.Chars(), szwMaster);
				if (FAILED(hr))
					ThrowHr(WarnHr(hr));
				sstmt.Init(sdb);
				stabCmd.Format("DROP DATABASE %s", pszDB);
				RETCODE rc;
				rc = SQLExecDirectA(sstmt.Hstmt(),
					reinterpret_cast<SQLCHAR *>(const_cast<char *>(stabCmd.Chars())), SQL_NTS);
				VerifySqlRc(rc, sstmt.Hstmt(), stabCmd.Chars());
				sstmt.Clear();
				sdb.Close();
			}
			else
			{
				fprintf(stderr, "The database \"%s\" already exists on the server \"%s\".\n",
					pszDB, pszServer);
				fprintf(stderr,
					"Use the -f command line flag to force recreating this database.\n");
				return 1;
			}
		}
		// osql -U sa -E -n -b -Q "CREATE DATABASE %1 ON
		// (NAME=%1,FILENAME='%OUTPUT_DIR%\%1.mdf',FILEGROWTH=5MB) LOG ON
		// (NAME='%1_Log', FILENAME='%OUTPUT_DIR%\%1_log.ldf',FILEGROWTH=5MB)"
		hr = sdb.Open(stubServer.Chars(), szwMaster);
		CheckHr(hr);
		sstmt.Init(sdb);
		if (pszOutputDir)
			stabCmd.Format("CREATE DATABASE %s ON (NAME='%s',FILENAME='%s\\%s.mdf') \
LOG ON (NAME='%s_Log',FILENAME='%s\\%s_log.ldf')",
			pszDB, pszDB, pszOutputDir, pszDB, pszDB, pszOutputDir, pszDB);
		else
			stabCmd.Format("CREATE DATABASE %s ", pszDB);

		RETCODE rc;
		rc = SQLExecDirectA(sstmt.Hstmt(),
			reinterpret_cast<SQLCHAR *>(const_cast<char *>(stabCmd.Chars())), SQL_NTS);
		VerifySqlRc(rc, sstmt.Hstmt(), stabCmd.Chars());
		sstmt.Clear();
		sdb.Close();
		if (pszInitScript)
		{
			InitializeDB(stubServer.Chars(), stubDatabase.Chars(), pszInitScript);
		}
	}
	catch (Throwable & thr)
	{
		fprintf(stderr, "Error %s caught creating database \"%s\" on server \"%s\"!\n",
			AsciiHresult(thr.Error()), pszDB, pszServer);
		return __LINE__;
	}
	catch (...)
	{
		fprintf(stderr, "Error caught creating database \"%s\" on server \"%s\"!\n",
			pszDB, pszServer);
		return __LINE__;
	}
	return 0;
}