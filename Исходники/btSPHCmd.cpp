void btSPHCmd::getAABB(const MString &name, MPoint& min, MPoint &max)
{
    _LogFunctionCall("btSPHCmd::getAABB("<< name<<")");

    MStatus status = MS::kSuccess;

    MSelectionList sList;
    IfMErrorWarn(MGlobal::getSelectionListByName(name, sList));

    assert(sList.length()==1);
    MDagPath dp;
    IfMErrorWarn(sList.getDagPath(0, dp));
    IfMErrorWarn(dp.extendToShape());//particle shape

    MFnMesh meshFn( dp, &status );
    IfMErrorWarn(status);

    MPointArray positions;
    IfMErrorWarn(meshFn.getPoints(positions, MSpace::kWorld));

    const size_t LEN = positions.length();
    for(size_t i=0; i<LEN; ++i)
    {
        const MPoint &p = positions[i];
        if(p.x<min.x) min.x = p.x;
        if(p.y<min.y) min.y = p.y;
        if(p.z<min.z) min.z = p.z;

        if(p.x>max.x) max.x = p.x;
        if(p.y>max.y) max.y = p.y;
        if(p.z>max.z) max.z = p.z;
    }

// 	MPlug plug;
// 	getPlugValue_asDistance(min.x, meshFn, "boundingBoxMinX");
//  	getPlugValue_asDistance(min.y, meshFn, "boundingBoxMinY");
//  	getPlugValue_asDistance(min.z, meshFn, "boundingBoxMinZ");
//  	getPlugValue_asDistance(max.x, meshFn, "boundingBoxMaxX");
//  	getPlugValue_asDistance(max.y, meshFn, "boundingBoxMaxY");
//  	getPlugValue_asDistance(max.z, meshFn, "boundingBoxMaxZ");

}