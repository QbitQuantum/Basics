void createIK2BsolverAfterOpen(void *clientData)
//
// This method creates the ik2Bsolver after a File->Open
// if the ik2Bsolver does not exist in the loaded file.
//
{
	MSelectionList selList;
	MGlobal::getSelectionListByName("ik2Bsolver", selList);
	if (selList.length() == 0) {
		MGlobal::getActiveSelectionList( selList );
		MGlobal::executeCommand("createNode -n ik2Bsolver ik2Bsolver");
		MGlobal::setActiveSelectionList( selList );
	}
}