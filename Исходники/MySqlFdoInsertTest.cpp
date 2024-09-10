void MySqlFdoInsertTest::insertBoundaryUnsigned()
{
    StaticConnection* conn = new MySqlStaticConnection();

    try {

        UnitTestUtil::SetProvider( conn->GetServiceName() ); 

        conn->connect();

        FdoSchemaManagerP mgr = conn->CreateSchemaManager();

        FdoSmPhMgrP phMgr = mgr->GetPhysicalSchema();

        FdoStringP datastore = phMgr->GetDcOwnerName(
            UnitTestUtil::GetEnviron("datastore", UNSIGNED_SUFFIX)
        );

        FdoSmPhDatabaseP database = phMgr->GetDatabase();

        FdoSmPhOwnerP owner = phMgr->FindOwner( datastore, L"", false );
        if ( owner ) {
            owner->SetElementState( FdoSchemaElementState_Deleted );
            owner->Commit();
        }

        owner = database->CreateOwner(
            datastore, 
            false
        );
        owner->SetPassword( L"test" );

        FdoStringP tableName = L"unsigned_test";
            
        FdoSmPhTableP table = owner->CreateTable( tableName );
        table->SetPkeyName( tableName + L"_key" );
        FdoSmPhColumnP column = table->CreateColumnInt32(
            L"id",
            false
        );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnUnknown(
            L"uint_column",
            L"int unsigned",
            false,
            0,
            0
        );
        owner->Commit();
        
        phMgr = NULL;
        mgr = NULL;
        conn->disconnect();
        delete conn;
        conn = NULL;

        FdoPtr<FdoIConnection> connection = UnitTestUtil::GetConnection(UNSIGNED_SUFFIX, false);
        FdoPtr<FdoITransaction> featureTransaction = connection->BeginTransaction();
        FdoPtr<FdoIInsert> insertCommand = (FdoIInsert *) connection->CreateCommand(FdoCommandType_Insert);
        insertCommand->SetFeatureClassName(tableName);
        FdoPtr<FdoPropertyValueCollection> propertyValues = insertCommand->GetPropertyValues();

        FdoPtr<FdoDataValue> dataValue;
        dataValue = FdoDataValue::Create(L"1");
        FdoPtr<FdoPropertyValue> propertyValue = AddNewProperty( propertyValues, L"id");
        propertyValue->SetValue(dataValue);

        dataValue = FdoDataValue::Create(L"0");
        propertyValue = AddNewProperty( propertyValues, L"uint_column");
        propertyValue->SetValue(dataValue);

        FdoPtr<FdoIFeatureReader> reader = insertCommand->Execute();

        dataValue = FdoDataValue::Create(L"2");
        propertyValue = AddNewProperty( propertyValues, L"id");
        propertyValue->SetValue(dataValue);

        dataValue = FdoDataValue::Create(L"4294967295");
        propertyValue = AddNewProperty( propertyValues, L"uint_column");
        propertyValue->SetValue(dataValue);

        reader = insertCommand->Execute();

        featureTransaction->Commit();

        // check 
    	FdoPtr<FdoISelect> selectCmd = (FdoISelect *) connection->CreateCommand(FdoCommandType_Select);
	    selectCmd->SetFeatureClassName(tableName);

    	FdoPtr<FdoIFeatureReader> featureReader = selectCmd->Execute();
        FdoInt32 rowCount = 0;

        while ( featureReader->ReadNext() ) {
            rowCount++;

            switch ( featureReader->GetInt32(L"id") ) {
            case 1:
                CPPUNIT_ASSERT ( featureReader->GetInt64(L"uint_column") == 0 );
                break;

            case 2:
                CPPUNIT_ASSERT ( featureReader->GetInt64(L"uint_column") == 4294967295LL);
                break;
            }
        }
        CPPUNIT_ASSERT( rowCount == 2 );    
    }
    catch (FdoCommandException *ex)
    {
        if (conn)
        {
            conn->disconnect();
            delete conn;
        }
        UnitTestUtil::FailOnException(ex);
    }
    catch (FdoException *ex)
    {
        if (conn)
        {
            conn->disconnect();
            delete conn;
        }
        UnitTestUtil::FailOnException(ex);
    }
}