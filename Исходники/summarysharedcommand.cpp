int SummarySharedCommand::process(vector<SharedRAbundVector*> thisLookup, string sumFileName, string sumAllFileName) {
	try {
        vector< vector< vector<seqDist> > > calcDistsTotals;  //each iter, one for each calc, then each groupCombos dists. this will be used to make .dist files
        vector< vector<seqDist>  > calcDists; calcDists.resize(sumCalculators.size()); 		
        
        for (int thisIter = 0; thisIter < iters+1; thisIter++) {
            
            vector<SharedRAbundVector*> thisItersLookup = thisLookup;
            
            if (subsample && (thisIter != 0)) { //we want the summary results for the whole dataset, then the subsampling
                SubSample sample;
                vector<string> tempLabels; //dont need since we arent printing the sampled sharedRabunds
                
                //make copy of lookup so we don't get access violations
                vector<SharedRAbundVector*> newLookup;
                for (int k = 0; k < thisItersLookup.size(); k++) {
                    SharedRAbundVector* temp = new SharedRAbundVector();
                    temp->setLabel(thisItersLookup[k]->getLabel());
                    temp->setGroup(thisItersLookup[k]->getGroup());
                    newLookup.push_back(temp);
                }
                
                //for each bin
                for (int k = 0; k < thisItersLookup[0]->getNumBins(); k++) {
                    if (m->control_pressed) { for (int j = 0; j < newLookup.size(); j++) {  delete newLookup[j];  } return 0; }
                    for (int j = 0; j < thisItersLookup.size(); j++) { newLookup[j]->push_back(thisItersLookup[j]->getAbundance(k), thisItersLookup[j]->getGroup()); }
                }
                
                tempLabels = sample.getSample(newLookup, subsampleSize);
                thisItersLookup = newLookup;
            }
        
            
            if(processors == 1){
                driver(thisItersLookup, 0, numGroups, sumFileName+".temp", sumAllFileName+".temp", calcDists);
                m->appendFiles((sumFileName + ".temp"), sumFileName);
                m->mothurRemove((sumFileName + ".temp"));
                if (mult) {
                    m->appendFiles((sumAllFileName + ".temp"), sumAllFileName);
                    m->mothurRemove((sumAllFileName + ".temp"));
                }
            }else{
                
                int process = 1;
                vector<int> processIDS;
                
#if defined (__APPLE__) || (__MACH__) || (linux) || (__linux) || (__linux__) || (__unix__) || (__unix)
                //loop through and create all the processes you want
                while (process != processors) {
                    pid_t pid = fork();
                    
                    if (pid > 0) {
                        processIDS.push_back(pid); 
                        process++;
                    }else if (pid == 0){
                        driver(thisItersLookup, lines[process].start, lines[process].end, sumFileName + m->mothurGetpid(process) + ".temp", sumAllFileName + m->mothurGetpid(process) + ".temp", calcDists);
                        
                        //only do this if you want a distance file
                        if (createPhylip) {
                            string tempdistFileName = m->getRootName(m->getSimpleName(sumFileName)) + m->mothurGetpid(process) + ".dist";
                            ofstream outtemp;
                            m->openOutputFile(tempdistFileName, outtemp);
                            
                            for (int i = 0; i < calcDists.size(); i++) {
                                outtemp << calcDists[i].size() << endl;
                                
                                for (int j = 0; j < calcDists[i].size(); j++) {
                                    outtemp << calcDists[i][j].seq1 << '\t' << calcDists[i][j].seq2 << '\t' << calcDists[i][j].dist << endl;
                                }
                            }
                            outtemp.close();
                        }
                        
                        exit(0);
                    }else { 
                        m->mothurOut("[ERROR]: unable to spawn the necessary processes."); m->mothurOutEndLine(); 
                        for (int i = 0; i < processIDS.size(); i++) { kill (processIDS[i], SIGINT); }
                        exit(0);
                    }
                }
                
                //parent do your part
                driver(thisItersLookup, lines[0].start, lines[0].end, sumFileName + m->mothurGetpid(process) + ".temp", sumAllFileName + m->mothurGetpid(process) + ".temp", calcDists);
                m->appendFiles((sumFileName + m->mothurGetpid(process) + ".temp"), sumFileName);
                m->mothurRemove((sumFileName + m->mothurGetpid(process) + ".temp"));
                if (mult) { m->appendFiles((sumAllFileName + m->mothurGetpid(process) + ".temp"), sumAllFileName); }
                
                //force parent to wait until all the processes are done
                for (int i = 0; i < processIDS.size(); i++) {
                    int temp = processIDS[i];
                    wait(&temp);
                }
                
                for (int i = 0; i < processIDS.size(); i++) {
                    m->appendFiles((sumFileName + toString(processIDS[i]) + ".temp"), sumFileName);
                    m->mothurRemove((sumFileName + toString(processIDS[i]) + ".temp"));
                    if (mult) {	m->mothurRemove((sumAllFileName + toString(processIDS[i]) + ".temp"));	}
                    
                    if (createPhylip) {
                        string tempdistFileName = m->getRootName(m->getSimpleName(sumFileName)) + toString(processIDS[i]) +  ".dist";
                        ifstream intemp;
                        m->openInputFile(tempdistFileName, intemp);
                        
                        for (int k = 0; k < calcDists.size(); k++) {
                            int size = 0;
                            intemp >> size; m->gobble(intemp);
                            
                            for (int j = 0; j < size; j++) {
                                int seq1 = 0;
                                int seq2 = 0;
                                float dist = 1.0;
                                
                                intemp >> seq1 >> seq2 >> dist;   m->gobble(intemp);
                                
                                seqDist tempDist(seq1, seq2, dist);
                                calcDists[k].push_back(tempDist);
                            }
                        }
                        intemp.close();
                        m->mothurRemove(tempdistFileName);
                    }
                }
#else
                //////////////////////////////////////////////////////////////////////////////////////////////////////
                //Windows version shared memory, so be careful when passing variables through the summarySharedData struct. 
                //Above fork() will clone, so memory is separate, but that's not the case with windows, 
                //Taking advantage of shared memory to pass results vectors.
                //////////////////////////////////////////////////////////////////////////////////////////////////////
                
                vector<summarySharedData*> pDataArray; 
                DWORD   dwThreadIdArray[processors-1];
                HANDLE  hThreadArray[processors-1];
                
                //Create processor worker threads.
                for( int i=1; i<processors; i++ ){
                    
                    //make copy of lookup so we don't get access violations
                    vector<SharedRAbundVector*> newLookup;
                    for (int k = 0; k < thisLookup.size(); k++) {
                        SharedRAbundVector* temp = new SharedRAbundVector();
                        temp->setLabel(thisLookup[k]->getLabel());
                        temp->setGroup(thisLookup[k]->getGroup());
                        newLookup.push_back(temp);
                    }
                
                    
                    //for each bin
                    for (int k = 0; k < thisItersLookup[0]->getNumBins(); k++) {
                        if (m->control_pressed) { for (int j = 0; j < newLookup.size(); j++) {  delete newLookup[j];  } return 0; }
                        for (int j = 0; j < thisItersLookup.size(); j++) { newLookup[j]->push_back(thisItersLookup[j]->getAbundance(k), thisItersLookup[j]->getGroup()); }
                    }
                    
                    // Allocate memory for thread data.
                    summarySharedData* tempSum = new summarySharedData((sumFileName+toString(i)+".temp"), m, lines[i].start, lines[i].end, Estimators, newLookup);
                    pDataArray.push_back(tempSum);
                    processIDS.push_back(i);
                    
                    hThreadArray[i-1] = CreateThread(NULL, 0, MySummarySharedThreadFunction, pDataArray[i-1], 0, &dwThreadIdArray[i-1]);   
                }
                
                //parent do your part
                driver(thisItersLookup, lines[0].start, lines[0].end, sumFileName +"0.temp", sumAllFileName + "0.temp", calcDists);
                m->appendFiles((sumFileName + "0.temp"), sumFileName);
                m->mothurRemove((sumFileName + "0.temp"));
                if (mult) { m->appendFiles((sumAllFileName + "0.temp"), sumAllFileName); }
                
                //Wait until all threads have terminated.
                WaitForMultipleObjects(processors-1, hThreadArray, TRUE, INFINITE);
                
                //Close all thread handles and free memory allocations.
                for(int i=0; i < pDataArray.size(); i++){
                    if (pDataArray[i]->count != (pDataArray[i]->end-pDataArray[i]->start)) {
                        m->mothurOut("[ERROR]: process " + toString(i) + " only processed " + toString(pDataArray[i]->count) + " of " + toString(pDataArray[i]->end-pDataArray[i]->start) + " groups assigned to it, quitting. \n"); m->control_pressed = true; 
                    }
                    m->appendFiles((sumFileName + toString(processIDS[i]) + ".temp"), sumFileName);
                    m->mothurRemove((sumFileName + toString(processIDS[i]) + ".temp"));
                    
                    for (int j = 0; j < pDataArray[i]->thisLookup.size(); j++) {  delete pDataArray[i]->thisLookup[j];  }
                    
                    if (createPhylip) {
                        for (int k = 0; k < calcDists.size(); k++) {
                            int size = pDataArray[i]->calcDists[k].size();
                            for (int j = 0; j < size; j++) {    calcDists[k].push_back(pDataArray[i]->calcDists[k][j]);    }
                        }
                    }
                    
                    CloseHandle(hThreadArray[i]);
                    delete pDataArray[i];
                }
                
#endif
            }
            
            if (subsample && (thisIter != 0)) { //we want the summary results for the whole dataset, then the subsampling
                
                calcDistsTotals.push_back(calcDists); 
                //clean up memory
                for (int i = 0; i < thisItersLookup.size(); i++) { delete thisItersLookup[i]; }
                thisItersLookup.clear();
            }else {
                if (createPhylip) {
                    for (int i = 0; i < calcDists.size(); i++) {
                        if (m->control_pressed) { break; }
                        
                        //initialize matrix
                        vector< vector<double> > matrix; //square matrix to represent the distance
                        matrix.resize(thisLookup.size());
                        for (int k = 0; k < thisLookup.size(); k++) {  matrix[k].resize(thisLookup.size(), 0.0); }
                        
                        for (int j = 0; j < calcDists[i].size(); j++) {
                            int row = calcDists[i][j].seq1;
                            int column = calcDists[i][j].seq2;
                            double dist = calcDists[i][j].dist;
                            
                            matrix[row][column] = dist;
                            matrix[column][row] = dist;
                        }
                        
                        map<string, string> variables; 
                        variables["[filename]"] = outputDir + m->getRootName(m->getSimpleName(sharedfile));
                        variables["[calc]"] = sumCalculators[i]->getName();
                        variables["[distance]"] = thisLookup[0]->getLabel();
                        variables["[outputtag]"] = output;
                        variables["[tag2]"] = "";
                        string distFileName = getOutputFileName("phylip",variables);
                        outputNames.push_back(distFileName); outputTypes["phylip"].push_back(distFileName);
                        ofstream outDist;
                        m->openOutputFile(distFileName, outDist);
                        outDist.setf(ios::fixed, ios::floatfield); outDist.setf(ios::showpoint);
                        
                        printSims(outDist, matrix);
                        
                        outDist.close();
                    }
                }
            }
            for (int i = 0; i < calcDists.size(); i++) {  calcDists[i].clear(); }
		}

        if (iters != 0) {
            //we need to find the average distance and standard deviation for each groups distance
            vector< vector<seqDist>  > calcAverages = m->getAverages(calcDistsTotals);
            
            //find standard deviation
            vector< vector<seqDist>  > stdDev = m->getStandardDeviation(calcDistsTotals, calcAverages); 
            
            //print results
            for (int i = 0; i < calcDists.size(); i++) {
                vector< vector<double> > matrix; //square matrix to represent the distance
                matrix.resize(thisLookup.size());
                for (int k = 0; k < thisLookup.size(); k++) {  matrix[k].resize(thisLookup.size(), 0.0); }
                
                vector< vector<double> > stdmatrix; //square matrix to represent the stdDev
                stdmatrix.resize(thisLookup.size());
                for (int k = 0; k < thisLookup.size(); k++) {  stdmatrix[k].resize(thisLookup.size(), 0.0); }
                
                
                for (int j = 0; j < calcAverages[i].size(); j++) {
                    int row = calcAverages[i][j].seq1;
                    int column = calcAverages[i][j].seq2;
                    float dist = calcAverages[i][j].dist;
                    float stdDist = stdDev[i][j].dist;
                    
                    matrix[row][column] = dist;
                    matrix[column][row] = dist;
                    stdmatrix[row][column] = stdDist;
                    stdmatrix[column][row] = stdDist;
                }
                
                map<string, string> variables; 
                variables["[filename]"] = outputDir + m->getRootName(m->getSimpleName(sharedfile));
                variables["[calc]"] = sumCalculators[i]->getName();
                variables["[distance]"] = thisLookup[0]->getLabel();
                variables["[outputtag]"] = output;
                variables["[tag2]"] = "ave";
                string distFileName = getOutputFileName("phylip",variables);
                outputNames.push_back(distFileName); outputTypes["phylip"].push_back(distFileName);
                ofstream outAve;
                m->openOutputFile(distFileName, outAve);
                outAve.setf(ios::fixed, ios::floatfield); outAve.setf(ios::showpoint);
                
                printSims(outAve, matrix);
                
                outAve.close();
                
                variables["[tag2]"] = "std";
                distFileName = getOutputFileName("phylip",variables);
                outputNames.push_back(distFileName); outputTypes["phylip"].push_back(distFileName);
                ofstream outSTD;
                m->openOutputFile(distFileName, outSTD);
                outSTD.setf(ios::fixed, ios::floatfield); outSTD.setf(ios::showpoint);
                
                printSims(outSTD, stdmatrix);
                
                outSTD.close();
                
            }
        }
        
        return 0;
	}
	catch(exception& e) {
		m->errorOut(e, "SummarySharedCommand", "process");
		exit(1);
	}
}