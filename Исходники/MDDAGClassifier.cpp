// Returns the results into ptRes
void MDDAGClassifier::computeResults(InputData* pData, vector<BaseLearner*>& weakHypotheses,
                                     vector< ExampleResults* >& results, int numIterations)
{
    assert( !weakHypotheses.empty() );

    const int numClasses = pData->getNumClasses();
    const int numExamples = pData->getNumExamples();

    // Initialize the output info
    OutputInfo* pOutInfo = NULL;

    if ( !_outputInfoFile.empty() )
    {
        if ( _args.getNumValues("outputinfo") > 1 )
        {
            pOutInfo = new OutputInfo(_args);;
        }
        else
        {
            pOutInfo = new OutputInfo(_outputInfoFile, "e01hamauc", false);
        }

    }


    // Creating the results structures. See file Structures.h for the
    // PointResults structure
    results.clear();
    results.reserve(numExamples);
    for (int i = 0; i < numExamples; ++i)
        results.push_back( new ExampleResults(i, numClasses) );

    // iterator over all the weak hypotheses
    vector<BaseLearner*>::const_iterator whyIt;
    int t;

    if ( pOutInfo )
    {
        pOutInfo->initialize( pData );
        pOutInfo->outputHeader(pData->getClassMap(),
                               true, // output iterations
                               false, // output time
                               true // endline
                              );
    }

    // for every feature: 1..T
    for (whyIt = weakHypotheses.begin(), t = 0;
            whyIt != weakHypotheses.end() && t < numIterations; ++whyIt, ++t)
    {
        BaseLearner* currWeakHyp = *whyIt;
        AlphaReal alpha = currWeakHyp->getAlpha();

        // for every point
        for (int i = 0; i < numExamples; ++i)
        {
            // a reference for clarity and speed
            vector<AlphaReal>& currVotesVector = results[i]->getVotesVector();

            // for every class
            for (int l = 0; l < numClasses; ++l)
                currVotesVector[l] += alpha * currWeakHyp->classify(pData, i, l);
        }

        // if needed output the step-by-step information
        if ( pOutInfo )
        {
            pOutInfo->outputIteration(t);
            //				pOutInfo->outputError(pData, currWeakHyp);
            //				pOutInfo->outTPRFPR(pData);
            //pOutInfo->outputBalancedError(pData, currWeakHyp);
            //				if ( ( t % 1 ) == 0 ) {
            //					pOutInfo->outputROC(pData);
            //				}

            pOutInfo->outputCustom(pData, currWeakHyp);
            // Margins and edge requires an update of the weight,
            // therefore I keep them out for the moment
            //outInfo.outputMargins(pData, currWeakHyp);
            //outInfo.outputEdge(pData, currWeakHyp);
            pOutInfo->endLine();
        }
    }

    if (pOutInfo)
        delete pOutInfo;

}