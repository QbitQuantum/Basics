// ----------------------------------------------------------------------- //
//
//	ROUTINE:	CAutoTargetMgr::InterpolateAim()
//
//	PURPOSE:	Rotate our current aim vector to match our target vector
//
// ----------------------------------------------------------------------- //
void CAutoTargetMgr::InterpolateAim()
{
	//we are currently aimed at m_vCurTarget
	//we want to aim at m_vTarget
	float fActualToTargetAng = m_vTarget.Dot(m_vCurTarget);

	//get the maximum angle we can move
	float fMaxAngVel = ObjectContextTimer( g_pMoveMgr->GetServerObject( )).GetTimerElapsedS( );
	if (IsMultiplayerGameClient())
	{
		fMaxAngVel *= ClientDB::Instance( ).GetMPAutoTargetSpeed();
	}
	else
	{
		fMaxAngVel *= ClientDB::Instance( ).GetAutoTargetSpeed();
	}
	float fCosMaxAngVel = (float)cos(fMaxAngVel);

	//if we are at 180 degrees difference, much can go wrong, so ensure that we aren't,
	//but if we are, we just want to keep looking in the direction that we currently
	//are
	if(fActualToTargetAng >= fCosMaxAngVel)
	{
		//the look target is within our reach, so just go there
		m_vCurTarget = m_vTarget;
	}
	else
	{
		//form a right vector that passes through the arc that we are interpolating
		//upon 
		LTVector vRight = m_vCurTarget - (m_vTarget - m_vCurTarget) / (fActualToTargetAng - 1.0f);
		vRight.Normalize();

		//now we can get our values based upon that space
		m_vCurTarget =  fCosMaxAngVel * m_vCurTarget + (float)sin(fMaxAngVel) * vRight;
		m_vCurTarget.Normalize();
		
	}	

}