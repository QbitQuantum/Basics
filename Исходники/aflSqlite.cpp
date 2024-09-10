bool SQLite::dumpSQL(String* dest)
{
	if(!m_sqlite)
		return false;
	String sql;
	sql.printf("select name,sql from sqlite_master;");
	SQRes res = exec(sql);
	*dest = "begin;";
	while(res->next())
	{
		dest->appendf("%s;\n",res->getColumn(1));
		sql.printf("select * from %s;",SQLSTRING(res->getColumn(0)));
		SQRes data = exec(sql);

		String s;
		INT c,r;
		INT cols = data->getFeilds();
		INT rows = data->getRows();
	
		for(r=0;r<rows;r++)
		{
			String work;
			for(c=0;c<cols;c++)
			{
				if(c)
					work += ',';
				work.appendf("'%s'",SQLSTRING(data->getColumn(r,c)));
			}
			s.appendf("INSERT INTO %s values(%s);\n",SQLSTRING(res->getColumn(0)),work.c_str());
		}
		*dest += s;
	}		
	*dest += "commit;";
	return true;
}