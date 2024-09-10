void db_in(int score)
{
	int res;
	char* name;
    MYSQL mysql;
  
    mysql_init(&mysql);	// 初始化mysql结构  
						//mysql_real_connect()函数的功能是连接一个MYSql数据库服务器,
						//MYSQL结构地址是&mysql，host主机名或地址是localhost，
						//用户名是root,密码是root,数据库是mydb,端口是3306
    if (!mysql_real_connect(&mysql, "localhost", "root", "", "snake", 3306, NULL, 0))
    {
        printf("\n数据库连接发生错误!");
    }
    else
    {
        printf("\n数据库连接成功!\n"); 			
		//插入一条数据到数据库
	switch(ms)
	{
	case 200:mul=1;break;
	case 100:mul=2;break;
	case 50 :mul=4;break;
	default:break;
	}

			///////////取时间
			time ( &rawtime );
			timeinfo = localtime ( &rawtime );
			name=input_name();

		sprintf(sql_insert, "INSERT INTO score(name,score,time) values('%s','%d','%s')",name,mul*score,asctime (timeinfo));
		res = mysql_query(&mysql, sql_insert);
        if(res)
        {		
			 printf("插入数据失败!\n");
        }else 
		{
			printf("成绩输入成功\n");
		}
    }  
    mysql_close(&mysql); // 释放数据库连接 
	printf("任意键重试！");
	fgetchar();
	replay();

}