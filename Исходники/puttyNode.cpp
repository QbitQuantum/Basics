MStatus puttyNode::deform( MDataBlock& block, MItGeometry& iter, const MMatrix& worldMatrix, unsigned int multiIndex)
{
//	MGlobal::displayInfo("deform");
    MStatus status = MS::kSuccess;

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // get inputs
    //
	
	// get the node ready flag
	MDataHandle dh = block.inputValue(aScriptSourced,&status);
	SYS_ERROR_CHECK(status, "Error getting aScriptSourced data handle\n");
	bool scriptSourced = dh.asBool();
	if (!scriptSourced)
		return MS::kSuccess;


	dh = block.inputValue(aNodeReady,&status);
	SYS_ERROR_CHECK(status, "Error getting node ready data handle\n");
	bool nodeReady = dh.asBool();

	// if it's not ready, don't do anything
	if (!nodeReady)
		return MS::kSuccess;

    dh = block.inputValue(aDefSpace,&status);
    SYS_ERROR_CHECK(status, "Error getting defSpace data handle\n");
    short defSpace = dh.asShort();
    
    dh = block.inputValue(aDefWeights,&status);
    SYS_ERROR_CHECK(status, "Error getting defWeights data handle\n");
    short defWeights = dh.asShort();
 
    dh = block.inputValue(aDefEnvelope,&status);
    SYS_ERROR_CHECK(status, "Error getting defEnvelope data handle\n");
    short defEnvelope = dh.asShort();
    

    
    // get the command
    dh = block.inputValue(aCmdBaseName,&status);
    SYS_ERROR_CHECK(status, "Error getting aCmdBaseName  handle\n");    
    MString script =  dh.asString(); 
        
 /*   if (script == "")
    {
        status = MS::kFailure;
        USER_ERROR_CHECK(status, "no script provided!\n");    
    }
   */ 
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // build mel cmd string
    //
    
    // check if it's a valid cmd
        
   
    // get the envelope
    //
    double env = 1;
    
    if (defEnvelope == MSD_ENVELOPE_AUTO)
    {
        dh = block.inputValue(envelope,&status);
    	SYS_ERROR_CHECK(status, "Error getting envelope data handle\n");	
	    env = double(dh.asFloat());	
        
        // early stop 'cause there is nothing more to do
        if (env == 0.0)
            return MS::kSuccess;
    }
    
    // get the points, transform them into the right space if needed
    //
    int count = iter.count();
    MVectorArray points(count);
    for ( ; !iter.isDone(); iter.next()) 
        points[iter.index()] = iter.position();
        
    if ( defSpace == MSD_SPACE_WORLD )
    {
        for (int i = 0;i<count;i++)
            points[i] = MPoint(points[i]) * worldMatrix;
    }
    
    
    // get the weights
    //
    MDoubleArray weights;
    if ( defWeights == MSD_WEIGHTS_AUTO)
    {
        weights.setLength(count);
        
        for (int i = 0;i<count;i++)
            weights[i]  = weightValue(block,multiIndex,i);
        
    }


    // get the object name and type
    // get the input geometry, traverse through the data handles    
    MArrayDataHandle adh = block.outputArrayValue( input, &status );
    SYS_ERROR_CHECK(status,"error getting input array data handle.\n");

    status = adh.jumpToElement( multiIndex );
    SYS_ERROR_CHECK(status, "input jumpToElement failed.\n");

    // compound data 
    MDataHandle cdh = adh.inputValue( &status );
    SYS_ERROR_CHECK(status, "error getting input inputValue\n");
   
    // input geometry child
    dh = cdh.child( inputGeom );
    MObject dInputGeometry = dh.data();
   
    // get the type      
    MString geometryType = dInputGeometry.apiTypeStr();

    // get the name    
//    MFnDagNode dagFn( dInputGeometry, &status);
//    SYS_ERROR_CHECK(status, "error converting geometry obj to dag node\n");
   
//    MString geometryName = dagFn.fullPathName(&status);
//    SYS_ERROR_CHECK(status, "error getting full path name \n");

//    MString geometryType = "";
//    MString geometryName = "";
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //  
    //  set the current values on the temp plugs for the script to be picked up
    //
    
    // the position
    MObject thisNode = thisMObject();
    
    MPlug currPlug(thisNode,aCurrPosition);
    MFnVectorArrayData vecD;
    MObject currObj = vecD.create(points,&status);
    currPlug.setValue(currObj);
    SYS_ERROR_CHECK(status, "error setting currPosPlug value\n");
    
    // the weights
    currPlug =MPlug(thisNode,aCurrWeight);
    MFnDoubleArrayData dblD;
    currObj = dblD.create(weights,&status);
    currPlug.setValue(currObj);
    SYS_ERROR_CHECK(status, "error setting currWeightsPlug value\n");
    
    // world matrix
    currPlug =MPlug(thisNode,aCurrWorldMatrix);
    MFnMatrixData matD;
    currObj = matD.create(worldMatrix,&status);
    currPlug.setValue(currObj);
    SYS_ERROR_CHECK(status, "error setting currWorldMatrixPlug value\n");

    // the multi index
    currPlug =MPlug(thisNode,aCurrMultiIndex);
    currPlug.setValue(int(multiIndex));
    SYS_ERROR_CHECK(status, "error setting currMultiIndexPlug value\n");
    
    // geometry name/type
//    currPlug =MPlug(thisNode,aCurrGeometryName);
//    currPlug.setValue(geometryName);
//    SYS_ERROR_CHECK(status, "error setting aCurrGeometryName value\n");

    currPlug =MPlug(thisNode,aCurrGeometryType);
    currPlug.setValue(geometryType);
    SYS_ERROR_CHECK(status, "error setting aCurrGeometryType value\n");

   
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // execute the mel script
    //
    MString melCmd = script+"(\"" +name()+"\","+count+")";
    
    MCommandResult melResult;
    status = MGlobal::executeCommand(melCmd,melResult);
	
	// if the command did not work, then try to resource the script
	// (might have been that we were in a fresh scene and nothing was ready yet
	if (status != MS::kSuccess)
	{
		dh = block.inputValue(aScript,&status);
	    SYS_ERROR_CHECK(status, "Error getting aCmdBaseName  handle\n");    
		MString scriptFile =  dh.asString(); 	

		// try to source the script
		MString cmd = "source \"" + scriptFile+"\"";
			
		MCommandResult melResult;
		status = MGlobal::executeCommand(cmd,melResult);
		// if successfull, retry the command 
		if (!status.error())
		{
			status = MGlobal::executeCommand(melCmd,melResult);
		}
	}

	USER_ERROR_CHECK(status, "Error executing mel command, please check the function you provided is valid, error free and has the appropriate parameters!");

    // check the result type
    if ((melResult.resultType()) != (MCommandResult::kDoubleArray))
    {
        USER_ERROR_CHECK(MS::kFailure, "result of mel command has wrong type, should be doubleArray (which will be interpreted as vectorArray)!");
    }
    
    // get the result as a double array
    MDoubleArray newP;  
    status = melResult.getResult(newP);
    USER_ERROR_CHECK(status, "Error getting result of mel command!");
    
    int newCount = newP.length()/3;
    // size check
    if (newCount != count)
    {
        USER_ERROR_CHECK(MS::kFailure, "the size of the result does not match the size of the input!");
    }

    // convert the double array into a vector array
    MPointArray newPoints(newCount);
    
    for(int i=0;i<newCount;i++)
        newPoints[i]=MPoint(newP[i*3],newP[i*3+1],newP[i*3+2]);
    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // interprete and apply the result
    //


  
    // do the envelope and weights   
    if ((defEnvelope == MSD_ENVELOPE_AUTO)||((defWeights == MSD_WEIGHTS_AUTO)))
    {
        MDoubleArray envPP(count, env);
    
        if (defWeights == MSD_WEIGHTS_AUTO)
        { 
            for (int i = 0;i<count;i++)
                envPP[i] *= weights[i];
        }

        // linear interpolation between old and new points
        for (int i = 0;i<count;i++)
            newPoints[i] = (points[i] * (1-envPP[i])) + (newPoints[i] * envPP[i]);
    }


    // retransform the result if it was in world space
    if ( defSpace == MSD_SPACE_WORLD )
    {
        MMatrix worldMatrixInv = worldMatrix.inverse();
        
        for (int i = 0;i<count;i++)
            newPoints[i] *= worldMatrixInv;
    }
 
 
    // set the points    
    iter.reset();
  	for ( ; !iter.isDone(); iter.next()) 
     	iter.setPosition(newPoints[iter.index()]);    

    return status;
}