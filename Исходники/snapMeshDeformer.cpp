MStatus snapDeformer::deform(MDataBlock &data, MItGeometry &iter, const MMatrix &mat, unsigned int multiIndex) {
	MStatus stat;


    //lets see if we need to do anything
	MDataHandle DataHandle = data.inputValue(envelope, &stat);
	float env = DataHandle.asFloat();
	if (env == 0)
		return stat;
    DataHandle = data.inputValue(weight, &stat);
	const float weight = DataHandle.asFloat();
    if (weight == 0)
		return stat;
    
    env = (env*weight);


	//space target
	DataHandle = data.inputValue(space, &stat);
    int SpaceInt = DataHandle.asInt();

    //space source
	DataHandle = data.inputValue(spaceSource, &stat);
    int SpaceSourceInt = DataHandle.asInt();

    //pointlist
    MArrayDataHandle pointArrayHandle = data.inputArrayValue(pointList);


	//snapMesh
	MFnMesh	SnapMesh;
	DataHandle = data.inputValue(snapMesh, &stat);
    if (!stat)
        return Err(stat,"Can't get mesh to snap to");
    MObject SnapMeshObj = DataHandle.asMesh();
    SnapMesh.setObject(SnapMeshObj);
    MPointArray snapPoints;
    if (SpaceSourceInt==0)
        SnapMesh.getPoints(snapPoints, MSpace::kWorld);
    else
        SnapMesh.getPoints(snapPoints, MSpace::kObject);
    


    iter.reset();
    for ( ; !iter.isDone(); iter.next()) 	{
        //check for painted weights
        float currEnv = env * weightValue(data, multiIndex, iter.index());

        //get point to snap to
        unsigned int index;
        stat = pointArrayHandle.jumpToElement(iter.index());
        if (!stat)
            index = 0;
        else {
            DataHandle = pointArrayHandle.outputValue();
            index = DataHandle.asInt();
        }

        if (index != -1) {
            //calc point location
            MPoint currPoint;
            if (snapPoints.length() > index)
                currPoint = snapPoints[index];

            if (SpaceInt == 0)
                currPoint *= mat.inverse();

            if (currEnv !=1)
            {
                MPoint p = (currPoint- iter.position());
                currPoint = iter.position() + (p*currEnv);
            }


            //set point location
            iter.setPosition(currPoint);
        }
            
            
    }

    return stat;
}