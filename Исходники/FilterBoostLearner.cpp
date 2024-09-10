	void FilterBoostLearner::run(const nor_utils::Args& args)
	{
		// load the arguments
		this->getArgs(args);

		time_t startTime, currentTime;
		time(&startTime);

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

		const int numClasses = pTrainingData->getNumClasses();
		const int numExamples = pTrainingData->getNumExamples();
		
		//initialize the margins variable
		_margins.resize( numExamples );
		for( int i=0; i<numExamples; i++ )
		{
			_margins[i].resize( numClasses );
			fill( _margins[i].begin(), _margins[i].end(), 0.0 );
		}


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
			float constantEnergy = pConstantWeakHypothesis->run();

			pOutInfo = new OutputInfo(_outputInfoFile);
			pOutInfo->initialize(pTrainingData);

			updateMargins( pTrainingData, pConstantWeakHypothesis );

			if (pTestData)
				pOutInfo->initialize(pTestData);
			pOutInfo->outputHeader();

			pOutInfo->outputIteration(-1);
			pOutInfo->outputError(pTrainingData, pConstantWeakHypothesis);

			if (pTestData)
				pOutInfo->outputError(pTestData, pConstantWeakHypothesis);
			/*
			pOutInfo->outputMargins(pTrainingData, pConstantWeakHypothesis);
			
			pOutInfo->outputEdge(pTrainingData, pConstantWeakHypothesis);

			if (pTestData)
				pOutInfo->outputMargins(pTestData, pConstantWeakHypothesis);

			pOutInfo->outputMAE(pTrainingData);

			if (pTestData)
				pOutInfo->outputMAE(pTestData);
			*/
			pOutInfo->outputCurrentTime();

			pOutInfo->endLine();
			pOutInfo->initialize(pTrainingData);
			
			if (pTestData)
				pOutInfo->initialize(pTestData);
		}
		// reload the previously found weak learners if -resume is set. 
		// otherwise just return 0
		int startingIteration = resumeWeakLearners(pTrainingData);


		Serialization ss(_shypFileName, _isShypCompressed );
		ss.writeHeader(_baseLearnerName); // this must go after resumeProcess has been called

		// perform the resuming if necessary. If not it will just return
		resumeProcess(ss, pTrainingData, pTestData, pOutInfo);

		if (_verbose == 1)
			cout << "Learning in progress..." << endl;

		///////////////////////////////////////////////////////////////////////
		// Starting the AdaBoost main loop
		///////////////////////////////////////////////////////////////////////
		for (int t = startingIteration; t < _numIterations; ++t)
		{
			if (_verbose > 1)
				cout << "------- WORKING ON ITERATION " << (t+1) << " -------" << endl;

			filter( pTrainingData, (int)(_Cn * log(t+2.0)) );
			if ( pTrainingData->getNumExamples() < 2 ) 
			{
				filter( pTrainingData, (int)(_Cn * log(t+2.0)), false );
			}
			
			if (_verbose > 1)
			{
				cout << "--> Size of training data = " << pTrainingData->getNumExamples() << endl;
			}

			BaseLearner* pWeakHypothesis = pWeakHypothesisSource->create();
			pWeakHypothesis->initLearningOptions(args);
			//pTrainingData->clearIndexSet();
			pWeakHypothesis->setTrainingData(pTrainingData);
			float energy = pWeakHypothesis->run();

			BaseLearner* pConstantWeakHypothesis;
			if (_withConstantLearner) // check constant learner if user wants it
			{
				pConstantWeakHypothesis = pConstantWeakHypothesisSource->create() ;
				pConstantWeakHypothesis->initLearningOptions(args);
				pConstantWeakHypothesis->setTrainingData(pTrainingData);
				float constantEnergy = pConstantWeakHypothesis->run();
			}

			//estimate edge
			filter( pTrainingData, (int)(_Cn * log(t+2.0)), false );
			float edge = pWeakHypothesis->getEdge() / 2.0;

			if (_withConstantLearner) // check constant learner if user wants it
			{
				float constantEdge = pConstantWeakHypothesis->getEdge() / 2.0;
				if ( constantEdge > edge )
				{
					delete pWeakHypothesis;
					pWeakHypothesis = pConstantWeakHypothesis;
					edge = constantEdge;
				} else {
					delete pConstantWeakHypothesis;
				}
			}

			// calculate alpha
			float alpha = 0.0;
			alpha = 0.5 * log( ( 0.5 + edge ) / ( 0.5 - edge ) );
			pWeakHypothesis->setAlpha( alpha );

			if (_verbose > 1)
				cout << "Weak learner: " << pWeakHypothesis->getName()<< endl;
			// Output the step-by-step information
			pTrainingData->clearIndexSet();
			printOutputInfo(pOutInfo, t, pTrainingData, pTestData, pWeakHypothesis);

			// Updates the weights and returns the edge
			float gamma = updateWeights(pTrainingData, pWeakHypothesis);

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

			// update the margins
			updateMargins( pTrainingData, pWeakHypothesis );

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