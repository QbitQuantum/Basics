    void SoftCascadeLearner::run(const nor_utils::Args& args)
    {
        // load the arguments
        this->getArgs(args);
        
        //print cascade properties
        if (_verbose > 0) {
            cout    << "[+] Softcascade parameters :" << endl
                    << "\t --> target detection rate = " << _targetDetectionRate << endl
                    << "\t --> alpha (exp param) = " << _alphaExponentialParameter << endl
                    << "\t --> bootstrap rate = " << _bootstrapRate << endl
                    << endl;
        }
        

        // get the registered weak learner (type from name)
        BaseLearner* pWeakHypothesisSource = 
            BaseLearner::RegisteredLearners().getLearner(_baseLearnerName);
        // initialize learning options; normally it's done in the strong loop
        // also, here we do it for Product learners, so input data can be created
        pWeakHypothesisSource->initLearningOptions(args);

        // get the training input data, and load it

        InputData* pTrainingData = pWeakHypothesisSource->createInputData();
        pTrainingData->initOptions(args);
        pTrainingData->load(_trainFileName, IT_TRAIN, 5);

        InputData* pBootstrapData = NULL;
        if (!_bootstrapFileName.empty()) {
            pBootstrapData = pWeakHypothesisSource->createInputData();
            pBootstrapData->initOptions(args);
            pBootstrapData->load(_bootstrapFileName, IT_TRAIN, 5);
        }
        
        // get the testing input data, and load it
        InputData* pTestData = NULL;
        if ( !_testFileName.empty() )
        {
            pTestData = pWeakHypothesisSource->createInputData();
            pTestData->initOptions(args);
            pTestData->load(_testFileName, IT_TEST, 5);
        }

        Serialization ss(_shypFileName, false );
        ss.writeHeader(_baseLearnerName);
        
        
//        outputHeader();
        // The output information object
        OutputInfo* pOutInfo = NULL;

        if ( !_outputInfoFile.empty() ) 
        {
            pOutInfo = new OutputInfo(args, true);
            pOutInfo->setOutputList("sca", &args);
            
            pOutInfo->initialize(pTrainingData);
            
            if (pTestData)
                pOutInfo->initialize(pTestData);
            pOutInfo->outputHeader(pTrainingData->getClassMap(), true, true, false);
            pOutInfo->outputUserHeader("thresh");
            pOutInfo->headerEndLine();
        }
        
        
//        ofstream trainPosteriorsFile;
//        ofstream testPosteriorsFile;
        
        
        const NameMap& namemap = pTrainingData->getClassMap();
        _positiveLabelIndex = namemap.getIdxFromName(_positiveLabelName);

        // FIXME: output posteriors

//        OutputInfo* pTrainPosteriorsOut = NULL;
//        OutputInfo* pTestPosteriorsOut = NULL;
        
//        if (! _trainPosteriorsFileName.empty()) {
//            pTrainPosteriorsOut = new OutputInfo(_trainPosteriorsFileName, "pos", true);
//            pTrainPosteriorsOut->initialize(pTrainingData);
//            dynamic_cast<PosteriorsOutput*>( pTrainPosteriorsOut->getOutputInfoObject("pos") )->addClassIndex(_positiveLabelIndex );
//        }
        
//        if (! _testPosteriorsFileName.empty() && !_testFileName.empty() ) {
//            pTestPosteriorsOut = new OutputInfo(_testPosteriorsFileName, "pos", true);
//            pTestPosteriorsOut->initialize(pTestData);
//            dynamic_cast<PosteriorsOutput*>( pTestPosteriorsOut->getOutputInfoObject("pos") )->addClassIndex(_positiveLabelIndex );            
//        }
        
        const int numExamples = pTrainingData->getNumExamples();

        vector<BaseLearner*> inWeakHypotheses;
        
        if (_fullRun) {            
            // TODO : the full training is implementet, testing is needed
            AdaBoostMHLearner* sHypothesis = new AdaBoostMHLearner();
            sHypothesis->run(args, pTrainingData, _baseLearnerName, _numIterations, inWeakHypotheses );
            delete sHypothesis;
        }
        else { 
            
            cout << "[+] Loading uncalibrated shyp file... ";
            //read the shyp file of the trained classifier
            UnSerialization us;
            us.loadHypotheses(_unCalibratedShypFileName, inWeakHypotheses, pTrainingData);  
            if (_inShypLimit > 0 && _inShypLimit < inWeakHypotheses.size() ) {
                inWeakHypotheses.resize(_inShypLimit);
            }
            if (_numIterations > inWeakHypotheses.size()) {
                _numIterations = inWeakHypotheses.size();
            }
            cout << "weak hypotheses loaded, " << inWeakHypotheses.size() << " retained.\n";
        }
        
        // some initializations
        _foundHypotheses.resize(0);
        double faceRejectionFraction = 0.;
        double estimatedExecutionTime = 0.;
        vector<double> rejectionDistributionVector;

        _rejectionThresholds.resize(0);
        
        
        set<int> trainingIndices;
        for (int i = 0; i < numExamples; i++) {
            trainingIndices.insert(pTrainingData->getRawIndex(i) );
        }
        
        // init v_t (see the paper)
        initializeRejectionDistributionVector(_numIterations, rejectionDistributionVector);

        if (_verbose == 1)
            cout << "Learning in progress..." << endl;

        ///////////////////////////////////////////////////////////////////////
        // Starting the SoftCascade main loop
        ///////////////////////////////////////////////////////////////////////
        for (int t = 0; t < _numIterations; ++t)
        {
            if (_verbose > 0)
                cout << "--------------[ iteration " << (t+1) << " ]--------------" << endl;

            faceRejectionFraction += rejectionDistributionVector[t];
            
            cout << "[+] Face rejection tolerated : " << faceRejectionFraction << " | v[t] = " << rejectionDistributionVector[t] << endl;
            
            int numberOfNegatives = pTrainingData->getNumExamplesPerClass(1 - _positiveLabelIndex);
            
            //vector<BaseLearner*>::const_iterator whyIt;
            int selectedIndex = 0;
            AlphaReal bestGap = 0;
            vector<AlphaReal> posteriors;
            computePosteriors(pTrainingData, _foundHypotheses, posteriors, _positiveLabelIndex);
            
            //should use an iterator instead of i
            
            vector<BaseLearner*>::iterator whyIt;
            int i;
            for (i = 0, whyIt = inWeakHypotheses.begin(); whyIt != inWeakHypotheses.end(); ++whyIt, ++i) {
            
                vector<AlphaReal> temporaryPosteriors = posteriors;
                vector<BaseLearner*> temporaryWeakHyp = _foundHypotheses;
                temporaryWeakHyp.push_back(*whyIt);
                updatePosteriors(pTrainingData, *whyIt, temporaryPosteriors, _positiveLabelIndex);
                
                AlphaReal gap = computeSeparationSpan(pTrainingData, temporaryPosteriors, _positiveLabelIndex );

                if (gap > bestGap) {
                    bestGap = gap;
                    selectedIndex = i;
                }
            }
            
            BaseLearner* selectedWeakHypothesis = inWeakHypotheses[selectedIndex];
            
            cout << "[+] Rank of the selected weak hypothesis : " << selectedIndex << endl
                 << "\t ---> edge gap = " << bestGap << endl
                 << "\t ---> alpha = " << selectedWeakHypothesis->getAlpha() << endl;

            //update the stages
            _foundHypotheses.push_back(selectedWeakHypothesis);
            updatePosteriors(pTrainingData, selectedWeakHypothesis, posteriors, _positiveLabelIndex);
            
            double missesFraction;
            AlphaReal r = findBestRejectionThreshold(pTrainingData, posteriors, faceRejectionFraction, missesFraction);
            _rejectionThresholds.push_back(r);
            
            
            // update the output info object
            dynamic_cast<SoftCascadeOutput*>( pOutInfo->getOutputInfoObject("sca") )->appendRejectionThreshold(r);
            
            cout << "[+] Rejection threshold = " << r << endl;
            
            //some updates
            ss.appendHypothesisWithThreshold(t, selectedWeakHypothesis, r);
            faceRejectionFraction -= missesFraction;
            
            inWeakHypotheses.erase(inWeakHypotheses.begin() + selectedIndex);
            double whypCost = 1; //just in case there are different costs for each whyp
            estimatedExecutionTime += whypCost * numberOfNegatives;
            
            // output perf in file
            vector< vector< AlphaReal> > scores(0);
            _output << t + 1 << setw(_sepWidth + 1) << r << setw(_sepWidth);
            
            // update OutputInfo with the new whyp
//            updateOutputInfo(pOutInfo, pTrainingData, selectedWeakHypothesis);
//            if (pTestData) {
//                updateOutputInfo(pOutInfo, pTestData, selectedWeakHypothesis);
//            }
            

            // output the iteration results
            printOutputInfo(pOutInfo, t, pTrainingData, pTestData, selectedWeakHypothesis, r);
                        
//            if (pTrainPosteriorsOut) {
//                pTrainPosteriorsOut->setTable(pTrainingData, pOutInfo->getTable(pTrainingData));
//                pTrainPosteriorsOut->outputCustom(pTrainingData);
//            }
//
//            if (pTestPosteriorsOut) {
//                pTestPosteriorsOut->setTable(pTestData, pOutInfo->getTable(pTestData));
//                pTestPosteriorsOut->outputCustom(pTestData);
//            }
            
            
            int leftNegatives = filterDataset(pTrainingData, posteriors, r, trainingIndices);
            if (leftNegatives == 0) {
                cout << endl << "[+] No more negatives.\n";
                break;
            }
            
            if (_bootstrapRate != 0) {
                bootstrapTrainingSet(pTrainingData, pBootstrapData, trainingIndices);
            }

        }  // loop on iterations
        /////////////////////////////////////////////////////////

        // write the footer of the strong hypothesis file
        ss.writeFooter();

        // Free the two input data objects
        if (pTrainingData)
            delete pTrainingData;
        if (pBootstrapData) {
            delete pBootstrapData;
        }
        if (pTestData)
            delete pTestData;

        if (_verbose > 0)
            cout << "Learning completed." << endl;
    }