void testCacheDbLoop( DbEnv* memEnv, ContextManager& cm, const ConfigParametersV& cp )
{
	cout<< "-- CacheDatabase Test: Running loop tests. --\n";

	CacheDatabase cache_db;
	cache_db.Initialize( memEnv, cp );

	int num_ofrecords = 1000000000;
	int number_of_partitions = cp.MemBDB.DatabaseConfigs.Partitions;
	LARGE_INTEGER begin, end, num_ticks;
	QueryPerformanceFrequency( &num_ticks );

	ContextStructure* c_struct, *c_struct2;
	cm.GetFreeContext( c_struct );
	cm.GetFreeContext( c_struct2 );

	CacheKey cacheKey( c_struct );
	CacheValue cacheValue( c_struct ), CacheRetrieveVal( c_struct2 );

	string strDzSeedName = "testLoopDz", strKey = "testLoopKey", strValue = "testLoopValue";
	Vdt dzName, key, Value; // = TCUtility::convertToVdt( strDzName );
	string sDZName, sKey, sValue;

	
	int partition_number;
	int dataRec_inserted = 0, dataRec_retrieved = 0;
	int md_inserted = 0, md_retrieved = 0;
	int dataRec_deleted = 0, md_deleted = 0;
	TCQValue qval(0, 0.0);
	char dirtybit = '1';
	char cleanbit = '0';
	bool quitloop = false;
	char* dataBuf = new char[sizeof_rec_in];
	
	std::cout << "Inserting records in Cache..." << std::endl;

	QueryPerformanceCounter( &begin );
	for(int i = 1; i < num_ofrecords && !quitloop; i++)
	{			
		sDZName = strDzSeedName + TCUtility::intToString(i);
		dzName = TCUtility::convertToVdt( sDZName );
		sKey = strKey + TCUtility::intToString(i);
		key = TCUtility::convertToVdt( sKey );
		
		sValue = strValue + TCUtility::intToString(i);
		memcpy(dataBuf, (char*)sValue.c_str(), sValue.length());
		Value.set_data(dataBuf);
		Value.set_size(sizeof_rec_in);
		//Value = TCUtility::convertToVdt( sValue );

		cacheKey.setValues( dzName, key );
		cacheValue.setDataRecValues( Value );

		partition_number = i % number_of_partitions;
		if( cache_db.InsertDataRec( cacheKey, cacheValue, partition_number) == 0 )
			dataRec_inserted++;
		else
		{
			std::cout << "Cache Data_rec is full" << std::endl;
			quitloop = true;
		}

		qval = (double)1 / (i * number_of_partitions);
		
		if(i/num_ofrecords == 0)
			cacheValue.setMDValues( dirtybit, qval );
		else
			cacheValue.setMDValues( cleanbit, qval );

		if( cache_db.InsertMDLookup( cacheKey, cacheValue, partition_number) == 0 )
			md_inserted++;
		else
		{
			std::cout << "Cache MD is full" << std::endl;
			quitloop = true;
		}
	}
	QueryPerformanceCounter( &end );
	cout << "Records Inserted in DataRec: " << dataRec_inserted << std::endl;
	cout << "Records Inserted in MD: " << md_inserted << std::endl;
	cout << "Time taken (seg): " << (double)(end.QuadPart - begin.QuadPart) / num_ticks.QuadPart << std::endl << std::endl;
	delete [] dataBuf;
	dataBuf = NULL;


	string sDZName2, sKey2;
	dataBuf = new char[sizeof_rec_out];
	//qval = 0.0;
	qval.setFraction(0.0);
	qval.setInt(0);
	TCQValue qvalr(0,0.0);
	quitloop = false;
	std::cout << "Retriving records from Cache..." << std::endl;
	char bit;
	string datar;
	
	QueryPerformanceCounter( &begin );
	for(int i = 1; i < num_ofrecords && !quitloop; i++)
	{
		sDZName2 = strDzSeedName + TCUtility::intToString(i);
		dzName = TCUtility::convertToVdt( sDZName2 );
		sKey2 = strKey + TCUtility::intToString(i);
		key = TCUtility::convertToVdt( sKey2 );
		
		sValue = strValue + TCUtility::intToString(i);
		
		Value.set_data(dataBuf);
		Value.set_size(sizeof_rec_out);
		
		cacheKey.setValues( dzName, key );
		CacheRetrieveVal.setDataRecValues( Value );

		partition_number = i % number_of_partitions;
		if( cache_db.GetDataRec( cacheKey, CacheRetrieveVal, partition_number) == 0 )
			dataRec_retrieved++;
		else
		{
			std::cout << "Records in Data_rec not Found" << std::endl;
			quitloop = true;
			break;
		}

		datar.clear();
		datar.insert(0, (char*)Value.get_data(), sValue.length());
		if(sValue.compare(datar) != 0)
			std::cout << "Record's value in Data_rec don't match" << std::endl;

		qval.setFraction( (double)1 / (i * number_of_partitions) );
		if( cache_db.GetMDLookup( cacheKey, CacheRetrieveVal, partition_number) == 0 )
			md_retrieved++;
		else
		{
			std::cout << "Records in MD not Found" << std::endl;
			quitloop = true;
			break;
		}
		qvalr = CacheRetrieveVal.getQValue();
		if(qval != qvalr)
			std::cout << "Wrong Qval Found" << std::endl;

		bit = CacheRetrieveVal.getDirtyBit();
		if(i/num_ofrecords == 0)
			dirtybit = '1';
		else
			dirtybit = '0';

		if(bit != dirtybit)
			std::cout << "Wrong DirtyBit Found" << std::endl;

	}
	QueryPerformanceCounter( &end );

	cout << "Records retrieved from DataRec: " << dataRec_retrieved << std::endl;
	cout << "Records retrieved from MD: " << md_retrieved << std::endl;
	cout << "Time taken (seg): " << (double)(end.QuadPart - begin.QuadPart) / num_ticks.QuadPart  << std::endl << std::endl;
	delete [] dataBuf;
	dataBuf = NULL;

	qval = 0.0;
	quitloop = false;
	//Deletes records
	QueryPerformanceCounter( &begin );
	for(int i = 1; i < num_ofrecords && !quitloop ; i++)
	{
		sDZName2 = strDzSeedName + TCUtility::intToString(i);
		dzName = TCUtility::convertToVdt( sDZName2 );
		sKey2 = strKey + TCUtility::intToString(i);
		key = TCUtility::convertToVdt( sKey2 );

		cacheKey.setValues( dzName, key );

		partition_number = i % number_of_partitions;
		if( cache_db.DeleteDataRec( cacheKey, partition_number) == 0 )
			dataRec_deleted++;
		else
		{
			std::cout << "Records in Data_rec not deleted" << std::endl;
			quitloop = true;
			break;
		}

		qval = (double)1 / (i * number_of_partitions);
		if( cache_db.DeleteMDLookup( cacheKey, partition_number) == 0 )
			md_deleted++;
		else
		{
			std::cout << "Records in MD not deleted" << std::endl;
			quitloop = true;
			break;
		}

	}

	QueryPerformanceCounter( &end );

	cout << "Records deleted from Data_Rec: " << dataRec_deleted << std::endl;
	cout << "Records deleted from MD: " << md_deleted << std::endl;
	cout << "Time taken (seg): " << (double)(end.QuadPart - begin.QuadPart) / num_ticks.QuadPart  << std::endl;

	cm.ReleaseContext( c_struct );
	cm.ReleaseContext( c_struct2 );
	
	
	cout<< "-- CacheDatabase Test: End of loop tests. --\n";
}