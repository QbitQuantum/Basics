int PreClusterCommand::createProcessesGroups(string newFName, string newNName, string newMFile, vector<string> groups) {
	try {
		
		vector<int> processIDS;
		int process = 1;
		int num = 0;
		bool recalc = false;
        
		//sanity check
		if (groups.size() < processors) { processors = groups.size(); }
		
		//divide the groups between the processors
		vector<linePair> lines;
		int remainingPairs = groups.size();
        int startIndex = 0;
        for (int remainingProcessors = processors; remainingProcessors > 0; remainingProcessors--) {
            int numPairs = remainingPairs; //case for last processor
            if (remainingProcessors != 1) { numPairs = ceil(remainingPairs / remainingProcessors); }
            lines.push_back(linePair(startIndex, (startIndex+numPairs))); //startIndex, endIndex
            startIndex = startIndex + numPairs;
            remainingPairs = remainingPairs - numPairs;
        }
		
#if defined (__APPLE__) || (__MACH__) || (linux) || (__linux) || (__linux__) || (__unix__) || (__unix)		
		
		//loop through and create all the processes you want
		while (process != processors) {
			pid_t pid = fork();
			
			if (pid > 0) {
				processIDS.push_back(pid);  //create map from line number to pid so you can append files in correct order later
				process++;
			}else if (pid == 0){
                outputNames.clear();
				num = driverGroups(newFName + m->mothurGetpid(process) + ".temp", newNName + m->mothurGetpid(process) + ".temp", newMFile, lines[process].start, lines[process].end, groups);
                
                string tempFile = m->mothurGetpid(process) + ".outputNames.temp";
                ofstream outTemp;
                m->openOutputFile(tempFile, outTemp);
                
                outTemp << outputNames.size();
                for (int i = 0; i < outputNames.size(); i++) { outTemp << outputNames[i] << endl; }
                outTemp.close();
                
				exit(0);
			}else {
                m->mothurOut("[ERROR]: unable to spawn the number of processes you requested, reducing number to " + toString(process) + "\n"); processors = process; //successful fork()'s
                for (int i = 0; i < processIDS.size(); i++) { kill (processIDS[i], SIGINT); }
                recalc = true;
				break;
			}
		}
        
        if (recalc) {
            lines.clear();
            num = 0;
            processIDS.resize(0);
            process = 1;
            
            int remainingPairs = groups.size();
            int startIndex = 0;
            for (int remainingProcessors = processors; remainingProcessors > 0; remainingProcessors--) {
                int numPairs = remainingPairs; //case for last processor
                if (remainingProcessors != 1) { numPairs = ceil(remainingPairs / remainingProcessors); }
                lines.push_back(linePair(startIndex, (startIndex+numPairs))); //startIndex, endIndex
                startIndex = startIndex + numPairs;
                remainingPairs = remainingPairs - numPairs;
            }
            
            while (process != processors) {
                pid_t pid = fork();
                
                if (pid > 0) {
                    processIDS.push_back(pid);  //create map from line number to pid so you can append files in correct order later
                    process++;
                }else if (pid == 0){
                    outputNames.clear();
                    num = driverGroups(newFName + m->mothurGetpid(process) + ".temp", newNName + m->mothurGetpid(process) + ".temp", newMFile, lines[process].start, lines[process].end, groups);
                    
                    string tempFile = m->mothurGetpid(process) + ".outputNames.temp";
                    ofstream outTemp;
                    m->openOutputFile(tempFile, outTemp);
                    
                    outTemp << outputNames.size();
                    for (int i = 0; i < outputNames.size(); i++) { outTemp << outputNames[i] << endl; }
                    outTemp.close();
                    
                    exit(0);
                }else {
                    m->mothurOut("[ERROR]: unable to spawn the necessary processes."); m->mothurOutEndLine();
                    for (int i = 0; i < processIDS.size(); i++) { kill (processIDS[i], SIGINT); }
                    exit(0);
                }
            }
        }

		
		//do my part
		num = driverGroups(newFName, newNName, newMFile, lines[0].start, lines[0].end, groups);
		
		//force parent to wait until all the processes are done
		for (int i=0;i<processIDS.size();i++) { 
			int temp = processIDS[i];
			wait(&temp);
		}
        
        for (int i = 0; i < processIDS.size(); i++) {
            string tempFile = toString(processIDS[i]) +  ".outputNames.temp";
            ifstream intemp;
            m->openInputFile(tempFile, intemp);
            
            int num;
            intemp >> num;
            for (int k = 0; k < num; k++) {
                string name = "";
                intemp >> name; m->gobble(intemp);
                
                outputNames.push_back(name); outputTypes["map"].push_back(name);
            }
            intemp.close();
            m->mothurRemove(tempFile);
        }
#else
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//Windows version shared memory, so be careful when passing variables through the preClusterData struct. 
		//Above fork() will clone, so memory is separate, but that's not the case with windows, 
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		
		vector<preClusterData*> pDataArray; 
		DWORD   dwThreadIdArray[processors-1];
		HANDLE  hThreadArray[processors-1]; 
		
		//Create processor worker threads.
		for( int i=1; i<processors; i++ ){
			// Allocate memory for thread data.
			string extension = toString(i) + ".temp";
			
			preClusterData* tempPreCluster = new preClusterData(fastafile, namefile, groupfile, countfile, (newFName+extension), (newNName+extension), newMFile, groups, m, lines[i].start, lines[i].end, diffs, topdown, i);
			pDataArray.push_back(tempPreCluster);
			processIDS.push_back(i);
			
			//MySeqSumThreadFunction is in header. It must be global or static to work with the threads.
			//default security attributes, thread function name, argument to thread function, use default creation flags, returns the thread identifier
			hThreadArray[i-1] = CreateThread(NULL, 0, MyPreclusterThreadFunction, pDataArray[i-1], 0, &dwThreadIdArray[i-1]);   
		}
		
				
		//using the main process as a worker saves time and memory
		num = driverGroups(newFName, newNName, newMFile, lines[0].start, lines[0].end, groups);
		
		//Wait until all threads have terminated.
		WaitForMultipleObjects(processors-1, hThreadArray, TRUE, INFINITE);
		
		//Close all thread handles and free memory allocations.
		for(int i=0; i < pDataArray.size(); i++){
            if (pDataArray[i]->count != (pDataArray[i]->end-pDataArray[i]->start)) {
                m->mothurOut("[ERROR]: process " + toString(i) + " only processed " + toString(pDataArray[i]->count) + " of " + toString(pDataArray[i]->end-pDataArray[i]->start) + " groups assigned to it, quitting. \n"); m->control_pressed = true; 
            }
			for (int j = 0; j < pDataArray[i]->mapFileNames.size(); j++) {
				outputNames.push_back(pDataArray[i]->mapFileNames[j]); outputTypes["map"].push_back(pDataArray[i]->mapFileNames[j]); 
			}
			CloseHandle(hThreadArray[i]);
			delete pDataArray[i];
		}
		
#endif		
		
		//append output files
		for(int i=0;i<processIDS.size();i++){
			//newFName = m->getFullPathName(".\\" + newFName);
			//newNName = m->getFullPathName(".\\" + newNName);
			
			m->appendFiles((newFName + toString(processIDS[i]) + ".temp"), newFName);
			m->mothurRemove((newFName + toString(processIDS[i]) + ".temp"));
			
			m->appendFiles((newNName + toString(processIDS[i]) + ".temp"), newNName);
			m->mothurRemove((newNName + toString(processIDS[i]) + ".temp"));
		}
		
		return num;	
		
	}
	catch(exception& e) {
		m->errorOut(e, "PreClusterCommand", "createProcessesGroups");
		exit(1);
	}
}