//---------------------------------------------------------------------------
//
// This implementation of NfGetLocalTM removes all scales from the returned
// Matrix3, but also stores them in the parameter pScaleOut (if specified)
// so that they can be pushed down to the geometry level.
//
Matrix3 U2MaxSceneExport::GetLocalTM(INode* pMaxNode, TimeValue t)
{
	Matrix3 localScaleTM;
	INode* pParent = pMaxNode->GetParentNode();


	if(pParent)
	{
		Matrix3 parentTM = pParent->GetNodeTM(t);
		Matrix3 thisTM = pMaxNode->GetNodeTM(t);

		localScaleTM = thisTM * Inverse(parentTM);		
	}
	else 
		localScaleTM.IdentityMatrix();

	Matrix3 localNoScaleTM;
	localNoScaleTM = UniformMatrix(localScaleTM);

	return localNoScaleTM;

}