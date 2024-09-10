	MObject getMObjectByName(const MString& name)
	{
		MSelectionList sList;
		MGlobal::getSelectionListByName(name, sList);
		assert(1==sList.length());
		
		MObject mobj;
		sList.getDependNode(0, mobj);
		return mobj;
	}