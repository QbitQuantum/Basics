Matrix3 SGP_MaxInterface::GetNodeTM(INode *pNode, float time)
{
	// initialize matrix with the identity
	Matrix3 tm;
	tm.IdentityMatrix();

	// only do this for valid nodes
	if(pNode != NULL)
	{
		// get the node transformation
		tm = pNode->GetNodeTM(SecToTicks(time));

		// make the transformation uniform
		tm.NoScale();
	}

	return tm;
}