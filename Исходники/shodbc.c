void dolines(SQLHSTMT *stmt, SQLSMALLINT ncol, char format)
{
	int j;
	long ans;

	string *str, *tstr;

	char istr[256];
	long sb = 0;

	SQLLEN si;

	str = new_string();
	tstr = new_string();

	for(;;)
	{
		ans = SQLFetch(*stmt);

		/*
		 * I assume error here is EOF...
		 */
		if((ans != SQL_SUCCESS) && ( ans != SQL_SUCCESS_WITH_INFO))
			break;

		for(j=0;j<ncol;j++)
		{

			si = 0;

			for(;;)
			{
				ans = SQLGetData(stmt, j+1, SQL_C_CHAR, istr, 256, &si);
				if(ans == SQL_NO_DATA) break;

				if(si == SQL_NO_TOTAL)
				{
					sb += 255;	
				}
				else
				{
					sb += si;
				}

				string_cat(tstr, istr);
		
				if(si != SQL_NO_TOTAL) break;
			}
			dolitem(str, string_s(tstr), (j == ncol - 1), format);
			string_clear(tstr);
		}
		string_cat_c(str, '\n');
		if(message_send(mes, str, 0, MES_SERVER_TO_CLIENT) < 0) return;
		string_clear(str);
	}
	string_delete(str);
	string_delete(tstr);
	return;
}