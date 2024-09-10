Matrix3 Jiggle::GetCurrentTM(TimeValue t)
{
	INode* baseNode = NULL;
	baseNode = selfNode;

	Matrix3 selfTM;
	Point3 pos = Point3(0.0f,0.0f,0.0f);
	Interval for_ever = FOREVER;
	posCtrl->GetValue(t, pos, for_ever, CTRL_ABSOLUTE);
	if (baseNode != NULL )
	{
		selfTM = baseNode->GetNodeTM(t);
		selfTM.SetTrans(selfTM * pos);
	}
	else 
	{	
		selfTM.IdentityMatrix();
		selfTM.SetTrans(pos);
	}
	return selfTM;
}