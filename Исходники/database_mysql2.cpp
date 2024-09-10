int InsertServerPrerequisiteForMessageType(int msgType, vector<string> * v){
	char query[200];
	char * fixedInsertStr;
	unsigned int len;
	int holder;
	char * cTemp;
	MYSQL * conn;

	if(WaitForSingleObject(mysqlMutex, INFINITE) != WAIT_OBJECT_0){
		printf("InsertServerPrerequisiteForMessageType: Couldn't acquire mutex. Returning\n");
		return GENERIC_ERROR;
	}

	conn = OpenDatabaseConnection(gffServerDBName);
	if(conn == NULL){
		printf("InsertServerPrerequisiteForMessageType: OpenDatabaseConnection(gffServerDBName) failed\n");
		v->clear();
		return ReleaseMutexAndReturnError(mysqlMutex, GENERIC_ERROR);
	}

	//For each host to measure in the vector
	for(unsigned int i=0; i < v->size(); i++){
		string temp = v->at(i);
		cTemp = (char *)temp.c_str();

		fixedInsertStr = "INSERT INTO TableVerificationPrerequisiteModules VALUES(NULL,%i,'%s')";
		len = sprintf_s(query, 200, fixedInsertStr, msgType, cTemp);

		//////////////////////////////////
		if(0 != mysql_real_query(conn, query, len)){
			holder = CheckError(conn,mysql_errno(conn));
			
			// if error code is 1062, the entry already exists, so it's ok
			if(holder != 1062){
				CloseDatabaseConnection(conn);
				v->clear();
				return ReleaseMutexAndReturnError(mysqlMutex, holder);
			}
		}

	}
	CloseDatabaseConnection(conn);
	v->clear();
	//////////////////////////////////
	if(!ReleaseMutex(mysqlMutex)){
		printf("InsertServerPrerequisiteForMessageType: Couldn't release mutex. Returning\n");
		return GENERIC_ERROR;
	}
	return GENERIC_SUCCESS;
}