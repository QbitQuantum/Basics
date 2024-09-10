MStatus particleSystemInfoCmd::nodeFromName(MString name, MObject & obj)
{
	MSelectionList tempList;
	tempList.add( name );
	if ( tempList.length() > 0 ) 
	{
		tempList.getDependNode( 0, obj );
		return MS::kSuccess;
	}
	return MS::kFailure;
}