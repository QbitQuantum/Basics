//
// Method to add in a light "prune" list. Only selected
// lights will be have their shadows requested, and
// be used for the scene render shader override.
//
MStatus viewRenderOverrideShadows::updateLightList()
{
	mLightList.clear();

	shadowPrepass* shadowOp = (shadowPrepass*)mRenderOperations[kShadowPrePass];
	sceneRender* sceneOp = (sceneRender*)mRenderOperations[kMaya3dSceneRender];
	if (!shadowOp || !sceneOp)
		return MStatus::kFailure;

	// Scan selection list for active lights
	//
	MSelectionList selectList;
	MDagPath dagPath;
	MObject component;
	MGlobal::getActiveSelectionList( selectList );
	for (unsigned int i=0; i<selectList.length(); i++)
	{
		selectList.getDagPath( i, dagPath, component );
		dagPath.extendToShape();
		if ( dagPath.hasFn( MFn::kLight ) )
		{
			mLightList.add( dagPath );
		}
	}
	
	// Set light list to prune which lights to request shadows for
	//
	if (mLightList.length())
		shadowOp->setLightList( &mLightList );
	else
		shadowOp->setLightList( NULL );

	// Set light list to prune which lights to bind for scene shader
	//
	if (mLightList.length())
		sceneOp->setLightList( &mLightList );
	else
		sceneOp->setLightList( NULL );

	return MStatus::kSuccess;
}