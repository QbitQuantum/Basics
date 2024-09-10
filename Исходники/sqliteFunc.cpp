int runSQLite(int clientSelect)
{
    clientNumber=clientSelect;
	sqlite3 *db = NULL;
	int rc;
	//打开指定的数据库文件
	rc = sqlite3_open("./data/DataBase.db",&db);
	if(rc)
	{
		fprintf(stderr,"can't open database: %s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	else
		printf("You have opened a sqlite3 database successfully!\n");
	//创建表
	createTable(db);
	//插入记录
	insertRecord(db);
	//查询
	//使用sqlite3_get_table实现查询
	//inquire_nocb(db);
	printf("--------------------------------\n");
	//使用回调函数实现查询
	inquire_Usecb(db);
	//删除记录
	//deleteRecord(db);
	//关闭数据库
	sqlite3_close(db);
	return 0;
}