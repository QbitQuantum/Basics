int main(int argc, char* argv[]) 
{


	Status status = client::initialize();
    if ( !status.isOK() ) {
        std::cout << "failed to initialize the mongo client driver: " << status.toString() << endl;
        return EXIT_FAILURE;
    }

    const char *port = "27017";

    try {
        cout << "connecting to localhost..." << endl;
        DBConnection.connect(string("localhost:") + port);
        cout << "connected ok" << endl;

		string tracePath;
		const char* defaultTracePath = "/home/vladimir/Desktop/vlad-trace/traces.otf2";
		//const char* defaultTracePath = "/home/vladimir/Dicertation/otf2_trace/traces.otf2";
		//const char* defaultTracePath = "/home/vladimir/Desktop/qgen10-trace/traces.otf2";
		//const char* defaultTracePath = "/home/vladimir/tests/mpi_isend/scorep-20150416_1732_2789913328919/traces.otf2";

		if (argc != 2)
			tracePath = defaultTracePath;
		else
		{
			ifstream in;
			in.open(argv[1], ios::in);
			in >> tracePath;
			in.close();
		}

		OTF2_Reader* reader = OTF2_Reader_Open(tracePath.c_str());

		uint64_t tid_temp = 0; 
	    OTF2_Reader_GetTraceId (reader, &tid_temp);

	    // get procs number TODO
	    uint64_t numProcesses = 0;
	    OTF2_Reader_GetNumberOfLocations(reader, &numProcesses);

	    if ( numProcesses == 0 ) {
	        std::cout << "Something wrong with processes number" << endl;
	        return EXIT_FAILURE;
	    }

	    NumProcesses = numProcesses;

	    BeginTimes = new uint64_t[numProcesses];

	    for(int i = 0; i < numProcesses; i++){
	    	BeginTimes[i] = 0;
	    }

	   // SendTo = new int[numProcesses];

	    //for(int i = 0; i < numProcesses; i++){
	    //	SendTo[i] = -1;
	    //}


	    SendLength = new long long int[numProcesses];

	    for(int i = 0; i < numProcesses; i++){
	    	SendLength[i] = 0;
	    }

	    //RecvFrom = new int[numProcesses];

	    //for(int i = 0; i < numProcesses; i++){
	    //	RecvFrom[i] = -1;
	    //}

	    RecvLength = new long long int[numProcesses];

	    for(int i = 0; i < numProcesses; i++){
	    	RecvLength[i] = 0;
	    }

	    Root = new int[numProcesses];

	    for(int i = 0; i < numProcesses; i++){
	    	Root[i] = -1;
	    }

	    RegionNames = new int[numProcesses];
	    for(int i = 0; i < numProcesses; i++){
	    	RegionNames[i] = -1;
	    }

	    IsPointEvent = new bool[numProcesses];

	    for(int i = 0; i < numProcesses; i++){
	    	IsPointEvent[i] = 0;
	    }

	    IsCommEvent = new bool[numProcesses];

	    for(int i = 0; i < numProcesses; i++){
	    	IsCommEvent[i] = 0;
	    }





		//Point_SendTime = new long long int[numProcesses * numProcesses];
	    //for(int i = 0; i < numProcesses * numProcesses; i++){
	    //	Point_SendTime[i] = -1;
	    //}

	    //Point_SendTime = new long long int[numProcesses * numProcesses];
	    for(int i = 0; i < numProcesses * numProcesses; i++){
	    	//Point_SendTime[i] = -1;
	    	Point_SendTime.push_back(vector<long long int>());
	    }

	    for(int i = 0; i < numProcesses * numProcesses; i++){
	    	//Point_SendTime[i] = -1;
	    	Point_SendComm.push_back(vector<int>());
	    }

	    for(int i = 0; i < numProcesses * numProcesses; i++){
	    	//Point_SendTime[i] = -1;
	    	Point_SendTag.push_back(vector<int>());
	    }

	    for(int i = 0; i < numProcesses * numProcesses; i++){
	    	//Point_SendTime[i] = -1;
	    	Point_SendLength.push_back(vector<long long int>());
	    }






	    cout << tid_temp << endl;

	    char *buff;
	    buff = (char*) malloc (64);
	    sprintf(buff , "%" PRIx64, tid_temp);
		TraceId = string(buff);
		free(buff);

		auto_ptr<DBClientCursor> cursor = DBConnection.query("Otf2Data.TraceIds",  Query("{TraceId: \"" + TraceId + "\", Status: \"done\"}"));
		if(cursor->more()){
			cout << "Трасса с таким id уже сществует в БД" << endl;
		}
		else{
			DBConnection.remove("Otf2Data.Events", Query("{TraceId: \"" + TraceId + "\"}"));


			DBConnection.remove("Otf2Data.PointOperations", Query("{TraceId: \"" + TraceId + "\"}"));

			OTF2_GlobalDefReader* global_def_reader = OTF2_Reader_GetGlobalDefReader(reader);
			// creating global definition callbacks handle
			OTF2_GlobalDefReaderCallbacks* global_def_callbacks = OTF2_GlobalDefReaderCallbacks_New();
			// setting global definition reader callbacks to handle



			// получаем все строки
			OTF2_GlobalDefReaderCallbacks_SetStringCallback( global_def_callbacks, print_global_def_string );


			// получаем названия регионов 
			OTF2_GlobalDefReaderCallbacks_SetRegionCallback( global_def_callbacks, print_global_def_region );


			OTF2_GlobalDefReaderCallbacks_SetLocationCallback(global_def_callbacks, &GlobDefLocation_Register);

			//OTF2_GlobalDefReaderCallbacks_SetCommCallback (global_def_callbacks, &GlobDefCommunicator_Register);
			//OTF2_GlobalDefReaderCallbacks_SetGroupCallback(global_def_callbacks, &GlobDefGroup_Register);
			// registering callbacks and deleting callbacks handle
			OTF2_Reader_RegisterGlobalDefCallbacks(reader, global_def_reader, global_def_callbacks, reader);
			OTF2_GlobalDefReaderCallbacks_Delete( global_def_callbacks );

			// reading all global definitions
			uint64_t definitions_read = 0;
			OTF2_Reader_ReadAllGlobalDefinitions( reader, global_def_reader, &definitions_read );
			printf("Definitions_read = %"PRIu64"\n", definitions_read);
			
			// DEFINITIONS READING END
			
			cout << "numProcesses = " << numProcesses << endl; 


			// EVENTS READING START
			
			OTF2_GlobalEvtReader* global_evt_reader = OTF2_Reader_GetGlobalEvtReader(reader);
			// creating global event callbacks handle
			OTF2_GlobalEvtReaderCallbacks* event_callbacks = OTF2_GlobalEvtReaderCallbacks_New();
			// setting global event reader callbacks to handle

			OTF2_GlobalEvtReaderCallbacks_SetEnterCallback( event_callbacks, &EnterCallback);
			OTF2_GlobalEvtReaderCallbacks_SetLeaveCallback( event_callbacks, &LeaveCallback);

			
			OTF2_GlobalEvtReaderCallbacks_SetMpiSendCallback(event_callbacks, &MPI_Send_print);
			OTF2_GlobalEvtReaderCallbacks_SetMpiIsendCallback(event_callbacks, &MPI_Isend_print);



			OTF2_GlobalEvtReaderCallbacks_SetMpiRecvCallback(event_callbacks, &MPI_Recv_print);
			OTF2_GlobalEvtReaderCallbacks_SetMpiIrecvCallback(event_callbacks, &MPI_Irecv_print);



			//OTF2_GlobalEvtReaderCallbacks_SetMpiCollectiveBeginCallback(event_callbacks, &MPI_CollectiveBegin_print);

			OTF2_GlobalEvtReaderCallbacks_SetMpiCollectiveEndCallback(event_callbacks, &MPI_CollectiveEnd_print);

			
			// registering callbacks and deleting callbacks handle
			OTF2_Reader_RegisterGlobalEvtCallbacks(reader, global_evt_reader, event_callbacks, NULL);
			OTF2_GlobalEvtReaderCallbacks_Delete(event_callbacks);

			// reading all global events
			uint64_t events_read = 0;
			OTF2_Reader_ReadAllGlobalEvents(reader, global_evt_reader, &events_read);
			//printf("Events_read = %"PRIu64"\n", events_read);
			

			OTF2_Reader_Close( reader );

			cout << "Events started at " << startTime << endl;
			cout << "Events ended at " << endTime << endl;

			long long int num1 = numProcesses;

			DBConnection.insert("Otf2Data.TraceIds", BSON( "TraceId" << TraceId << "Status" << "done" << "NumberOfLocations" << num1));

			cout << "getlasterror returns: \"" << DBConnection.getLastError() << '"' << endl;

			cout << "Inserting successfully done! " << endl;
		}



		delete [] BeginTimes;
		delete [] IsPointEvent;

		delete [] IsCommEvent;

		delete [] RegionNames;
		//delete [] SendTo;
		//delete [] RecvFrom;

		delete [] SendLength;
		delete [] RecvLength;
		delete [] Root;

		//delete [] Point_SendTime;
		//delete [] Point_SendComm;
		//delete [] Point_SendTag;
		//delete [] Point_SendLength;


		
    } 
    catch(DBException& e) { 
        cout << "caught DBException " << e.toString() << endl;
        return EXIT_FAILURE;
    }






	return EXIT_SUCCESS;
}