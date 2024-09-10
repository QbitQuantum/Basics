//
//      Deform computation
//
MStatus jhMeshBlur::deform( MDataBlock& block,MItGeometry& iter,const MMatrix& m,unsigned int multiIndex)
{
    MStatus returnStatus;

    // Envelope
    float envData = block.inputValue(envelope, &returnStatus).asFloat();
	CHECK_MSTATUS(returnStatus);

    if(envData == 0)
		return MS::kFailure;

    /*
     VARIABLES
     */
    //float factor = block.inputValue(aShapeFactor, &returnStatus).asFloat();
    float fStrength = block.inputValue(aStrength, &returnStatus).asFloat();
	CHECK_MSTATUS(returnStatus);
	
	if (fStrength == 0)
		return MS::kFailure;
	
    float fThreshold = block.inputValue(aTreshhold, &returnStatus).asFloat();
	CHECK_MSTATUS(returnStatus);
    float fW = 0.0f; // weight
    float fDistance;
    fStrength *= envData;

    double dKracht = block.inputValue(aInterpPower, &returnStatus).asDouble();
	CHECK_MSTATUS(returnStatus);
    double dDotProduct;  // Dotproduct of the point

    bool bTweakblur = block.inputValue(aTweakBlur, &returnStatus).asBool();
	CHECK_MSTATUS(returnStatus);
	
    bool bQuad = block.inputValue(aQuadInterp, &returnStatus).asBool();
	CHECK_MSTATUS(returnStatus);
	
	MTime inTime = block.inputValue(aTime).asTime();
    int nTijd = (int)inTime.as(MTime::kFilm);


    MFloatVectorArray currentNormals;   // normals of mesh
    MFnPointArrayData fnPoints;         // help converting to MPointArrays
    MFloatVector dirVector;             // direction vector of the point
    MFloatVector normal;                // normal of the point
    MPointArray savedPoints;            // save all point before edited
    MMatrix matInv = m.inverse();       // inversed matrix
    MPoint ptA;                         // current point (iter mesh)
    MPoint ptB;                         // previous point (iter mesh)
    MPoint ptC;                         // mesh before previous point (iter mesh)

    // get node, use node to get inputGeom, use inputGeom to get mesh data, use mesh data to get normal data
    MFnDependencyNode nodeFn(this->thisMObject());

    MPlug inGeomPlug(nodeFn.findPlug(this->inputGeom,true));
    MObject inputObject(inGeomPlug.asMObject());
    MFnMesh inMesh(inputObject);

    inMesh.getVertexNormals(true, currentNormals);

    // get the previous mesh data
    MPlug oldMeshPlug = nodeFn.findPlug(MString("oldMesh"));
    MPlug oldMeshPositionsAPlug = oldMeshPlug.elementByLogicalIndex((multiIndex*4) + 0);
    MPlug oldMeshPositionsBPlug = oldMeshPlug.elementByLogicalIndex((multiIndex*4) + 1);
    MPlug oldMeshPositionsCPlug = oldMeshPlug.elementByLogicalIndex((multiIndex*4) + 2); // cache for tweak mode
    MPlug oldMeshPositionsDPlug = oldMeshPlug.elementByLogicalIndex((multiIndex*4) + 3); // cache for tweak mode

    // convert to MPointArrays
    MObject objOldMeshA;
    MObject objOldMeshB;
    MObject objOldMeshC; // cache
    MObject objOldMeshD; // cache

    oldMeshPositionsAPlug.getValue(objOldMeshA);
    oldMeshPositionsBPlug.getValue(objOldMeshB);
    oldMeshPositionsCPlug.getValue(objOldMeshC); // cache
    oldMeshPositionsDPlug.getValue(objOldMeshD); // cache

    fnPoints.setObject(objOldMeshA);
    MPointArray oldMeshPositionsA = fnPoints.array();
    
    fnPoints.setObject(objOldMeshB);
    MPointArray oldMeshPositionsB = fnPoints.array();
    
    fnPoints.setObject(objOldMeshC);
    MPointArray oldMeshPositionsC = fnPoints.array(); // cache
    
    fnPoints.setObject(objOldMeshD);
    MPointArray oldMeshPositionsD = fnPoints.array(); // cache

    
    
    // If mesh position variables are empty,fill them with default values
    if(oldMeshPositionsA.length() == 0 || nTijd <= 1){
        iter.allPositions(oldMeshPositionsA);

        for(int i=0; i < oldMeshPositionsA.length(); i++)
        {
            // convert to world
            oldMeshPositionsA[i] = oldMeshPositionsA[i] * m;
        }
		
        oldMeshPositionsB.copy(oldMeshPositionsA);
        oldMeshPositionsC.copy(oldMeshPositionsA); // cache
        oldMeshPositionsD.copy(oldMeshPositionsA); // cache
    }
	
	// get back old date again
	if (bTweakblur == true) { // restore cache
		oldMeshPositionsA.copy(oldMeshPositionsC);
		oldMeshPositionsB.copy(oldMeshPositionsD);
	}
    
    
    iter.allPositions(savedPoints);
    for(int i=0; i < savedPoints.length(); i++)
    {
        // convert points to world points
        savedPoints[i] = savedPoints[i] * m;
    }

    // Actual Iteration through points
    for (; !iter.isDone(); iter.next()){
        // get current position
        ptA = iter.position();
        // get old positions
        ptB = oldMeshPositionsA[iter.index()] * matInv;
        ptC = oldMeshPositionsB[iter.index()] * matInv;

        fDistance = ptA.distanceTo(ptB);
        fW = weightValue(block,multiIndex,iter.index());


        if (fDistance * (fStrength*fW) < fThreshold && fThreshold > 0){
            iter.setPosition(ptA);
        } else {
            // aim/direction vector to calculate strength
            dirVector = (ptA - ptB); // (per punt)
            dirVector.normalize();

            normal = currentNormals[iter.index()];

            dDotProduct = normal.x * dirVector.x + normal.y * dirVector.y + normal.z * dirVector.z;

            
            if(bQuad == true){
                MVector vecA(((ptB - ptC) + (ptA - ptB)) / 2);
                vecA.normalize();

                MPoint hiddenPt(ptB + (vecA * fDistance) * dKracht);
                ptA = quadInterpBetween(ptB, hiddenPt, ptA, (1 - fStrength * fW) + (linearInterp(dDotProduct, -1, 1) * (fStrength * fW) ) );
            } else {
                MPoint halfway = (ptA - ptB) * 0.5;
                MPoint offset = halfway * dDotProduct * (fStrength*fW);
                ptA = ptA - ((halfway * (fStrength*fW)) - offset); // + (offset * strength);
            }
            // set new value

            iter.setPosition(ptA);
        }
    }
    if(bTweakblur == false){
        oldMeshPositionsD.copy(oldMeshPositionsB);
        oldMeshPositionsC.copy(oldMeshPositionsA);
        oldMeshPositionsB.copy(oldMeshPositionsA);
        oldMeshPositionsA.copy(savedPoints);

        // Save back to plugs
        objOldMeshA = fnPoints.create(oldMeshPositionsA);
        objOldMeshB = fnPoints.create(oldMeshPositionsB);
        objOldMeshC = fnPoints.create(oldMeshPositionsC);
        objOldMeshD = fnPoints.create(oldMeshPositionsD);
		
        oldMeshPositionsAPlug.setValue(objOldMeshA);
        oldMeshPositionsBPlug.setValue(objOldMeshB);
        oldMeshPositionsCPlug.setValue(objOldMeshC);
        oldMeshPositionsDPlug.setValue(objOldMeshD);
    }
    
    return returnStatus;
}