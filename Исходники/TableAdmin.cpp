void TableAdmin::Edit( int line, StructAdmin StrAdmin, SQLHDBC hdbc_loc )
{
	if( !( hasInit && line < SA_count ) ) return;

	// edit a record
	char temp[ 1024 ];
	sprintf( temp, "update Admin set canManageAdmin = %d, canManageStudent = %d, canSetProblem = %d, canSetPaper = %d, "
				   "canSetExam = %d, canDeleteGrade = %d, canEditGrade = %d where AdminName = \'%s\';",
				   StrAdmin.canManageAdmin ? 1 : 0, StrAdmin.canManageStudent ? 1 : 0, StrAdmin.canSetProblem ? 1 : 0,
				   StrAdmin.canSetPaper ? 1 : 0, StrAdmin.canSetExam ? 1 : 0, StrAdmin.canDeleteGrade ? 1 : 0,
				   StrAdmin.canEditGrade ? 1 : 0,  StrAdmin.Name );

	SQLHSTMT h;
	SQLAllocHandle( SQL_HANDLE_STMT, hdbc_loc, &h );
	SQLExecDirectA( h, (SQLCHAR *)temp, SQL_NTS );
	SQLFreeHandle( SQL_HANDLE_STMT, h );

	delete [ ] SA;
	Init( hdbc_loc, AdminName, PasswordHash );
	return;
}