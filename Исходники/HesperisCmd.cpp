MStatus HesperisCmd::doIt(const MArgList &args)
{
	MStatus status = parseArgs( args );
	
	if( status != MS::kSuccess ) return status;
	
	if(m_ioMode == IOHelp) return printHelp();
	
	MSelectionList selList;
    MGlobal::getActiveSelectionList(selList);
    
	if(selList.length() < 1) {
		MGlobal::displayInfo(" empty selction");
		return MS::kSuccess;
	}
    
    if(m_ioMode == IOWrite) return writeSelected(selList);
    if(m_ioMode == IOFieldDeform) return deformSelected();
	
	return MS::kSuccess;
}