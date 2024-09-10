EstOutput Unweighted::createProcesses(Tree* t, vector< vector<string> > namesOfGroupCombos, CountTable* ct) {
	try {
        int process = 1;
		vector<int> processIDS;
        bool recalc = false;
		
		EstOutput results;
#if defined (__APPLE__) || (__MACH__) || (linux) || (__linux) || (__linux__) || (__unix__) || (__unix)
		
		
		//loop through and create all the processes you want
		while (process != processors) {
			pid_t pid = fork();
			
			if (pid > 0) {
				processIDS.push_back(pid);  //create map from line number to pid so you can append files in correct order later
				process++;
			}else if (pid == 0){
				EstOutput myresults;
				myresults = driver(t, namesOfGroupCombos, lines[process].start, lines[process].num, ct);
				
				if (m->control_pressed) { exit(0); }
				
				//pass numSeqs to parent
				ofstream out;
				string tempFile = outputDir + m->mothurGetpid(process) + ".unweighted.results.temp";
				m->openOutputFile(tempFile, out);
				out << myresults.size() << endl;
				for (int i = 0; i < myresults.size(); i++) {  out << myresults[i] << '\t';  } out << endl;
				out.close();
				
				exit(0);
			}else { 
                m->mothurOut("[ERROR]: unable to spawn the number of processes you requested, reducing number to " + toString(process) + "\n"); processors = process;
                for (int i = 0; i < processIDS.size(); i++) { kill (processIDS[i], SIGINT); }
                //wait to die
                for (int i=0;i<processIDS.size();i++) {
                    int temp = processIDS[i];
                    wait(&temp);
                }
                m->control_pressed = false;
                for (int i=0;i<processIDS.size();i++) {
                    m->mothurRemove(outputDir + (toString(processIDS[i]) + ".unweighted.results.temp"));
                }
                recalc = true;
                break;
			}
		}
		
        if (recalc) {
            //test line, also set recalc to true.
            //for (int i = 0; i < processIDS.size(); i++) { kill (processIDS[i], SIGINT); } for (int i=0;i<processIDS.size();i++) { int temp = processIDS[i]; wait(&temp); } m->control_pressed = false;  for (int i=0;i<processIDS.size();i++) {m->mothurRemove(outputDir + (toString(processIDS[i]) + ".unweighted.results.temp"));}processors=3; m->mothurOut("[ERROR]: unable to spawn the number of processes you requested, reducing number to " + toString(processors) + "\n");
            
            //if the users enters no groups then give them the score of all groups
            int numGroups = m->getNumGroups();
            
            //calculate number of comparsions
            int numComp = 0;
            vector< vector<string> > namesOfGroupCombos;
            for (int r=0; r<numGroups; r++) {
                for (int l = 0; l < r; l++) {
                    numComp++;
                    vector<string> groups; groups.push_back((m->getGroups())[r]); groups.push_back((m->getGroups())[l]);
                    namesOfGroupCombos.push_back(groups);
                }
            }
            
            if (numComp != 1) {
                vector<string> groups;
                if (numGroups == 0) {
                    //get score for all users groups
                    for (int i = 0; i < (ct->getNamesOfGroups()).size(); i++) {
                        if ((ct->getNamesOfGroups())[i] != "xxx") {
                            groups.push_back((ct->getNamesOfGroups())[i]);
                        }
                    }
                    namesOfGroupCombos.push_back(groups);
                }else {
                    for (int i = 0; i < m->getNumGroups(); i++) {
                        groups.push_back((m->getGroups())[i]);
                    }
                    namesOfGroupCombos.push_back(groups);
                }
            }
            
            lines.clear();
            int remainingPairs = namesOfGroupCombos.size();
            int startIndex = 0;
            for (int remainingProcessors = processors; remainingProcessors > 0; remainingProcessors--) {
                int numPairs = remainingPairs; //case for last processor
                if (remainingProcessors != 1) { numPairs = ceil(remainingPairs / remainingProcessors); }
                lines.push_back(linePair(startIndex, numPairs)); //startIndex, numPairs
                startIndex = startIndex + numPairs;
                remainingPairs = remainingPairs - numPairs;
            }
            
            results.clear();
            processIDS.resize(0);
            process = 1;
            
            //loop through and create all the processes you want
            while (process != processors) {
                pid_t pid = fork();
                
                if (pid > 0) {
                    processIDS.push_back(pid);  //create map from line number to pid so you can append files in correct order later
                    process++;
                }else if (pid == 0){
                    EstOutput myresults;
                    myresults = driver(t, namesOfGroupCombos, lines[process].start, lines[process].num, ct);
                    
                    if (m->control_pressed) { exit(0); }
                    
                    //pass numSeqs to parent
                    ofstream out;
                    string tempFile = outputDir + m->mothurGetpid(process) + ".unweighted.results.temp";
                    m->openOutputFile(tempFile, out);
                    out << myresults.size() << endl;
                    for (int i = 0; i < myresults.size(); i++) {  out << myresults[i] << '\t';  } out << endl;
                    out.close();
                    
                    exit(0);
                }else { 
                    m->mothurOut("[ERROR]: unable to spawn the necessary processes."); m->mothurOutEndLine(); 
                    for (int i = 0; i < processIDS.size(); i++) { kill (processIDS[i], SIGINT); }
                    exit(0); 
                }
            }
        }
        
		results = driver(t, namesOfGroupCombos, lines[0].start, lines[0].num, ct);
		
		//force parent to wait until all the processes are done
		for (int i=0;i<(processors-1);i++) { 
			int temp = processIDS[i];
			wait(&temp);
		}
		
		if (m->control_pressed) { return results; }
		
		//get data created by processes
		for (int i=0;i<(processors-1);i++) { 
			ifstream in;
			string s = outputDir + toString(processIDS[i]) + ".unweighted.results.temp";
			m->openInputFile(s, in);
			
			//get quantiles
			if (!in.eof()) {
				int num;
				in >> num; m->gobble(in);
				
				if (m->control_pressed) { break; }
				
				double w; 
				for (int j = 0; j < num; j++) {
					in >> w;
					results.push_back(w);
				}
				m->gobble(in);
			}
			in.close();
			m->mothurRemove(s);
		}
#else
		//fill in functions
        vector<unweightedData*> pDataArray;
		DWORD   dwThreadIdArray[processors-1];
		HANDLE  hThreadArray[processors-1];
        vector<CountTable*> cts;
        vector<Tree*> trees;
		
		//Create processor worker threads.
		for( int i=1; i<processors; i++ ){
            CountTable* copyCount = new CountTable();
            copyCount->copy(ct);
            Tree* copyTree = new Tree(copyCount);
            copyTree->getCopy(t);
            
            cts.push_back(copyCount);
            trees.push_back(copyTree);
            
            unweightedData* tempweighted = new unweightedData(m, lines[i].start, lines[i].num, namesOfGroupCombos, copyTree, copyCount, includeRoot);
			pDataArray.push_back(tempweighted);
			processIDS.push_back(i);
            
			hThreadArray[i-1] = CreateThread(NULL, 0, MyUnWeightedThreadFunction, pDataArray[i-1], 0, &dwThreadIdArray[i-1]);
		}
		
		results = driver(t, namesOfGroupCombos, lines[0].start, lines[0].num, ct);
		
		//Wait until all threads have terminated.
		WaitForMultipleObjects(processors-1, hThreadArray, TRUE, INFINITE);
		
		//Close all thread handles and free memory allocations.
		for(int i=0; i < pDataArray.size(); i++){
            for (int j = 0; j < pDataArray[i]->results.size(); j++) {  results.push_back(pDataArray[i]->results[j]);  }
			delete cts[i];
            delete trees[i];
			CloseHandle(hThreadArray[i]);
			delete pDataArray[i];
		}

#endif	
        return results;
	}