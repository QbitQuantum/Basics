bool DbHelper::BindParamInt(int* param)
{
	//todo: int형 파라미터 바인딩
	//http://wolfsi.egloos.com/10205557
	//두번째 매개변수는 1부터 시작이므로 후위연산
	//precision 참고
	//http://publib.boulder.ibm.com/infocenter/idshelp/v111/index.jsp?topic=/com.ibm.odbc.doc/sii-04-26325.htm
	SQLRETURN ret =SQLBindParameter(mCurrentSqlHstmt,mCurrentBindParam++,SQL_PARAM_INPUT, 
									 SQL_C_LONG, SQL_INTEGER, 10, 0, param, 0, NULL ); // = SQLBindParameter(...);
	///# 굿! 유일하게 제대로 한 팀.

	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
	{
		PrintSqlStmtError();
		return false;
	}

	return true;
}