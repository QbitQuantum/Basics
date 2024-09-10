//*********************************************
//***	Test 5: Test some error conditions	***
bool HeapDriver::Test5()
{
    cout << "\n  Test 5: Test some error conditions\n";
    Status status = OK;
    Scan* scan = 0;
    RecordID rid;
	
	//	Open the heap file
    HeapFile f("file_1", status);
    if (status != OK)
        cerr << "*** Error opening heap file\n";
	
    if ( status == OK )
	{
        cout << "  - Try to change the size of a record\n";
        scan = f.OpenScan(status);
        if (status != OK)
            cerr << "*** Error opening scan\n";
	}

	//	Try to change the size of a record -- should fail
    if ( status == OK )
	{
        int len;
        Rec rec;
		len = sizeof(rec);
        status = scan->GetNext(rid, (char *)&rec, len);
        if ( status != OK )
            cerr << "*** Error reading first record\n";
        else
		{
            status = f.UpdateRecord( rid, (char*)&rec, len-1 );
            TestFailure( status, HEAPFILE, "Shortening a record" );
            if ( status == OK )
			{
                status = f.UpdateRecord( rid, (char*)&rec, len+1 );
                TestFailure( status, HEAPFILE, "Lengthening a record" );
			}
		}
	}
	
    delete scan;
	
	//	Try to insert a too long record -- should fail
    if ( status == OK )
	{
        cout << "  - Try to insert a record that's too long\n";
        char record[MINIBASE_PAGESIZE] = "";
        status = f.InsertRecord( record, MINIBASE_PAGESIZE, rid );
        TestFailure( status, HEAPFILE, "Inserting a too-long record" );
	}
	
    if ( status == OK )
        cout << "  Test 5 completed successfully.\n";
    return (status == OK);
}