void DMPDSExporter::fillSkeleton( DMPParameters* param )
{
	MStatus stat;
	mSkelData.clear();
	if (!param->bExportSkeleton)
	{
		return;
	}
	mSkelData.skeleton.name = param->skeletonFileName.asUTF8();


	// Get the selection list
	MSelectionList activeList;
	stat = MGlobal::getActiveSelectionList(activeList);
	if(param->bExportAll)
	{
		// We are exporting the whole scene
		MItDag dagIter;
		MFnDagNode worldDag (dagIter.root());
		MDagPath worldPath;
		worldDag.getPath(worldPath);
		traverseSubSkeleton(param, worldPath);
	}
	else
	{
		if (MStatus::kSuccess != stat)
		{
			return;
		}
		MItSelectionList iter(activeList);

		for ( ; !iter.isDone(); iter.next())
		{								
			MDagPath dagPath;
			iter.getDagPath(dagPath);
			traverseSubSkeleton(param, dagPath); 
		}	
	}
	// may lose selection while exporting, so reset it.
	MGlobal::setActiveSelectionList(activeList);
}