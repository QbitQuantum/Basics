static void st_ReleaseHstmt(SQLHSTMT hstmt)
{
	//ÊÍ·ÅÓï¾ä¾ä±ú
	if (hstmt != SQL_NULL_HSTMT) {
		SQLCloseCursor(hstmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
		hstmt = SQL_NULL_HSTMT;
	}
}