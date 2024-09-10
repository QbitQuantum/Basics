//--------------------------------------------------------------------
// JoinSpec::PrintRelation
// 
// Purpose :  Prints the relation represented by a JoinSpec.
// Input   :  filename  - The file to which to write the output. When NULL (default)
//                        output is written to the screen. 
// Output  :  None
// Return  :  None
//-------------------------------------------------------------------- 
void JoinSpec::PrintRelation(const char* filename) {
	Status s;
	Scan *scan = file->OpenScan(s);

	if (s != OK) {
		std::cerr << "Cannot open scan on HeapFile in PrintRelation."<< std::endl;
		return;
	}


	FILE* f;
	if(filename == NULL) {
		f = stdout;
	}
	else {
		f = fopen(filename, "w");
		if (f == NULL) {
			std::cerr << "Cannot open file " << filename << " for writing.\n";
			return;
		}
	}

	char* rec = new char[recLen];

	int len = recLen;
	RecordID rid;

	while(scan->GetNext(rid, rec, len) != DONE) {
		if(len != recLen) {
			std::cerr << "Unexpected record length in print method." << std::endl;
			return;
		}
		for(int i = 0; i < numOfAttr; i++) {
			fprintf(f, "%d ", *(((int*)(rec)) + i));
		}
		fprintf(f, "\n");
	}

	if(filename != NULL) {
		fclose(f);
	}

	delete [] rec;
}