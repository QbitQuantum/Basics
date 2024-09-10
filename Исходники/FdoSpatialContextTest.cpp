void FdoSpatialContextTest::CreateTables( StaticConnection* staticConn, FdoStringP datastore )
{
    FdoSchemaManagerP sm = staticConn->CreateSchemaManager();
    FdoSmPhMgrP phMgr = sm->GetPhysicalSchema();
    FdoSmPhOwnerP owner = phMgr->FindOwner( datastore );

    FdoSmPhTableP table = owner->CreateTable( phMgr->GetDcDbObjectName(L"table1" ));
    FdoSmPhColumnP column = table->CreateColumnInt32( L"id", false );
    table->AddPkeyCol( column->GetName() );

    FdoSmPhScInfoP scinfo = UnitTestUtil::CreateScInfo( 4903, 0, 0, 10, 10, 0.001, 0.001 );
    column = table->CreateColumnGeom( L"geometry1", scinfo, true, false );
    
    scinfo = UnitTestUtil::CreateScInfo( 4903, 0, 0, 20, 20, 0.001, 0.001 );
    column = table->CreateColumnGeom( L"geometry2", scinfo, true, false );
   
    table = owner->CreateTable( phMgr->GetDcDbObjectName(L"table2" ));
    column = table->CreateColumnInt32( L"id", false );
    table->AddPkeyCol( column->GetName() );

    scinfo = UnitTestUtil::CreateScInfo( 4722, 0, 0, 10, 10, 0.001, 0.001 );
    column = table->CreateColumnGeom( L"geometry1", scinfo, true, false );
   
    scinfo = UnitTestUtil::CreateScInfo( 4216, 0, 0, 10, 10, 0.001, 0.001 );
    column = table->CreateColumnGeom( L"geometry2", scinfo, true, false );

    scinfo = UnitTestUtil::CreateScInfo( 4722, 0, 0, 10, 10, 0.001, 0.001 );
    column = table->CreateColumnGeom( L"geometry3", scinfo, true, false );

    owner->Commit();
}