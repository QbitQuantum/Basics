void ProxyViz::updateViewFrustum(MObject & thisNode)
{
	MPlug matplg(thisNode, acameraspace);
	MObject matobj;
	matplg.getValue(matobj);
	MFnMatrixData matdata(matobj);
    MMatrix cameramat = matdata.matrix(); 
	AHelper::ConvertToMatrix44F(*cameraSpaceR(), cameramat);
	AHelper::ConvertToMatrix44F(*cameraInvSpaceR(), cameramat.inverse() );
	float peye[3];
	peye[0] = cameramat.matrix[3][0];
	peye[1] = cameramat.matrix[3][1];
	peye[2] = cameramat.matrix[3][2];
	setEyePosition(peye);
	
	MPlug hfaplg(thisNode, ahapeture);
	float hfa = hfaplg.asFloat();
	MPlug vfaplg(thisNode, avapeture);
	float vfa = vfaplg.asFloat();
	MPlug flplg(thisNode, afocallength);
	float fl = flplg.asFloat();
	
    float farClip = -20.f;
    if(numPlants() > 0) getFarClipDepth(farClip, gridBoundingBox() );
    
    setFrustum(hfa, vfa, fl, -10.f, farClip );
	
	MPlug overscanPlug(thisNode, ainoverscan);
	setOverscan(overscanPlug.asDouble() );
}