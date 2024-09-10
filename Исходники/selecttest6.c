int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = createConnection();
  rv  = con->connect("root","manager");
  if(rv!=OK)return 1;

  AbsSqlStatement *stmt = createStatement();
  stmt->setConnection(con);
  char statement[200];

  strcpy(statement,"CREATE TABLE t1(f1 INT,f2 CHAR(20));");
  if(strcmp(getenv("DSN"),"db2")==0)
      strcpy(statement,"CREATE TABLE t1(f1 INT,f2 CHAR(20))");

  int rows=0;
  rv = stmt->prepare(statement);
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 1;
 }

 rv  = stmt->execute(rows);
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 2;
 }
 stmt->free();
 printf("Table created\n");
 con->commit();
 //  insert records

 strcpy(statement,"INSERT INTO t1 VALUES(?,?);");
 if(strcmp(getenv("DSN"),"db2")==0)
     strcpy(statement,"INSERT INTO t1 VALUES(?,?)");

 int f1var = 1;
 char f2var[20] = "lakshya";
 

 rv = stmt->prepare(statement);
 if(rv!=OK)
 {
   delete stmt;
   delete con;
   return 3;
 }

 int count=0;

 for(int i=0;i<2;i++)
 {
    
   for(int j=0;j<5;j++)
    {	
        f1var = j;
        rv = con->beginTrans();
	if(rv!=OK)break;
	
         	
        stmt->setIntParam(1,f1var);
	stmt->setStringParam(2,f2var);

	rv = stmt->execute(rows);
	if(rv!=OK)break;
	rv = con->commit();
	if(rv!=OK)break;
	count++;
    }
    printf("%d rows inserted\n",count);
 }
 stmt->free();

//*******************************************

  strcpy(statement,"SELECT * FROM t1;");
  if(strcmp(getenv("DSN"),"db2")==0)
      strcpy(statement,"SELECT * FROM t1");
  /*rv = stmt->prepare(statement);
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 1;
  } */ 
  stmt->bindField(1,&f1var);
  stmt->bindField(2,f2var);
  
  void *ret;
  count = 0;
  rv = con->beginTrans();
  if(rv!=OK)return 6;
  stmt->execute(rows);
  
  

  while(1)
  {
     ret = ((char*)stmt->fetch());
     if(ret ==NULL)
     {
       
      printf("fetch failed without prepare\n");
      strcpy(statement,"DROP TABLE t1;");
      if(strcmp(getenv("DSN"),"db2")==0)
          strcpy(statement,"DROP TABLE t1;");
      rv = stmt->prepare(statement);
      rv = stmt->execute(rows);
      if(rv==OK){printf("Table dropped successfully\n");}
      stmt->free();
      con->commit();
      delete stmt;
      delete con;
      return 0;
     }
     printf("Test script failed\n");
  }
 delete stmt;
 delete con;
 return 8;
}  