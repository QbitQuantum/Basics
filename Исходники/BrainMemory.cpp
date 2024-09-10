void   CBrainMemory::SetSystemItem(int64 Item,AnsiString Info){
	CppSQLite3Buffer SQL;
	CppSQLite3Query  Result;
	char a[30],b[30];
     int64toa(ROOM_SYSTEM,a);
	 int64toa(Item,b);

    SQL.format("select b from \"%s\" where a = \"%s\";",a,b);				
	Result = BrainDB.execQuery(SQL);
	bool Find = !Result.eof();
    Result.finalize();

	if(!Find){
		SQL.format("insert into \"%s\" values (\"%s\", ?)",
			a,
			b);
	}else{
		SQL.format("update \"%s\" set b = ? where a = \"%s\";",
			a,
			b
			);
	}

	CppSQLite3Statement State = BrainDB.compileStatement(SQL);
	State.bind(1,Info.c_str()); //替换第一个问号
	State.execDML();

}