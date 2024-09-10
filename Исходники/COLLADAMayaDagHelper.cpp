    //---------------------------------------------------
    // set the bind pose for a transform
    //
    MStatus DagHelper::setBindPoseInverse ( const MObject& node, const MMatrix& bindPoseInverse )
    {
        MStatus status;
        MFnDependencyNode dgFn ( node );
        MPlug bindPosePlug = dgFn.findPlug ( "bindPose", &status );
        if ( status != MS::kSuccess )
        {
            MGlobal::displayWarning ( MString ( "No bindPose found on node " ) + dgFn.name() );
            return status;
        }

        MFnMatrixData matrixFn;
        MObject val = matrixFn.create ( bindPoseInverse.inverse(), &status );
        MObject invval = matrixFn.create ( bindPoseInverse, &status );
        if ( status != MS::kSuccess )
        {
            MGlobal::displayWarning ( MString ( "Error setting bindPose on node " ) + dgFn.name() );
            return status;
        }

        // set the bind pose on the joint itself
        bindPosePlug.setValue ( val );

        // Now, perhaps more significantly, see if there's a
        // skinCluster using this bone and update its bind
        // pose (as the joint bind pose is not connected to
        // the skin - it's set at bind time from the joint's
        // current position, and our importer may not want to
        // disturb the current scene state just to put bones
        // in a bind position before creating skin clusters)
        MObject _node ( node );
        MItDependencyGraph it ( _node, MFn::kSkinClusterFilter );
        while ( !it.isDone() )
        {
            MPlug plug = it.thisPlug();
            unsigned int idx = plug.logicalIndex();
            MFnDependencyNode skinFn ( plug.node() );
            MPlug skinBindPosePlug = skinFn.findPlug ( "bindPreMatrix", &status );

            if ( status == MS::kSuccess )
            {
                // The skinCluster stores inverse inclusive matrix
                // so notice we use invval (the MObject created off
                // the inverse matrix here)
                skinBindPosePlug = skinBindPosePlug.elementByLogicalIndex ( idx );
                skinBindPosePlug.setValue ( invval );
            }

            it.next();
        }

        return status;
    }