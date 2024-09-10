MStatus   clusterControledCurve::compute( const MPlug& plug, MDataBlock& data )
{
	//MFnDependencyNode thisNode( thisMObject() );
	//cout << thisNode.name() << ", start" << endl;

	MStatus status;

	MDataHandle hInputCurve = data.inputValue( aInputCurve, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hInputCurveMatrix = data.inputValue( aInputCurveMatrix, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hOutputCurve = data.outputValue( aOutputCurve, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );

	MArrayDataHandle hArrBindPreMatrix = data.inputArrayValue( aBindPreMatrix, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MArrayDataHandle hArrMatrix = data.inputArrayValue( aMatrix, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );

	MArrayDataHandle hArrWeightList = data.inputArrayValue( aWeightList, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );

	MDataHandle hUpdate = data.inputValue( aUpdate, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );

	MObject oInputCurve = hInputCurve.asNurbsCurve();

	int bindPreMatrixLength = hArrBindPreMatrix.elementCount();
	int matrixLength = hArrMatrix.elementCount();

	MFnNurbsCurve fnInputCurve = oInputCurve;
	int numCVs = fnInputCurve.numCVs();
	int weightListLength = hArrWeightList.elementCount();

	if( weightListLength > 100 )
	{
		cout << "WeightList Count Error : " << weightListLength << endl;
		return MS::kFailure;
	}

	MPointArray inputCvPoints;
	MPointArray outputCvPoints;

	fnInputCurve.getCVs( inputCvPoints );
	outputCvPoints.setLength( numCVs );

	MMatrix matrix;
	MMatrix inputCurveMatrix = hInputCurveMatrix.asMatrix();
	MMatrix inputCurveMatrixInverse = inputCurveMatrix.inverse();

	if( requireUpdate )
	CHECK_MSTATUS_AND_RETURN_IT( updateBindPreMatrix( oInputCurve, inputCurveMatrixInverse,
				                                      hArrMatrix, hArrBindPreMatrix, hUpdate.asBool() ) );

	for( int i=0; i< numCVs; i++ )
	{
		inputCvPoints[i] *= inputCurveMatrix;
	}

	for( int i=0; i< numCVs; i++ )
	{
		outputCvPoints[i] = MPoint( 0,0,0 );
		double weight;

		for( int j=0; j< matrixLength; j++ )
		{
			weight = setWeights[i][j];

			hArrMatrix.jumpToElement( j );
			matrix = hArrMatrix.inputValue().asMatrix();
			outputCvPoints[i] += inputCvPoints[i]*bindPreMatrix[j]*matrix*weight;
		}
	}

	for( int i=0; i< numCVs; i++ )
	{
		outputCvPoints[i] *= inputCurveMatrixInverse;
	}

	MFnNurbsCurveData outputCurveData;
	MObject oOutputCurve = outputCurveData.create();

	fnInputCurve.copy( oInputCurve, oOutputCurve );

	MFnNurbsCurve fnOutputCurve( oOutputCurve, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	fnOutputCurve.setCVs( outputCvPoints );

	hOutputCurve.set( oOutputCurve );

	data.setClean( plug );

	//cout << thisNode.name() << ", end" << endl;

	return status;
}