    LearningInfo(string data_infile, string network_infile, string child_name) {

        if (dataSet.ReadFile(data_infile.c_str()) != DSL_OKAY) {
            cout << "Cannot read data file... exiting." << endl;
            exit(1);
        }

        if (originalNet.ReadFile(network_infile.c_str(), DSL_XDSL_FORMAT) != DSL_OKAY) {
            cout << "Cannot read network... exiting." << endl;
            exit(1);
        }

        string err;
        if (dataSet.MatchNetwork(originalNet, matches, err) != DSL_OKAY) {
            cout << "Cannot match network... exiting." << endl;
            exit(1);
        }

        for(unsigned int i=0 ; i < matches.size() ; ++i) {
            matchNetToData[matches[i].node] = matches[i].column;
            matchDataToNet[matches[i].column] = matches[i].node;
        }

        childIdx = originalNet.FindNode(child_name.c_str());
        childNode = originalNet.GetNode(childIdx);

        if (childNode->Definition()->GetType() != (DSL_CHANCE | DSL_DISCRETE | DSL_NOISY_MAX) ) {
            cout << "Child should be a NoisyMAX... exiting" << endl;
            // ewentualnie zmienic na noisy-max ręcznie
            exit(1);
        }

        childMAXDefinition = new DSL_noisyMAX(*(childNode->Definition()));

        DSL_intArray &parents = originalNet.GetParents(childNode->Handle());
        numberOfParents = parents.NumItems();
        parentIndices = vector<int>(numberOfParents, 0);
        for(int i=0; i<numberOfParents; ++i)
            parentIndices[i] = parents[i];

        childDimension = childNode->Definition()->GetNumberOfOutcomes();
        parentDimensions = vector<int>(numberOfParents, 0);
        sumParentDimensions = 0;

        parentOutcomesStrengths = vector<DSL_intArray>(numberOfParents);
        minimalNumberOfParameters = 1; // minimal number of unique parameters to calculate (count leak right away)

        for(int parentIdx = 0 ; parentIdx < numberOfParents ; ++parentIdx) {
            DSL_node *parentNode = originalNet.GetNode(parentIndices[parentIdx]);
            sumParentDimensions += (parentDimensions[parentIdx] = parentNode->Definition()->GetNumberOfOutcomes()); //parent dimension is equal to the number of outcomes
            parentOutcomesStrengths[parentIdx] = childMAXDefinition->GetParentOutcomeStrengths(parentIdx);
            //for (int stateIdx=0 ; stateIdx < parentDimensions[parentIdx] ; ++stateIdx)
            //	cout << parentOutcomesStrengths[parentIdx][stateIdx] << " ";
            //cout << endl;
            minimalNumberOfParameters += parentDimensions[parentIdx] - 1; // (each parent dimension reduced by one) because we don't count distinguished states of parents
            distinguishedStates[parentIdx] = parentOutcomesStrengths[parentIdx][parentDimensions[parentIdx] - 1];
        }

        int sumOffset = 0;
        parameterRowOffset = vi1D(numberOfParents + 1, 0); // +1 so we know the offset for LEAK column
        for(int parentIdx = 0; parentIdx < numberOfParents ; ++parentIdx) {
            parameterRowOffset[parentIdx] = sumOffset;
            sumOffset += parentDimensions[parentIdx] - 1;
        }
        parameterRowOffset[numberOfParents] = sumOffset;

        parametersRowLength = minimalNumberOfParameters;
        minimalNumberOfParameters *= (childDimension - 1); // number of unique rows, last row is always 1.0 - sum

        //	DEBUG(minimalNumberOfParameters);
        //	DEBUG(childDimension);
        //	DEBUGV(parentDimensions);
        //	DEBUGV(parameterRowOffset);


        //for(int j=0; j< 7 ; ++j) {
        //	DSL_datasetVarInfo vi = ds.GetVariableInfo(j);
        //	cout << "discreete:" << vi.discrete << " id:" << vi.id << endl << " missingInt:" << vi.missingInt << " mF:" << vi.missingFloat << "snames:"<< endl;
        //	for(int i=0;i<vi.stateNames.size(); ++i)
        //		cout << vi.stateNames[i]<< " ";
        //	cout <<endl;
        //}

        //for(int i = 0; i < ds.GetNumberOfRecords(); ++i) {

        //	vector<int> row(ds.GetNumberOfVariables(), 0);
        //	int sum_ones = 0;

        //	for(int j = 0; j < ds.GetNumberOfVariables(); ++j) {
        //		sum_ones += (row[j] = ds.GetInt(j,i));
        //	}
        //}
        //vector<int> rd = ds.GetIntData(0);
        //cout <<"RDSize:"<<rd.size()<< endl;
        //for(int i=0;i<rd.size();++i) {
        //	cout << vi.stateNames[rd[i]] << endl;
        //}
        //
    }