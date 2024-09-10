// Tests the creating of unique constraints that are too large for 
// MySQL. Verifies that the MySQL provider properly truncates
// constraint columns to get the total size within the maximum allowed.
void MySqlSchemaMgrTests::testWideConstraint ()
{
    StaticConnection* conn = CreateStaticConnection();
    FdoPtr<FdoIConnection> fdoConn;
    FdoInt32 ix;

    try
    {
        char prvenv[100];
        FdoStringP providerName = conn->GetServiceName();
        sprintf( prvenv, "provider=%ls", (FdoString*) providerName );
#ifdef _WIN32
        _putenv( prvenv );
#else
        putenv( prvenv );
#endif

        // Sets the other env.
        UnitTestUtil::SetProvider( conn->GetServiceName() ); 

        printf( "\nOpening Connection ...\n" );

        conn->connect();

        FdoSchemaManagerP mgr = conn->CreateSchemaManager();

        FdoSmPhGrdMgrP phMgr = mgr->GetPhysicalSchema()->SmartCast<FdoSmPhGrdMgr>();

        FdoSmPhDatabaseP database = phMgr->GetDatabase();

        printf( "Predeleting schema ...\n" );

        FdoStringP datastore = phMgr->GetDcOwnerName(
            UnitTestUtil::GetEnviron("datastore", DB_NAME_SUFFIX)
        );

        FdoSmPhOwnerP owner = phMgr->FindOwner( datastore, L"", false );
        if ( owner ) {
            owner->SetElementState( FdoSchemaElementState_Deleted );
            owner->Commit();
        }

        printf( "Creating schema ...\n" );

        owner = database->CreateOwner(
            datastore, 
            false
        );
        owner->SetPassword( L"test" );

        owner->Commit();
        FdoInt32 charLen = (FdoInt32)(owner->SmartCast<FdoSmPhMySqlOwner>()->GetCharacterSet()->SmartCast<FdoSmPhMySqlCharacterSet>()->GetCharLen());

        // Table1 tests various column types and constraints 
        // with various numbers and sizes of columns.
        // Primary Keys, indexes and unique constraints are tested.

        FdoSmPhTableP table = owner->CreateTable( phMgr->GetDcDbObjectName(L"TABLE1" ));
        FdoSmPhColumnP column = table->CreateColumnInt32( L"ID", false );
        table->AddPkeyCol( column->GetName() );

        // Columns of various types (tested by adding to primary key) 
        column = table->CreateColumnBLOB( L"BLOB_COLUMN", true );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnChar( L"STRING_COLUMN", false, 50 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnSingle( L"SINGLE_COLUMN", true );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDouble( L"DOUBLE_COLUMN", true );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDecimal( L"DECIMAL_COLUMN", true, 65, 0 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnBool( L"BOOL_COLUMN", true );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnByte( L"BYTE_COLUMN", true );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnInt16( L"INT16_COLUMN", true );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnInt32( L"INT32_COLUMN", true );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnInt64( L"INT64_COLUMN", true );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDate( L"DATE_COLUMN", true );
        table->AddPkeyCol( column->GetName() );
        AddProviderColumns( table );
        column = table->GetColumns()->GetItem( L"BINARY_COLUMN" );
        table->AddPkeyCol( column->GetName() );
        column = table->GetColumns()->GetItem( L"MEDIUMBLOB_COLUMN" );
        column = table->GetColumns()->GetItem( L"TINYBLOB_COLUMN" );
        column = table->GetColumns()->GetItem( L"VARBINARY_COLUMN" );
        table->AddPkeyCol( column->GetName() );
        column = table->GetColumns()->GetItem( L"DATE2_COLUMN" );
        table->AddPkeyCol( column->GetName() );
        column = table->GetColumns()->GetItem( L"TIMESTAMP_COLUMN" );
        table->AddPkeyCol( column->GetName() );

        // Columns of various length.

        column = table->CreateColumnChar( L"STRING100000", false, 100000 );
        column = table->CreateColumnChar( L"STRING2000", false, 2000 );
        column = table->CreateColumnChar( L"STRING700_1", false, 700 );
        column = table->CreateColumnChar( L"STRING700_2", false, 700 );

        for ( ix = 0; ix < 10; ix++ ) {
            column = table->CreateColumnChar( 
                FdoStringP::Format(L"STRING300_%d", ix + 1),
                false,
                300 
            );
        }

        for ( ix = 0; ix < 10; ix++ ) {
            column = table->CreateColumnChar( 
                FdoStringP::Format(L"STRING100_%d", ix + 1),
                false,
                100 
            );
        }

        for ( ix = 0; ix < 10; ix++ ) {
            column = table->CreateColumnChar( 
                FdoStringP::Format(L"STRING40_%d", ix + 1),
                false,
                40 
            );
        }

        // Various unique constraints

        // One large (will be truncated) column, one small (not truncated)
        FdoSmPhColumnsP	ukeyColumns = new FdoSmPhColumnCollection();
	    table->GetUkeyColumns()->Add( ukeyColumns );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING100000" );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING100_1" );

        // Two large, one small. 
        ukeyColumns = new FdoSmPhColumnCollection();
	    table->GetUkeyColumns()->Add( ukeyColumns );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING2000" );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING700_1" );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING300_1" );

        table->Commit();

        // Three large, two small
        ukeyColumns = new FdoSmPhColumnCollection();
	    table->GetUkeyColumns()->Add( ukeyColumns );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING100000" );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING2000" );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING700_1" );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING100_3" );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING100_4" );

        // Constraint will maximum number of columns (16): 11 large, 5 small.
        ukeyColumns = new FdoSmPhColumnCollection();
	    table->GetUkeyColumns()->Add( ukeyColumns );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING2000" );

        for ( ix = 0; ix < 10; ix++ ) {
            table->AddUkeyCol( 
                table->GetUkeyColumns()->GetCount() - 1, 
                FdoStringP::Format(L"STRING300_%d", ix + 1)
            );
        }

        for ( ix = 0; ix < 4; ix++ ) {
            table->AddUkeyCol( 
                table->GetUkeyColumns()->GetCount() - 1, 
                FdoStringP::Format(L"STRING100_%d", ix + 1)
            );
        }

        for ( ix = 0; ix < 1; ix++ ) {
            table->AddUkeyCol( 
                table->GetUkeyColumns()->GetCount() - 1, 
                FdoStringP::Format(L"STRING40_%d", ix + 1)
            );
        }

        // No large columns, no truncation.
        // Tests columns whose size is over the initial truncation size but
        // under final truncation size.
        ukeyColumns = new FdoSmPhColumnCollection();
	    table->GetUkeyColumns()->Add( ukeyColumns );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING100_3" );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING100_4" );

        // No large columns, no truncation.
        // Tests columns whose size is under the initial truncation size.
        ukeyColumns = new FdoSmPhColumnCollection();
	    table->GetUkeyColumns()->Add( ukeyColumns );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING40_3" );
        table->AddUkeyCol( table->GetUkeyColumns()->GetCount() - 1, L"STRING40_4" );

        // Test an index.
        FdoSmPhIndexP index = table->CreateIndex(L"table1_ix1", true );
        index->GetColumns()->Add( FdoSmPhColumnP(table->GetColumns()->GetItem(L"STRING2000")) );
        index->GetColumns()->Add( FdoSmPhColumnP(table->GetColumns()->GetItem(L"STRING700_1")) );

        FdoStringP pkeyClause = table->GetAddPkeySql();

        FdoStringP expectedClause = FdoStringP::Format(
            L"constraint \"pk_table1\" primary key ( \"ID\", \"BLOB_COLUMN\"(%d), \"STRING_COLUMN\", \"SINGLE_COLUMN\", \"DOUBLE_COLUMN\", \"DECIMAL_COLUMN\", \"BOOL_COLUMN\", \"BYTE_COLUMN\", \"INT16_COLUMN\", \"INT32_COLUMN\", \"INT64_COLUMN\", \"DATE_COLUMN\", \"BINARY_COLUMN\", \"VARBINARY_COLUMN\", \"DATE2_COLUMN\", \"TIMESTAMP_COLUMN\" )",
            ( 680 - (charLen * 50))
        );

        // Verify that blob column got truncated to expected amount
        // (1000 - total size of other columns).
        CPPUNIT_ASSERT( pkeyClause ==  expectedClause );

        FdoStringP ukeyClause = table->GetAddUkeysSql();

        // Verify that all unique key columns got truncate to expected amounts.
        if ( charLen == 1 ) 
            CPPUNIT_ASSERT( ukeyClause == L"UNIQUE (\"AUTOINCREMENT_COLUMN\"), UNIQUE (\"STRING100000\"(760), \"STRING100_1\"), UNIQUE (\"STRING2000\"(350), \"STRING700_1\"(350), \"STRING300_1\"), UNIQUE (\"STRING100000\"(266), \"STRING2000\"(266), \"STRING700_1\"(266), \"STRING100_3\", \"STRING100_4\"), UNIQUE (\"STRING2000\"(64), \"STRING300_1\"(64), \"STRING300_2\"(64), \"STRING300_3\"(64), \"STRING300_4\"(64), \"STRING300_5\"(64), \"STRING300_6\"(64), \"STRING300_7\"(64), \"STRING300_8\"(64), \"STRING300_9\"(64), \"STRING300_10\"(64), \"STRING100_1\"(64), \"STRING100_2\"(64), \"STRING100_3\"(64), \"STRING100_4\"(64), \"STRING40_1\"), UNIQUE (\"STRING100_3\", \"STRING100_4\"), UNIQUE (\"STRING40_3\", \"STRING40_4\")" );

        // Table 2 tests a case where 3 constraint columns are 
        // over initial truncation limit, 2 are over the next limit
        // and only 1 over the final limit.
        // Later on we verify truncation by trying some data inserts.
        table = owner->CreateTable( phMgr->GetDcDbObjectName(L"TABLE2" ));
        column = table->CreateColumnChar( L"STRING2000", false, 2000 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnChar( L"STRING400", false, 400 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnChar( L"STRING100", false, 100 );
        table->AddPkeyCol( column->GetName() );

        pkeyClause = table->GetAddPkeySql();

        if ( charLen == 1 ) 
            CPPUNIT_ASSERT( pkeyClause == L"constraint \"pk_table2\" primary key ( \"STRING2000\"(500), \"STRING400\"(400), \"STRING100\" )" );

        // Calculating the size of MySql decimal columns is 
        // complicated. Table3 tests creating constraints
        // with decimal columns of various sizes
        table = owner->CreateTable( phMgr->GetDcDbObjectName(L"TABLE3" ));
        FdoSmPhMySqlTableP mysqlTable = table->SmartCast<FdoSmPhMySqlTable>();
        mysqlTable->SetStorageEngine( MySQLOvStorageEngineType_MyISAM );
        
        // Add a couple of large strings to verify that they
        // are truncated to the expected amount. This verifies
        // that the decimal column size calculations are 
        // correct (i.e. enough space was reserved for the 
        // decimal columns).
        column = table->CreateColumnChar( L"STRING1", false, 2000 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnChar( L"STRING2", false, 2000 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDecimal( L"DECIMAL1", true, 65, 0 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDecimal( L"DECIMAL2", true, 65, 10 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDecimal( L"DECIMAL3", true, 45, 0 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDecimal( L"DECIMAL4", true, 44, 0 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDecimal( L"DECIMAL5", true, 21, 12 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDecimal( L"DECIMAL6", true, 10, 5 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDecimal( L"DECIMAL7", true, 5, 0 );
        table->AddPkeyCol( column->GetName() );
        column = table->CreateColumnDecimal( L"DECIMAL8", true, 1, 0 );
        table->AddPkeyCol( column->GetName() );

        pkeyClause = table->GetAddPkeySql();
    
        if ( charLen == 1 ) 
            CPPUNIT_ASSERT( pkeyClause == L"constraint \"pk_table3\" primary key ( \"STRING1\"(440), \"STRING2\"(440), \"DECIMAL1\", \"DECIMAL2\", \"DECIMAL3\", \"DECIMAL4\", \"DECIMAL5\", \"DECIMAL6\", \"DECIMAL7\", \"DECIMAL8\" )" );
        
        database->Commit();

        if ( charLen == 1 ) {
            // Test column truncation by inserting some data values.
            wchar_t prefix500[500];
            wchar_t prefix400[400];
            wchar_t prefix100[100];

            // Fill in every character except the last 
            // non-truncated one for each constraint column.
            for ( ix = 0; ix < 499; ix++ ) 
                prefix500[ix] = 'a';
            for ( ix = 0; ix < 399; ix++ ) 
                prefix400[ix] = 'a';
            for ( ix = 0; ix < 99; ix++ ) 
                prefix100[ix] = 'a';

            prefix500[499] = 0;
            prefix400[399] = 0;
            prefix100[99] = 0;

            GdbiConnection* gdbiConn = phMgr->GetGdbiConnection();

            // Insert first object 
            gdbiConn->ExecuteNonQuery(
                (FdoString*) FdoStringP::Format( 
                    L"insert into table2 ( STRING2000, STRING400, STRING100 ) values ( '%ls', '%ls', '%ls' )",
                    (FdoString*) (FdoStringP(prefix500) + L"a"),
                    (FdoString*) (FdoStringP(prefix400) + L"a"),
                    (FdoString*) (FdoStringP(prefix100) + L"a")
                )
            );

            // Insert three more objects. In each case the truncated
            // key column values are identical exception for the 
            // last character of one of the columns.
            gdbiConn->ExecuteNonQuery(
                (FdoString*) FdoStringP::Format( 
                    L"insert into table2 ( STRING2000, STRING400, STRING100 ) values ( '%ls', '%ls', '%ls' )",
                    (FdoString*) (FdoStringP(prefix500) + L"b"),
                    (FdoString*) (FdoStringP(prefix400) + L"a"),
                    (FdoString*) (FdoStringP(prefix100) + L"a")
                )
            );

            gdbiConn->ExecuteNonQuery(
                (FdoString*) FdoStringP::Format( 
                    L"insert into table2 ( STRING2000, STRING400, STRING100 ) values ( '%ls', '%ls', '%ls' )",
                    (FdoString*) (FdoStringP(prefix500) + L"a"),
                    (FdoString*) (FdoStringP(prefix400) + L"b"),
                    (FdoString*) (FdoStringP(prefix100) + L"a")
                )
            );

            gdbiConn->ExecuteNonQuery(
                (FdoString*) FdoStringP::Format( 
                    L"insert into table2 ( STRING2000, STRING400, STRING100 ) values ( '%ls', '%ls', '%ls' )",
                    (FdoString*) (FdoStringP(prefix500) + L"a"),
                    (FdoString*) (FdoStringP(prefix400) + L"a"),
                    (FdoString*) (FdoStringP(prefix100) + L"b")
                )
            );

            bool duplicate = true;

            try {
                // try inserting a duplicate. The key column values are not duplicate
                // but the truncated values are.
                gdbiConn->ExecuteNonQuery(
                    (FdoString*) FdoStringP::Format( 
                        L"insert into table2 ( STRING2000, STRING400, STRING100 ) values ( '%ls', '%ls', '%ls' )",
                        (FdoString*) (FdoStringP(prefix500) + L"ab"),
                        (FdoString*) (FdoStringP(prefix400) + L"ab"),
                        (FdoString*) (FdoStringP(prefix100) + L"ab")
                    )
                );
            }
            catch ( FdoException* exc ) 
            {
                exc->Release();
                duplicate = false;
            }
            catch ( ... ) 
            {
                duplicate = false;
            }

            CPPUNIT_ASSERT( !duplicate );
        }

        conn->disconnect();

        delete conn;

        if ( charLen != 1 ) 
            CPPUNIT_FAIL ("Test appears to be Ok; However database character set is not Latin1 so truncation validation was skipped");

        printf( "Done\n" );
    }
    catch (FdoException* e ) 
    {
        UnitTestUtil::FailOnException(e);
    }
    catch (CppUnit::Exception exception)
    {
        throw exception;
    }
    catch (...)
    {
        CPPUNIT_FAIL ("unexpected exception encountered");
    }
}