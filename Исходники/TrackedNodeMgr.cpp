bool CTrackedNodeMgr::SetNodeConstraints(	HTRACKEDNODE ID,
							const LTVector& vMovConeAxis, 
							const LTVector& vMovConeUp,
							float fXDiscomfortAngle,
							float fYDiscomfortAngle,
							float fXMaxAngle,
							float fYMaxAngle,
							float fMaxAngVel
						)
{
	//sanity checks
	if(!CheckValidity(ID))
		return false;

	//ok, we have a valid ID, so let us setup the parameters
	CTrackedNode* pNode = (CTrackedNode*)ID;

	//see if the up and forward vectors are valid
	LTVector vForward	= vMovConeAxis;
	LTVector vUp		= vMovConeUp;

	//ensure proper scale
	vForward.Normalize();
	vUp.Normalize();

	//ensure they form a valid space (and not a plane)
	if(vUp.Dot(vForward) > 0.99f)
	{
		//not valid, we need to try a different up, our preference is the world up
		vUp.Init(0.0f, 1.0f, 0.0f);

		if(vUp.Dot(vForward) > 0.99f)
		{
			//ok, forward is already taking the up....so, tilt us back
			vUp.Init(0.0f, 0.0f, -1.0f);
		}
	}

	//now generate the right, and ensure orthogonality
	LTVector vRight = vForward.Cross(vUp);
	vUp = vRight.Cross(vForward);

	vRight.Normalize();
	vUp.Normalize();

	//setup this as the basis space
	pNode->m_mInvTargetTransform.SetBasisVectors(&vRight, &vUp, &vForward);
	pNode->m_mInvTargetTransform.Transpose();

	//we need to make sure that their angular constraints are valid (meaning that they are positive and
	//less than 90 deg)
	fXMaxAngle			= LTCLAMP(fXMaxAngle,			0.0f, DEG2RAD(89.0f));
	fYMaxAngle			= LTCLAMP(fYMaxAngle,			0.0f, DEG2RAD(89.0f));
	fXDiscomfortAngle	= LTCLAMP(fXDiscomfortAngle,	0.0f, fXMaxAngle);
	fYDiscomfortAngle	= LTCLAMP(fYDiscomfortAngle,	0.0f, fYMaxAngle);

	//now precompute the tangent of those values (used for finding the height of the cone created which
	//is used in the threshold determination code)
	pNode->m_fTanXDiscomfort = (float)tan(fXDiscomfortAngle);
	pNode->m_fTanYDiscomfort = (float)tan(fYDiscomfortAngle);
	pNode->m_fTanXThreshold  = (float)tan(fXMaxAngle);
	pNode->m_fTanYThreshold  = (float)tan(fYMaxAngle);

	//handle setting up the maximum angular velocity
	pNode->m_fMaxAngVel		= (float)fabs(fMaxAngVel);

	//and we are ready for primetime
	return true;
}