int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = createConnection();
  rv = con->connect("root","manager");
  if(rv !=OK)return 1;
  printf("Connection opened\n");

  AbsSqlStatement *stmt = createStatement(); 
  stmt->setConnection(con);
  char statement[200];
  strcpy(statement,"CREATE TABLE t1(f1 INT);");
  
  int  rows;
  rv = con->disconnect();
  if(rv!=OK)return 2;
  printf("Connection closed\n"); 
  
  rv = stmt->prepare(statement);
  if(rv==OK)
  {
     
     delete stmt;
     delete con;
     printf("Test script failed\n");
     return 3;
  }
  printf("Test script passed\n");
  delete stmt;
  delete con;
  return 0;
}