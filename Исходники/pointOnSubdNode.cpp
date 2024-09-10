MStatus pointOnSubd::compute( const MPlug& plug, MDataBlock& data )
//
//	Description:
//		This method computes the value of the given output plug based
//		on the values of the input attributes.
//
//	Arguments:
//		plug - the plug to compute
//		data - object that provides access to the attributes for this node
//
{
	MStatus returnStatus;
 
	// Check which output attribute we have been asked to compute.  If this 
	// node doesn't know how to compute it, we must return 
	// MS::kUnknownParameter.
	// 
	if( (plug == aPoint) || (plug == aNormal) ||
		(plug == aPointX) || (plug == aNormalX) ||
		(plug == aPointY) || (plug == aNormalY) ||
		(plug == aPointZ) || (plug == aNormalZ) ) {

		// Get a handle to the input attribute that we will need for the
		// computation.  If the value is being supplied via a connection 
		// in the dependency graph, then this call will cause all upstream  
		// connections to be evaluated so that the correct value is supplied.
		// 
		do {
			MDataHandle subdHandle = data.inputValue( aSubd, &returnStatus );
			if( returnStatus != MS::kSuccess ) {
				MGlobal::displayError( "ERROR: cannot get subd\n" );
				break;
			}
			
			MDataHandle faceFirstHandle =
				data.inputValue( aFaceFirst, &returnStatus );
			if( returnStatus != MS::kSuccess ) {
				MGlobal::displayError( "ERROR: cannot get face first\n" );
				break;
			}
			
			MDataHandle faceSecondHandle =
				data.inputValue( aFaceSecond, &returnStatus );
			if( returnStatus != MS::kSuccess ) {
				MGlobal::displayError( "ERROR: cannot get face2\n" );
				break;
			}
			
			MDataHandle uHandle = data.inputValue( aU, &returnStatus );
			if( returnStatus != MS::kSuccess ) {
				MGlobal::displayError( "ERROR: cannot get u\n" );
				break;
			}
			
			MDataHandle vHandle = data.inputValue( aV, &returnStatus );
			if( returnStatus != MS::kSuccess ) {
				MGlobal::displayError( "ERROR: cannot get v\n" );
				break;
			}

			MDataHandle relHandle = data.inputValue( aRelativeUV, &returnStatus );
			if( returnStatus != MS::kSuccess ) {
				MGlobal::displayError( "ERROR: cannot get relative UV\n" );
				break;
			}
			
			// Read the input value from the handle.
			//
			MStatus stat;
			MObject subdValue = subdHandle.asSubdSurface();
			MFnSubd subdFn( subdValue, &stat );
			McheckErr(stat,"ERROR creating subd function set"); 

			int faceFirstValue = faceFirstHandle.asLong();
			int faceSecondValue = faceSecondHandle.asLong();
			double uValue = uHandle.asDouble();
			double vValue = vHandle.asDouble();
			bool relUV = relHandle.asBool();

			MPoint point;
			MVector normal;

			MUint64 polyId;
			stat = MFnSubdNames::fromSelectionIndices( polyId, faceFirstValue,
													   faceSecondValue );
			McheckErr(stat,"ERROR converting indices"); 


			stat = subdFn.evaluatePositionAndNormal( polyId, uValue, vValue,
													 relUV, point, normal );
			normal.normalize();
			McheckErr(stat,"ERROR evaluating the position and the normal"); 

			// Get handles to the output attributes.  This is similar to the
			// "inputValue" call above except that no dependency graph 
			// computation will be done as a result of this call.
			// 
			MDataHandle pointHandle = data.outputValue( aPoint );
			pointHandle.set( point.x, point.y, point.z );
			data.setClean(plug);

			MDataHandle normalHandle = data.outputValue( aNormal );
			normalHandle.set( normal.x, normal.y, normal.z );
			data.setClean(plug);

		} while( false );
	}
	else {
		return MS::kUnknownParameter;
	}

	return MS::kSuccess;
}