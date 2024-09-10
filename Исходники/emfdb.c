int dbLoad(int did, char_t *filename, int flags)
{
	gstat_t		sbuf;
	char_t		*buf, *keyword, *value, *path, *ptr;
	char_t		*tablename;
	int			fd, tid, row;
	dbTable_t	*pTable;

    a_assert(did >= 0);

	fmtAlloc(&path, FNAMESIZE, T("%s/%s"), basicGetProductDir(), filename);
	trace(4, T("DB: About to read data file <%s>\n"), path);

	if (gstat(path, &sbuf) < 0) {
		trace(3, T("DB: Failed to stat persistent data file.\n"));
		bfree(B_L, path);
		return -1;
	}

	fd = gopen(path, O_RDONLY | O_BINARY, 0666);
	bfree(B_L, path);

	if (fd < 0) {
		trace(3, T("DB: No persistent data file present.\n"));
		return -1;
	}

	if (sbuf.st_size <= 0) {
		trace(3, T("DB: Persistent data file is empty.\n"));
		gclose(fd);
		return -1;
	}
/*
 *	Read entire file into temporary buffer
 */
	buf = balloc(B_L, sbuf.st_size + 1);
#ifdef CE
	if (readAscToUni(fd, &buf, sbuf.st_size) != (int)sbuf.st_size) {
#else
	if (gread(fd, buf, sbuf.st_size) != (int)sbuf.st_size) {
#endif
		trace(3, T("DB: Persistent data read failed.\n"));
		bfree(B_L, buf);
		gclose(fd);
		return -1;
	}

	gclose(fd);
	*(buf + sbuf.st_size) = '\0';

	row = -1;
	tid = -1;
	pTable = NULL;
	ptr = gstrtok(buf, T("\n"));
	tablename = NULL;

	do {
		if (crack(ptr, &keyword, &value) < 0) {
			trace(5, T("DB: Failed to crack line %s\n"), ptr);
			continue;
		}

		a_assert(keyword && *keyword);

		if (gstrcmp(keyword, KEYWORD_TABLE) == 0) {
/*
 *			Table name found, check to see if it's registered
 */
			if (tablename) {
				bfree(B_L, tablename);
			}

			tablename = bstrdup(B_L, value);
			tid = dbGetTableId(did, tablename);

			if (tid >= 0) {
				pTable = dbListTables[tid];
			} else {
				pTable = NULL;
			}

		} else if (gstrcmp(keyword, KEYWORD_ROW) == 0) {
/*
 *			Row/Record indicator found, add a new row to table
 */
			if (tid >= 0) {
				int nRows = dbGetTableNrow(did, tablename);

				if (dbSetTableNrow(did, tablename, nRows + 1) == 0) {
					row = nRows;
				}
			}

		} else if (row != -1) {
/*
 *			some other data found, assume it's a COLUMN=value
 */
			int nColumn = GetColumnIndex(tid, keyword);

			if ((nColumn >= 0) && (pTable != NULL)) {
				int nColumnType = pTable->columnTypes[nColumn];
				if (nColumnType == T_STRING) {
					dbWriteStr(did, tablename, keyword, row, value);
				} else {
					dbWriteInt(did, tablename, keyword, row, gstrtoi(value));
				}
			}
		}
	} while ((ptr = gstrtok(NULL, T("\n"))) != NULL);

	if (tablename) {
		bfree(B_L, tablename);
	}

	bfree(B_L, buf);

	return 0;
}

/******************************************************************************/
/*
 *	Return a table id given the table name
 */

int dbGetTableId(int did, char_t *tablename)
{
	int			tid;
	dbTable_t	*pTable;

	a_assert(tablename);

	for (tid = 0; (tid < dbMaxTables); tid++) {
		if ((pTable = dbListTables[tid]) != NULL) {
			if (gstrcmp(tablename, pTable->name) == 0) {
				return tid;
			}
		}
	}
	
	return -1;
}