int PointFloatShapeFeatureExtractor::extractFeatures(const LTKTraceGroup& inTraceGroup,
                                   vector<LTKShapeFeaturePtr>& outFeatureVec)
{
    LOG( LTKLogger::LTK_LOGLEVEL_DEBUG) << "Entering " <<
        "PointFloatShapeFeatureExtractor::extractFeatures()" << endl;
    
    PointFloatShapeFeature *featurePtr = NULL;
	float x,y,deltax;
	int numPoints=0;						// number of pts
	int count=0;
	int currentStrokeSize;
	float sintheta, costheta,sqsum;
	int i;

    int numberOfTraces = inTraceGroup.getNumTraces();

    if (numberOfTraces == 0 )
    {
        LOG( LTKLogger::LTK_LOGLEVEL_ERR) << "Error: " << 
            EEMPTY_TRACE_GROUP << " : " << getErrorMessage(EEMPTY_TRACE_GROUP)<<
            " PointFloatShapeFeatureExtractor::extractFeatures" <<endl;
        
        LTKReturnError(EEMPTY_TRACE_GROUP);
    }
    
	LTKTraceVector allTraces = inTraceGroup.getAllTraces();
	LTKTraceVector::iterator traceIter = allTraces.begin();
	LTKTraceVector::iterator traceEnd = allTraces.end();


	//***CONCATENTATING THE STROKES***
	for (; traceIter != traceEnd ; ++traceIter)
	{
		floatVector tempxVec, tempyVec;
		
		(*traceIter).getChannelValues("X", tempxVec);

		(*traceIter).getChannelValues("Y", tempyVec);

		// Number of points in the stroke
		numPoints = numPoints + tempxVec.size(); 
	}	

	//***THE CONCATENATED FULL STROKE***
	floatVector xVec(numPoints);
	floatVector yVec(numPoints);	


	traceIter = allTraces.begin();
	traceEnd  = allTraces.end();

	boolVector penUp;
	// Add the penUp here	
	for (; traceIter != traceEnd ; ++traceIter)
	{
		floatVector tempxVec, tempyVec;
		
		(*traceIter).getChannelValues("X", tempxVec);

		(*traceIter).getChannelValues("Y", tempyVec);

		currentStrokeSize = tempxVec.size();

        if (currentStrokeSize == 0)
        {
            LOG( LTKLogger::LTK_LOGLEVEL_ERR) << "Error: " << 
            EEMPTY_TRACE << " : " << getErrorMessage(EEMPTY_TRACE) <<
            " PointFloatShapeFeatureExtractor::extractFeatures" <<endl;
            
            LTKReturnError(EEMPTY_TRACE);
        }
        
		for( int point=0; point < currentStrokeSize ; point++ )
		{
			xVec[count] = tempxVec[point];
			yVec[count] = tempyVec[point];
			count++;
            
			if(point == currentStrokeSize - 1 )
            {         
				penUp.push_back(true);
            }
			else
            {         
				penUp.push_back(false);
            }
		}	

	}
	//***CONCATENTATING THE STROKES***

	vector<float> theta(numPoints);
	vector<float> delta_x(numPoints-1);
	vector<float> delta_y(numPoints-1);

	for(i=0; i<numPoints-1; ++i)
	{  
		delta_x[i]=xVec[i+1]-xVec[i];
		delta_y[i]=yVec[i+1]-yVec[i];

	}

	//Add the controlInfo here
	sqsum = sqrt( pow(xVec[0],2)+ pow(yVec[0],2))+ EPS;
    
	sintheta = (1+yVec[0]/sqsum)*PREPROC_DEF_NORMALIZEDSIZE/2;
    
	costheta = (1+xVec[0]/sqsum)*PREPROC_DEF_NORMALIZEDSIZE/2;

    featurePtr = new PointFloatShapeFeature(xVec[0],
                                             yVec[0],
                                             sintheta,
                                             costheta,
                                             penUp[0]);

	outFeatureVec.push_back(LTKShapeFeaturePtr(featurePtr));
	featurePtr = NULL;

    
	for( i=1; i<numPoints; ++i)
	{  

		//Add the controlInfo here

		sqsum = sqrt(pow(delta_x[i-1],2) + pow(delta_y[i-1],2))+EPS;
		sintheta = (1+delta_y[i-1]/sqsum)*PREPROC_DEF_NORMALIZEDSIZE/2;
		costheta = (1+delta_x[i-1]/sqsum)*PREPROC_DEF_NORMALIZEDSIZE/2;

        featurePtr = new PointFloatShapeFeature(xVec[i],
                                               yVec[i],
                                               sintheta,
                                               costheta,
                                               penUp[i]);
		//***POPULATING THE FEATURE VECTOR***
		outFeatureVec.push_back(LTKShapeFeaturePtr(featurePtr));
		featurePtr = NULL;
    
	}

    LOG( LTKLogger::LTK_LOGLEVEL_DEBUG) << "Exiting " <<
        "PointFloatShapeFeatureExtractor::extractFeatures()" << endl;
    
	return SUCCESS;
}