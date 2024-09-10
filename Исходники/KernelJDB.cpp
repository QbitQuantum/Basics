//int _main(int argc, char** argv){
int _stdcall _init_test(bool create){
	if(create){
		createBaseMaster(&masterdb);

		CreateBase("base1", 256);
		JDB::CDB* db = NULL;//new JDB::CDB();
		////create base table
		std::vector<JDB::CDB*>::iterator base;
		for(base = bases.begin(); base != bases.end(); base++){
			strcmp("base1.jdb", (*base)->GetFName());
			db = *base;
		}
		JDB::CTable* soBased = db->CreateTable("BaseTable", NULL);//new JDB::CTable(-1, NULL, "BaseTable");
		JDB::CSysField* fldBased = new JDB::CSysField("Id",2,JDB::FIXED);
		soBased->CreateField(fldBased);

		//create table derived from baseTeabe
		JDB::CTable* so = db->CreateTable("MyTable", soBased);//new JDB::CTable(-1, soBased, "MyTable");

		JDB::CSysField* fld = new JDB::CSysField("MyName", 0, JDB::VARIABLE);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyName1", 0, JDB::VARIABLE);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyName2", 0, JDB::VARIABLE);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyName3", 0, JDB::VARIABLE);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyName4", 0, JDB::VARIABLE);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyName5", 0, JDB::VARIABLE);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyName6", 0, JDB::VARIABLE);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyName7", 0, JDB::VARIABLE);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyName8", 0, JDB::VARIABLE);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyIsDeleted", 0, JDB::FIXED);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyDataPage", 3, JDB::FIXED);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyStringsPage", 3, JDB::FIXED);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyBinPage", 3, JDB::FIXED);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyIsCrypted", 0, JDB::FIXED);
		so->CreateField(fld);
		fld = new JDB::CSysField("MyBaseSysObjectPtr", 2, JDB::FIXED);
		so->CreateField(fld);
		
		//create object
		int objCnt = 1024;
		int stringSize = 8;
		for(int i = 0; i < objCnt; i++){
			int pos = 0;
			
			char* buff = new char[stringSize];
			char* buff1 = new char[stringSize];
			char* buff2 = new char[stringSize];
			char* buff3 = new char[stringSize];
			for(pos = 0; pos < stringSize; pos += 8){
				memcpy(buff + pos, "01234567", (stringSize - pos) < 8 ? (stringSize - pos) : 8);
				memcpy(buff1 + pos, "abcdefjh", (stringSize - pos) < 8 ? (stringSize - pos) : 8);
				memcpy(buff2 + pos, "iklmnopr", (stringSize - pos) < 8 ? (stringSize - pos) : 8);
				memcpy(buff3 + pos, "stuwvxyz", (stringSize - pos) < 8 ? (stringSize - pos) : 8);
			}
	
			JDB::CDBObject* dbObject = new JDB::CDBObject(so,-1);
			// Set base fields
			unsigned int id = i;
			dbObject->SetValue("Id", &id, 0);
			// set self fields
			dbObject->SetValue("MyName", "MyObject", 9);
			dbObject->SetValue("MyName1", buff, stringSize);
			dbObject->SetValue("MyName2", buff1, stringSize);
			dbObject->SetValue("MyName3", buff2, stringSize);
			dbObject->SetValue("MyName4", buff3, stringSize);
			dbObject->SetValue("MyName5", buff, stringSize);
			dbObject->SetValue("MyName6", buff1, stringSize);
			dbObject->SetValue("MyName7", buff2, stringSize);
			dbObject->SetValue("MyName8", buff3, stringSize);
			unsigned char deleted = 0x33;
			dbObject->SetValue("MyIsDeleted", &deleted, 0);
			int64_t datapage = 0x3131313131313131;
			dbObject->SetValue("MyDataPage", &datapage, 0);
			int64_t stringsPage = 0x3030303030303030;//00000000;
			dbObject->SetValue("MyStringsPage",&stringsPage, 0);
			int64_t binPage = 0x3232323232323232;
			dbObject->SetValue("MyBinPage", &binPage, 0);
			unsigned char isCrypted = 0x34;
			dbObject->SetValue("MyIsCrypted", &isCrypted, 0);
			int baseSysObjectPtr = 0x35;
			dbObject->SetValue("MyBaseSysObjectPtr", &baseSysObjectPtr, 0);

			dbObject->Write(db);

			delete buff;
			delete buff1;
			delete buff2;
			delete buff3;

			delete dbObject;
		}
	}
	else{
		LoadBases();

		char* bi = NULL;
		int cnt = 0;
		bi = GetBasesInfo(bi,cnt);
		delete[] bi;


		std::vector<JDB::CDB*>::iterator base;
		for(base = bases.begin(); base != bases.end(); base++){
			std::vector<JDB::CDBObject*> * records;
			std::map<int,JDB::CTable*>::iterator table;// masterTable
			for(table = (*base)->masterTable.begin(); table != (*base)->masterTable.end(); table++){
				printf("TableName:%s\n", (*table).second->GetName());
				std::vector<const char*> * fldNames = NULL;
				fldNames = (*table).second->GetFieldNames(fldNames);
				std::vector<const char*>::iterator name;
				for(name = (*fldNames).begin(); name != (*fldNames).end(); name++){
					printf("fldName:%s\n",*name);
				}
				delete fldNames;
				printf("\n\n");

				std::vector<int64_t> recNums;
				recNums.push_back(0x00);
				records = (*table).second->ReadRecords(recNums,(*base));
			}
		}
	}
	printf("%s\n","werr");
	{
		JDB::CTable so(5, NULL, "MyObject");
	}
	printf("end\n");
	std::vector<JDB::CDB*>::iterator base;
	for(base = bases.begin(); base != bases.end(); base++){
		delete *base;
	}
	return 0;
};