int
create_table_server(Ndb * pNdb){
  int check;
  NdbSchemaCon * MySchemaTransaction = NdbSchemaCon::startSchemaTrans(pNdb);
  if( MySchemaTransaction == NULL )
    error_handler("startSchemaTransaction", pNdb->getNdbError(), 0);
  
  NdbSchemaOp * MySchemaOp = MySchemaTransaction->getNdbSchemaOp();	
  if( MySchemaOp == NULL ) 
    error_handler("getNdbSchemaOp", MySchemaTransaction->getNdbError(), 0);
  
  // Create table
  check = MySchemaOp->createTable( SERVER_TABLE,
				   8,	     	// Table size
				   TupleKey,	// Key Type
				   1		// Nr of Pages
				   ,DistributionGroup,
				   6,
				   78,
				   80,
				   1,
				   useTableLogging
                                   );
  if( check == -1 ) 
    error_handler("createTable", MySchemaTransaction->getNdbError(), 0);
  
  check = MySchemaOp->createAttribute
    ( SERVER_SUBSCRIBER_SUFFIX,
      TupleKey, 
      sizeof(char) << 3,
      SUBSCRIBER_NUMBER_SUFFIX_LENGTH,
      String, 
      MMBased,
      NotNullAttribute,
      0,
      0,
      1,
      16);
  if( check == -1 ) 
    error_handler("createAttribute (subscriber suffix)", 
		  MySchemaTransaction->getNdbError(), 0);

  // Create first column, primary key 
  check = MySchemaOp->createAttribute( SERVER_ID,
				       TupleKey, 
				       sizeof(ServerId) << 3,
				       1,
				       UnSigned, 
				       MMBased,
				       NotNullAttribute );
  if( check == -1 ) 
    error_handler("createAttribute (serverid)", 
		  MySchemaTransaction->getNdbError(), 0);


  check = MySchemaOp->createAttribute( SERVER_NAME,
				       NoKey, 
				       sizeof(char) << 3,
				       SERVER_NAME_LENGTH,
				       String, 
				       MMBased,
				       NotNullAttribute );
  if( check == -1 ) 
    error_handler("createAttribute (server name)", 
		  MySchemaTransaction->getNdbError(), 0);
  

  check = MySchemaOp->createAttribute( SERVER_READS,
				       NoKey, 
				       sizeof(Counter) << 3,
				       1,
				       UnSigned,
				       MMBased,
				       NotNullAttribute );
  if( check == -1 ) 
    error_handler("createAttribute (server reads)", 
		  MySchemaTransaction->getNdbError(), 0);

  check = MySchemaOp->createAttribute( SERVER_INSERTS,
				       NoKey, 
				       sizeof(Counter) << 3,
				       1,
				       UnSigned,
				       MMBased,
				       NotNullAttribute );
  if( check == -1 ) 
    error_handler("createAttribute (server inserts)", 
		  MySchemaTransaction->getNdbError(), 0);

  check = MySchemaOp->createAttribute( SERVER_DELETES,
				       NoKey, 
				       sizeof(Counter) << 3,
				       1,
				       UnSigned,
				       MMBased,
				       NotNullAttribute );
  if( check == -1 ) 
    error_handler("createAttribute (server deletes)", 
		  MySchemaTransaction->getNdbError(), 0);
  
  if( MySchemaTransaction->execute() == -1 ) {
    error_handler("schemaTransaction->execute()", 
		  MySchemaTransaction->getNdbError(), 0);
  }    
  NdbSchemaCon::closeSchemaTrans(MySchemaTransaction);
  return 0;
}