MStatus dgTransform::compute( const MPlug& plug, MDataBlock& data )
{
	MStatus status;

	MDataHandle hTranslate = data.inputValue( aTranslate, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hRotate    = data.inputValue( aRotate, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hScale     = data.inputValue( aScale, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hShear     = data.inputValue( aShear, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hJointOrient     = data.inputValue( aJointOrient, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );

	MDataHandle hInputTranslate = data.inputValue( aInputTranslate, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hInputRotate    = data.inputValue( aInputRotate, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hInputScale     = data.inputValue( aInputScale, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );
	MDataHandle hInputShear     = data.inputValue( aInputShear, &status );
	CHECK_MSTATUS_AND_RETURN_IT( status );


	MPxTransformationMatrix inputMpxTrMtx;
	MEulerRotation inputEulerRot( hInputRotate.asVector() );

	inputMpxTrMtx.translateTo( hInputTranslate.asVector() );
	inputMpxTrMtx.rotateTo( inputEulerRot );
	inputMpxTrMtx.scaleTo( hInputScale.asVector() );
	inputMpxTrMtx.shearTo( hInputShear.asVector() );


	MMatrix parentMatrix = inputMpxTrMtx.asMatrix();


	MPxTransformationMatrix mpxTrMtx;
	MEulerRotation eulerRot( hRotate.asVector() );
	MEulerRotation joEulerRot( hJointOrient.asVector() );

	mpxTrMtx.translateTo( hTranslate.asVector() );
	mpxTrMtx.rotateTo( eulerRot );
	mpxTrMtx.rotateBy( joEulerRot );
	mpxTrMtx.scaleTo( hScale.asVector() );
	mpxTrMtx.shearTo( hShear.asVector() );

	if( plug == aMatrix )
	{
		//cout <<"matrix"<<endl;
		MDataHandle hMatrix = data.outputValue( aMatrix, &status );
		CHECK_MSTATUS_AND_RETURN_IT( status );
		hMatrix.setMMatrix( mpxTrMtx.asMatrix() );
	}

	if( plug == aInverseMatrix )
	{
		//cout <<"inverseMatrix"<<endl;
		MDataHandle hInverseMatrix = data.outputValue( aInverseMatrix, &status );
		CHECK_MSTATUS_AND_RETURN_IT( status );
		hInverseMatrix.setMMatrix( mpxTrMtx.asMatrix().inverse() );
	}

	if( plug == aWorldMatrix || plug == aWorldInverseMatrix )
	{
		MMatrix worldMatrix = mpxTrMtx.asMatrix()*parentMatrix;
		if( plug == aWorldMatrix )
		{
			//cout <<"worldMatrix"<<endl;
			MDataHandle hWorldMatrix = data.outputValue( aWorldMatrix, &status );
			CHECK_MSTATUS_AND_RETURN_IT( status );
			hWorldMatrix.setMMatrix( worldMatrix );
		}

		if( plug == aWorldInverseMatrix )
		{
			//cout <<"worldInverseMatrix"<<endl;
			MDataHandle hWorldInverseMatrix = data.outputValue( aWorldInverseMatrix, &status );
			CHECK_MSTATUS_AND_RETURN_IT( status );
			hWorldInverseMatrix.setMMatrix( worldMatrix.inverse() );
		}
	}

	if( plug == aParentMatrix )
	{
		//cout <<"parentMatrix"<<endl;
		MDataHandle hParentMatrix = data.outputValue( aParentMatrix, &status );
		CHECK_MSTATUS_AND_RETURN_IT( status );
		hParentMatrix.setMMatrix( parentMatrix );
	}

	if( plug == aParentInverseMatrix )
	{
		//cout <<"parentInverseMatrix"<<endl;
		MDataHandle hParentInverseMatrix = data.outputValue( aParentInverseMatrix, &status );
		CHECK_MSTATUS_AND_RETURN_IT( status );
		hParentInverseMatrix.setMMatrix( parentMatrix.inverse() );
	}

	data.setClean( plug );

	return status;
}