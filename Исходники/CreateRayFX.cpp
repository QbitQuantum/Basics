//performs a ray intersection. This will return false if nothing is hit, or true if something
//is. If something is hit, it will fill out the intersection property and the alignment
//vector according to the properties that the user has setup. If an object is hit, it will
//fill out the hit object, and specify the output transform relative to the hit object's space
bool CCreateRayFX::DetermineIntersection(	const LTVector& vObjPos, const LTVector& vObjForward, 
											HOBJECT& hOutObj, LTRigidTransform& tOutTrans)
{
	//default our output parameters to reasonable values
	hOutObj = NULL;
	tOutTrans.Init();

	//perform a ray intersection from our position along our Y axis and see if we hit anything.
	//If we do, create the effect there facing along the specified vector, randomly twisted

	//find the starting and ending points
	LTVector vStart = vObjPos + vObjForward * GetProps()->m_fMinDist;
	LTVector vEnd   = vObjPos + vObjForward * GetProps()->m_fMaxDist;

	//we now need to perform an intersection using these endpoints and see if we hit anything
	IntersectQuery	iQuery;
	IntersectInfo	iInfo;

	iQuery.m_Flags		= INTERSECT_HPOLY | IGNORE_NONSOLID;
	iQuery.m_FilterFn	= NULL;
	iQuery.m_pUserData	= NULL;
	iQuery.m_From		= vStart;
	iQuery.m_To			= vEnd;

	if( !g_pLTClient->IntersectSegment( iQuery, &iInfo ) )
	{
		//we didn't intersect anything, don't create an effect
		return false;
	}

	//determine if we hit the sky
	if(IsSkyPoly(iInfo.m_hPoly))
	{
		//never create an effect on the sky
		return false;
	}

	//we now need to determine the normal of intersection
	LTVector vHitNormal = iInfo.m_Plane.Normal();

	//we hit something, so we can now at least determine the point of intersection
	tOutTrans.m_vPos = iInfo.m_Point + vHitNormal * GetProps()->m_fOffset;

	//the primary vector we wish to align to
	LTVector vAlignment;

	//determine what our dominant axis should be
	switch (GetProps()->m_eAlignment)
	{
	default:
	case CCreateRayProps::eAlign_ToSource:
		vAlignment = -vObjForward;
		break;
	case CCreateRayProps::eAlign_Normal:
		vAlignment = vHitNormal;
		break;
	case CCreateRayProps::eAlign_Outgoing:
		vAlignment = vObjForward - (2.0f * vObjForward.Dot(vHitNormal)) * vHitNormal;
		vAlignment.Normalize();
		break;
	case CCreateRayProps::eAlign_ToViewer:
		{
			LTVector vCameraPos;
			g_pLTClient->GetObjectPos(m_pFxMgr->GetCamera(), &vCameraPos);
			vAlignment = vCameraPos - tOutTrans.m_vPos;
			vAlignment.Normalize();
		}
		break;
	}

	//and generate a randomly twisted orientation around our dominant axis
	tOutTrans.m_rRot = LTRotation(vAlignment, LTVector(0.0f, 1.0f, 0.0f));
	tOutTrans.m_rRot.Rotate(vAlignment, GetRandom(0.0f, MATH_CIRCLE));

	//now if we hit an object, make sure to store that object, and convert the transform into
	//the object's space
	if(iInfo.m_hObject && (g_pLTClient->Physics()->IsWorldObject(iInfo.m_hObject) == LT_NO))
	{
		//store this as our hit object
		hOutObj = iInfo.m_hObject;

		//and convert the transform into that object's space
		LTRigidTransform tObjTrans;
		g_pLTClient->GetObjectTransform(hOutObj, &tObjTrans);
		tOutTrans = tOutTrans.GetInverse() * tOutTrans;
	}

	//success
	return true;
}