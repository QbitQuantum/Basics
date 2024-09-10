MStatus lrutils::getMetaChildByRigId(MObject metaNodeObj, MString rigId, MObject& metaChildObj) {
    MStatus status = MS::kFailure;

    MFnDependencyNode metaNodeFn( metaNodeObj );
    MPlug metaChildrenPlug = metaNodeFn.findPlug( "metaChildren", true, &status );
    MyCheckStatusReturn(status, "MFnDependencyNode.findPlug() failed");

    //follow the plug connection to the connected plug on the other object
    MPlugArray connectedChildPlugs;
    metaChildrenPlug.connectedTo(connectedChildPlugs,false,true,&status);
    MyCheckStatusReturn(status,"MPlug.connectedTo() failed");

    for (unsigned int i = 0; i < connectedChildPlugs.length(); i++) {
        MPlug connectedPlug = connectedChildPlugs[i];
        MObject connectedNodeObj = connectedPlug.node(&status);
        MyCheckStatusReturn(status, "MPlug.node() failed");

        MFnDependencyNode connectedNodeFn( connectedNodeObj );

        //get the rigId number held in the rigId attribute
        MPlug rigIdPlug = connectedNodeFn.findPlug(MString("rigId"),true,&status);
        MyCheckStatusReturn(status,"findPlug failed");
        MString childRigId;
        rigIdPlug.getValue(childRigId);
        //if rigId is in childRigId then return the object
        if( childRigId.indexW(rigId) != -1 ) {
            metaChildObj = connectedNodeObj;
            status = MS::kSuccess;
            break;
        } 
    }

    return status;
}