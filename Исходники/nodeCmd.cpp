MStatus pbdSolverCmd::redoIt()
{
	//create solver node
	MStatus stat;
	MObject transform = dgMod.createNode("transform");
    MObject solver= dgMod.createNode(pbdSolverNode::typeId, transform, &stat);
	//connect time attribute
	MPlug plgInTime(solver,pbdSolverNode::time);
	MItDependencyNodes dnTime(MFn::kTime);
	MObject time = dnTime.thisNode();
	MPlug plgOutTime = MFnDependencyNode(time).findPlug("outTime", false);
	dgMod.connect(plgOutTime, plgInTime);
	
	//connect msattr
	MSelectionList activeSelect; 
	MGlobal::getActiveSelectionList(activeSelect);

	int pnum = 0, mnum = 0;
	for(int i = 0;i < activeSelect.length(); ++i)
	{
		MObject tNode; 
		activeSelect.getDependNode(i,tNode);
		MFnDagNode fnDagNode(tNode);
		MObject pNode=fnDagNode.child(0); 
		MFnDependencyNode fnNode(pNode);
			
		//MString name=fnNode1.name().asChar();
		if(fnNode.typeId() == OParticleNode::typeId)
		{
			//get solver message attribute from particleNode
			MPlug s_msg(pNode,OParticleNode::pbd_solver);
			//get particle message attribute from solverNode
			MPlug o_msg(solver,pbdSolverNode::orientedParticle);
			dgMod.connect(o_msg,s_msg);
			++pnum;
		}
		else if(pNode.apiType()==MFn::kMesh)
		{
			MString name=MFnDependencyNode(pNode).name().asChar();
			MPlug m_vs=fnNode.findPlug("ogc",false);
			MPlug s_vs(solver,pbdSolverNode::inMesh);

			dgMod.connect(m_vs,s_vs);
			++mnum;
		}
	}
	if( pnum == 0 )
		MGlobal::displayError(" No oriented particles are selected");
	if( mnum == 0 )
		MGlobal::displayError(" No mesh is selected");

	MGlobal::displayInfo("PBD solver is created");
	return dgMod.doIt();	
}