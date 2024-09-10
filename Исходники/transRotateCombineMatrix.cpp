MStatus transRotateCombineMatrix::compute( const MPlug& plug, MDataBlock& data )
{
	MStatus status;

	MDataHandle hOutputMatrix = data.outputValue( aOutputMatrix, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hOutputInverseMatrix = data.outputValue( aOutputInverseMatrix, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hTransMatrix = data.inputValue( aInputTransMatrix, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hRotateMatrix = data.inputValue( aInputRotateMatrix, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );

	MMatrix transMatrix = hTransMatrix.asMatrix();
	MMatrix rotateMatrix = hRotateMatrix.asMatrix();

	double buildMatrix[4][4] = { rotateMatrix( 0,0 ), rotateMatrix( 0,1 ), rotateMatrix( 0,2 ), 0,
		                         rotateMatrix( 1,0 ), rotateMatrix( 1,1 ), rotateMatrix( 1,2 ), 0,
								 rotateMatrix( 2,0 ), rotateMatrix( 2,1 ), rotateMatrix( 2,2 ), 0,
								 transMatrix( 3,0 ),  transMatrix( 3,1 ),  transMatrix( 3,2 ),  1 };

	MMatrix buildMtx = buildMatrix;
	
	if( plug == aOutputMatrix )
		hOutputMatrix.set( buildMtx );
	if( plug == aOutputInverseMatrix )
		hOutputInverseMatrix.set( buildMtx.inverse() );

	data.setClean( plug );

	return status;
}