static void odbc_Error(SQLSMALLINT type, void *obj, t_eventlog_level level, const char *function)
{
	SQLCHAR mState[6] = "\0";
	long native = 0;
	SQLSMALLINT mTextLen;
	short i = 0;

	while(SQLGetDiagRec(type, obj, ++i, NULL, NULL, NULL, 0, &mTextLen) != SQL_NO_DATA) {
		SQLCHAR *mText = xcalloc(sizeof *mText, ++mTextLen);
		SQLGetDiagRec(type, obj, i, mState,	&native, mText, mTextLen, NULL);
		eventlog(level, function, "ODBC Error: State %s, Native %i: %s", mState, native, mText);
		xfree(mText);
	}
}