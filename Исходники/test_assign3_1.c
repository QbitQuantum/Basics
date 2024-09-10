// ************************************************************ 
void
testCreateTableAndInsert (void)
{
  RM_TableData *table = (RM_TableData *) malloc(sizeof(RM_TableData));
  TestRecord inserts[] = { 
    {1, "aaaa", 3}, 
    {2, "bbbb", 2},
    {3, "cccc", 1},
    {4, "dddd", 3},
    {5, "eeee", 5},
    {6, "ffff", 1},
    {7, "gggg", 3},
    {8, "hhhh", 3},
    {9, "iiii", 2}
  };
  int numInserts = 9, i;
  Record *r;
  RID *rids;
  Schema *schema;
  testName = "test creating a new table and inserting tuples";
  schema = testSchema();
  rids = (RID *) malloc(sizeof(RID) * numInserts);
  
  TEST_CHECK(initRecordManager(NULL));
  //printf("\n Testing create table");
  TEST_CHECK(createTable("test_table_r.txt",schema));
  //printf("\n Testing open Table");
  TEST_CHECK(openTable(table, "test_table_r.txt"));
 printf("\n Opened "); 
  // insert rows into table
   for(i = 0; i < numInserts; i++)
    {
    	printf("\n Inserting");
      r = fromTestRecord(schema, inserts[i]);
      	
      TEST_CHECK(insertRecord(table,r)); 
      rids[i] = r->id;
    }

 TEST_CHECK(closeTable(table));
  TEST_CHECK(openTable(table, "test_table_r.txt"));
	printf("\n Opened successsfully");
  // randomly retrieve records from the table and compare to inserted ones
  for(i = 0; i < 1000; i++)
    {
      int pos = rand() % numInserts;
      RID rid = rids[pos];
      printf("\n getting records");
      TEST_CHECK(getRecord(table, rid, r));
      ASSERT_EQUALS_RECORDS(fromTestRecord(schema, inserts[pos]), r, schema, "compare records");
    }
  
  TEST_CHECK(closeTable(table));
  TEST_CHECK(deleteTable("test_table_r.txt"));
  TEST_CHECK(shutdownRecordManager());

  free(rids);
  free(table);
  TEST_DONE();
}