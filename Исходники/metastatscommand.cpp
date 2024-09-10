int MetaStatsCommand::process(vector<SharedRAbundVector*>& thisLookUp){
	try {
		
		
				if(processors == 1){
					driver(0, namesOfGroupCombos.size(), thisLookUp);
				}else{
					int process = 1;
					vector<int> processIDS;
		#if defined (__APPLE__) || (__MACH__) || (linux) || (__linux) || (__linux__) || (__unix__) || (__unix)
					//loop through and create all the processes you want
					while (process != processors) {
						int pid = fork();
			
						if (pid > 0) {
							processIDS.push_back(pid);  //create map from line number to pid so you can append files in correct order later
							process++;
						}else if (pid == 0){
							driver(lines[process].start, lines[process].num, thisLookUp);
							exit(0);
						}else { 
							m->mothurOut("[ERROR]: unable to spawn the necessary processes."); m->mothurOutEndLine(); 
							for (int i = 0; i < processIDS.size(); i++) { kill (processIDS[i], SIGINT); }
							exit(0);
						}
					}
					
					//do my part
					driver(lines[0].start, lines[0].num, thisLookUp);
		
					//force parent to wait until all the processes are done
					for (int i=0;i<(processors-1);i++) { 
						int temp = processIDS[i];
						wait(&temp);
					}
        #else
                    
                    //////////////////////////////////////////////////////////////////////////////////////////////////////
                    //Windows version shared memory, so be careful when passing variables through the summarySharedData struct. 
                    //Above fork() will clone, so memory is separate, but that's not the case with windows, 
                    //Taking advantage of shared memory to pass results vectors.
                    //////////////////////////////////////////////////////////////////////////////////////////////////////
                    
                    vector<metastatsData*> pDataArray; 
                    DWORD   dwThreadIdArray[processors-1];
                    HANDLE  hThreadArray[processors-1]; 
                    
                    //Create processor worker threads.
                    for( int i=1; i<processors; i++ ){
                        
                        //make copy of lookup so we don't get access violations
                        vector<SharedRAbundVector*> newLookup;
                        vector<string> designMapGroups;
                        for (int k = 0; k < thisLookUp.size(); k++) {
                            SharedRAbundVector* temp = new SharedRAbundVector();
                            temp->setLabel(thisLookUp[k]->getLabel());
                            temp->setGroup(thisLookUp[k]->getGroup());
                            newLookup.push_back(temp);
                            designMapGroups.push_back(designMap->getGroup(thisLookUp[k]->getGroup()));
                        }
                        
                        //for each bin
                        for (int k = 0; k < thisLookUp[0]->getNumBins(); k++) {
                            if (m->control_pressed) { for (int j = 0; j < newLookup.size(); j++) {  delete newLookup[j];  } return 0; }
                            for (int j = 0; j < thisLookUp.size(); j++) { newLookup[j]->push_back(thisLookUp[j]->getAbundance(k), thisLookUp[j]->getGroup()); }
                        }
                        
                        // Allocate memory for thread data.
                        metastatsData* tempSum = new metastatsData(sharedfile, outputDir, m, lines[i].start, lines[i].num, namesOfGroupCombos, newLookup, designMapGroups, iters, threshold);
                        pDataArray.push_back(tempSum);
                        processIDS.push_back(i);
                        
                        hThreadArray[i-1] = CreateThread(NULL, 0, MyMetastatsThreadFunction, pDataArray[i-1], 0, &dwThreadIdArray[i-1]);   
                    }
                    
                    //do my part
					driver(lines[0].start, lines[0].num, thisLookUp);
                    
                    //Wait until all threads have terminated.
                    WaitForMultipleObjects(processors-1, hThreadArray, TRUE, INFINITE);
                    
                    //Close all thread handles and free memory allocations.
                    for(int i=0; i < pDataArray.size(); i++){
                        if (pDataArray[i]->count != (pDataArray[i]->num)) {
                            m->mothurOut("[ERROR]: process " + toString(i) + " only processed " + toString(pDataArray[i]->count) + " of " + toString(pDataArray[i]->num) + " groups assigned to it, quitting. \n"); m->control_pressed = true; 
                        }
                        for (int j = 0; j < pDataArray[i]->thisLookUp.size(); j++) {  delete pDataArray[i]->thisLookUp[j];  } 
                        for (int j = 0; j < pDataArray[i]->outputNames.size(); j++) {  
                            outputNames.push_back(pDataArray[i]->outputNames[j]);
                            outputTypes["metastats"].push_back(pDataArray[i]->outputNames[j]);
                        }
                                                
                        CloseHandle(hThreadArray[i]);
                        delete pDataArray[i];
                    }
        #endif

				}
		
		return 0;
		
	}
	catch(exception& e) {
		m->errorOut(e, "MetaStatsCommand", "process");
		exit(1);
	}
}