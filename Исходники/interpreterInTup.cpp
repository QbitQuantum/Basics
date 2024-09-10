void  create_table(Ndb* pMyNdb) {

    /****************************************************************
     *    Create SimpleTable and Attributes.
     *
     *    create table SimpleTable1(
     *        col0 int,
     *        col1 int not null,
     *        col2 int not null,
     *        col3 int not null ... 129)
     *
     ***************************************************************/

    int               check = -1 ;
    NdbSchemaOp       *MySchemaOp = NULL ;

    ndbout << endl << "Creating " << tableName << " ... " << endl;

    NdbSchemaCon* MySchemaTransaction = NdbSchemaCon::startSchemaTrans(pMyNdb);
    if(!MySchemaTransaction) error_handler(MySchemaTransaction->getNdbError(), NO_FAIL);

    MySchemaOp = MySchemaTransaction->getNdbSchemaOp();
    if( !MySchemaOp ) error_handler(MySchemaTransaction->getNdbError(), NO_FAIL);
    // Create table
    check = MySchemaOp->createTable( tableName,
                                     8,         // Table size
                                     TupleKey,  // Key Type
                                     40         // Nr of Pages
                                   );

    if( check == -1 ) error_handler(MySchemaTransaction->getNdbError(), NO_FAIL);

    ndbout << "Creating attributes ... " << flush;

    // Create first column, primary key
    check = MySchemaOp->createAttribute( attrName[0],
                                         TupleKey,
                                         32,
                                         1/*3, tAttributeSize */,
                                         UnSigned,
                                         MMBased,
                                         NotNullAttribute );

    if( check == -1 ) error_handler(MySchemaTransaction->getNdbError(), NO_FAIL);

    // create the 2 .. n columns.
    for ( int i = 1; i < MAXATTR; i++ ) {
        check = MySchemaOp->createAttribute( attrName[i],
                                             NoKey,
                                             32,
                                             tAttributeSize,
                                             UnSigned,
                                             MMBased,
                                             NotNullAttribute );

        if( check == -1 ) error_handler(MySchemaTransaction->getNdbError(), NO_FAIL);
    }

    ndbout << "OK" << endl;

    if( MySchemaTransaction->execute() == -1 ) {
        ndbout << MySchemaTransaction->getNdbError() << endl;
    } else {
        ndbout << tableName[0] << " created" << endl;
    }


    NdbSchemaCon::closeSchemaTrans(MySchemaTransaction);

    return;

}