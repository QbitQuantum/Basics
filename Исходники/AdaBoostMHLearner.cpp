	void AdaBoostMHLearner::run(const nor_utils::Args& args)
	{
		// load the arguments
		this->getArgs(args);

		// get the registered weak learner (type from name)
		BaseLearner* pWeakHypothesisSource = 
			BaseLearner::RegisteredLearners().getLearner(_baseLearnerName);
		// initialize learning options; normally it's done in the strong loop
		// also, here we do it for Product learners, so input data can be created
		pWeakHypothesisSource->initLearningOptions(args);

		BaseLearner* pConstantWeakHypothesisSource = 
			BaseLearner::RegisteredLearners().getLearner("ConstantLearner");

		// get the training input data, and load it

		InputData* pTrainingData = pWeakHypothesisSource->createInputData();
		pTrainingData->initOptions(args);
		pTrainingData->load(_trainFileName, IT_TRAIN, _verbose);
		
		// get the testing input data, and load it
		InputData* pTestData = NULL;
		if ( !_testFileName.empty() )
		{
			pTestData = pWeakHypothesisSource->createInputData();
			pTestData->initOptions(args);
			pTestData->load(_testFileName, IT_TEST, _verbose);
		}

		// The output information object
		OutputInfo* pOutInfo = NULL;


		if ( !_outputInfoFile.empty() ) 
		{
			// Baseline: constant classifier - goes into 0th iteration

			BaseLearner* pConstantWeakHypothesis = pConstantWeakHypothesisSource->create() ;
			pConstantWeakHypothesis->initLearningOptions(args);
			pConstantWeakHypothesis->setTrainingData(pTrainingData);
			AlphaReal constantEnergy = pConstantWeakHypothesis->run();

			//pOutInfo = new OutputInfo(_outputInfoFile);
            pOutInfo = new OutputInfo(args);
			pOutInfo->initialize(pTrainingData);

			if (pTestData)
				pOutInfo->initialize(pTestData);
			pOutInfo->outputHeader(pTrainingData->getClassMap());

			pOutInfo->outputIteration(-1);
            pOutInfo->outputCustom(pTrainingData, pConstantWeakHypothesis);
            
			if (pTestData != NULL)
            {
                pOutInfo->separator();
                pOutInfo->outputCustom(pTestData, pConstantWeakHypothesis);   
            }

			pOutInfo->outputCurrentTime();

			pOutInfo->endLine(); 
			pOutInfo->initialize(pTrainingData);

			if (pTestData)
				pOutInfo->initialize(pTestData);
		}
		//cout << "Before serialization" << endl;
		// reload the previously found weak learners if -resume is set. 
		// otherwise just return 0
		int startingIteration = resumeWeakLearners(pTrainingData);


		Serialization ss(_shypFileName, _isShypCompressed );
		ss.writeHeader(_baseLearnerName); // this must go after resumeProcess has been called

		// perform the resuming if necessary. If not it will just return
		resumeProcess(ss, pTrainingData, pTestData, pOutInfo);

		if (_verbose == 1)
			cout << "Learning in progress..." << endl;

		//I put here the starting time, but it may take very long time to load the saved model
		time_t startTime, currentTime;
		time(&startTime);

		///////////////////////////////////////////////////////////////////////
		// Starting the AdaBoost main loop
		///////////////////////////////////////////////////////////////////////
		for (int t = startingIteration; t < _numIterations; ++t)
		{
			if (_verbose > 1)
				cout << "------- WORKING ON ITERATION " << (t+1) << " -------" << endl;

			BaseLearner* pWeakHypothesis = pWeakHypothesisSource->create();
			pWeakHypothesis->initLearningOptions(args);
			//pTrainingData->clearIndexSet();

			pWeakHypothesis->setTrainingData(pTrainingData);
			
			AlphaReal energy = pWeakHypothesis->run();
			
			//float gamma = pWeakHypothesis->getEdge();
			//cout << gamma << endl;

			if ( (_withConstantLearner) || ( energy != energy ) ) // check constant learner if user wants it (if energi is nan, then we chose constant learner
			{
				BaseLearner* pConstantWeakHypothesis = pConstantWeakHypothesisSource->create() ;
				pConstantWeakHypothesis->initLearningOptions(args);
				pConstantWeakHypothesis->setTrainingData(pTrainingData);
				AlphaReal constantEnergy = pConstantWeakHypothesis->run();

				if ( (constantEnergy <= energy) || ( energy != energy ) ) {
					delete pWeakHypothesis;
					pWeakHypothesis = pConstantWeakHypothesis;
				}
			}

			if (_verbose > 1)
				cout << "Weak learner: " << pWeakHypothesis->getName()<< endl;
			// Output the step-by-step information
			printOutputInfo(pOutInfo, t, pTrainingData, pTestData, pWeakHypothesis);

			// Updates the weights and returns the edge
			AlphaReal gamma = updateWeights(pTrainingData, pWeakHypothesis);

			if (_verbose > 1)
			{
				cout << setprecision(5)
					<< "--> Alpha = " << pWeakHypothesis->getAlpha() << endl
					<< "--> Edge  = " << gamma << endl
					<< "--> Energy  = " << energy << endl
					//            << "--> ConstantEnergy  = " << constantEnergy << endl
					//            << "--> difference  = " << (energy - constantEnergy) << endl
					;
			}

			// If gamma <= theta the algorithm must stop.
			// If theta == 0 and gamma is 0, it means that the weak learner is no better than chance
			// and no further training is possible.
			if (gamma <= _theta)
			{
				if (_verbose > 0)
				{
					cout << "Can't train any further: edge = " << gamma 
						<< " (with and edge offset (theta)=" << _theta << ")" << endl;
				}

				//          delete pWeakHypothesis;
				//          break; 
			}

			// append the current weak learner to strong hypothesis file,
			// that is, serialize it.
			ss.appendHypothesis(t, pWeakHypothesis);

			// Add it to the internal list of weak hypotheses
			_foundHypotheses.push_back(pWeakHypothesis); 

			// check if the time limit has been reached
			if (_maxTime > 0)
			{
				time( &currentTime );
				float diff = difftime(currentTime, startTime); // difftime is in seconds
				diff /= 60; // = minutes

				if (diff > _maxTime)
				{
					if (_verbose > 0)
						cout << "Time limit of " << _maxTime 
						<< " minutes has been reached!" << endl;
					break;     
				}
			} // check for maxtime
			delete pWeakHypothesis;
		}  // loop on iterations
		/////////////////////////////////////////////////////////

		// write the footer of the strong hypothesis file
		ss.writeFooter();

		// write the weights of the instances if the name of weights file isn't empty
		printOutWeights( pTrainingData );


		// Free the two input data objects
		if (pTrainingData)
			delete pTrainingData;
		if (pTestData)
			delete pTestData;

		if (pOutInfo)
			delete pOutInfo;

		if (_verbose > 0)
			cout << "Learning completed." << endl;
	}