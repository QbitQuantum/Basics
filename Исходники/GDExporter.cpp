bool GDExporter::GetSelectedMeshTransformPath(MDagPath &transformPath)
{
	MSelectionList currSelection;
	MGlobal::getActiveSelectionList(currSelection);

	unsigned int selectionCount = currSelection.length();
	
	MFnMesh* exportingMesh = 0;

	for(unsigned int selectionIndex = 0; selectionIndex < selectionCount; ++selectionIndex )
	{
		MDagPath currPath;
		currSelection.getDagPath(selectionIndex, currPath);

		if( currPath.apiType() != MFn::kTransform )
			continue;

		MFnTransform currTransform(currPath);
		unsigned int childCount = currTransform.childCount();
		for(unsigned int childIndex = 0; childIndex < childCount; ++childIndex)
		{
			MObject childObject = currTransform.child(childIndex);
			if( childObject.apiType() == MFn::kMesh )
			{
				MFnMesh childMesh(childObject);
				if( childMesh.isIntermediateObject() )
					continue;

				currTransform.getPath(transformPath);
				return true;
			}
		}
	}

	return false;
}