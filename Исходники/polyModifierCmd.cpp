MStatus polyModifierCmd::processUpstreamNode( modifyPolyData& data )
{
	MStatus status = MS::kSuccess;

	// Declare our function sets - Although dagNodeFn derives from depNodeFn, we need
	//							   both since dagNodeFn can only refer to DAG objects.
	//							   We will use depNodeFn for all times other when dealing
	//							   with the DAG.
	//
	MFnDependencyNode	depNodeFn;
	MFnDagNode			dagNodeFn;

	// Use the selected node's plug connections to find the upstream plug.
	// Since we are looking at the selected node's inMesh attribute, it will
	// always have only one connection coming in if it has history, and none
	// otherwise.
	//
	// If there is no history, copy the selected node and place it ahead of the
	// modifierNode as the new upstream node so that the modifierNode has an
	// input mesh to operate on.
	//
	MPlugArray tempPlugArray;

	if( fHasHistory )
	{
		// Since we have history, look for what connections exist on the
		// meshNode "inMesh" plug. "inMesh" plugs should only ever have one
		// connection.
		//
		data.meshNodeDestPlug.connectedTo( tempPlugArray, true, false);

		// ASSERT: Only one connection should exist on meshNodeShape.inMesh!
		//
		MStatusAssert( (tempPlugArray.length() == 1),
					   "tempPlugArray.length() == 1 -- 0 or >1 connections on meshNodeShape.inMesh" );
		data.upstreamNodeSrcPlug = tempPlugArray[0];

		// Construction history only deals with shapes, so we can grab the
		// upstreamNodeShape off of the source plug.
		//
		data.upstreamNodeShape = data.upstreamNodeSrcPlug.node();
		depNodeFn.setObject( data.upstreamNodeShape );
		data.upstreamNodeSrcAttr = data.upstreamNodeSrcPlug.attribute();

		// Disconnect the upstream node and the selected node, so we can
		// replace them with our own connections below.
		//
		fDGModifier.disconnect( data.upstreamNodeShape,
								data.upstreamNodeSrcAttr,
								data.meshNodeShape,
								data.meshNodeDestAttr );

	}
	else	// No History (!fHasHistory)
	{
		// Use the DAG node function set to duplicate the shape of the meshNode.
		// The duplicate method will return an MObject handle to the transform
		// of the duplicated shape, so traverse the dag to locate the shape. Store
		// this duplicate shape as our "upstream" node to drive the input for the 
		// modifierNode.
		//
		dagNodeFn.setObject( data.meshNodeShape );
		data.upstreamNodeTransform = dagNodeFn.duplicate( false, false );
		dagNodeFn.setObject( data.upstreamNodeTransform );


		// Ensure that our upstreamNode is pointing to a shape.
		//
		MStatusAssert( (0 < dagNodeFn.childCount()),
					   "0 < dagNodeFn.childCount() -- Duplicate meshNode transform has no shape." );
		data.upstreamNodeShape = dagNodeFn.child(0);

		// Re-parent the upstreamNodeShape under our original transform
		//
		status = fDagModifier.reparentNode( data.upstreamNodeShape, data.meshNodeTransform );
		MCheckStatus( status, "reparentNode" );

		// Perform the DAG re-parenting
		// 
		// Note: This reparent must be performed before the deleteNode() is called.
		//		 See polyModifierCmd.h (see definition of fDagModifier) for more details.
		//
		status = fDagModifier.doIt();
		MCheckStatus( status, "fDagModifier.doIt()" );

		// Mark the upstreamNodeShape (the original shape) as an intermediate object
		// (making it invisible to the user)
		//
		dagNodeFn.setObject( data.upstreamNodeShape );
		dagNodeFn.setIntermediateObject( true );

		// Get the upstream node source attribute
		//
		data.upstreamNodeSrcAttr = dagNodeFn.attribute( "outMesh" );

		// Remove the duplicated transform node (clean up)
		//
		status = fDagModifier.deleteNode( data.upstreamNodeTransform );
		MCheckStatus( status, "deleteNode" );

		// Perform the DAG delete node
		//
		// Note: This deleteNode must be performed after the reparentNode() method is
		//		 completed. See polyModifierCmd.h (see definition of fDagModifier) for
		//		 details.
		//
		status = fDagModifier.doIt();
		MCheckStatus( status, "fDagModifier.doIt()" );

		// Cache the DAG path to the duplicate shape
		//
		dagNodeFn.getPath( fDuplicateDagPath );
	}

	return status;
}