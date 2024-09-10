// ----------------------------------------------------------------------- //
//
//	ROUTINE:	CLightCycleMgr::UpdateLightCycleTrail
//
//	PURPOSE:	Updates a ligt cyclist's trail
//
// ----------------------------------------------------------------------- //
bool CLightCycleMgr::UpdateLightCycleTrail(LIGHT_CYCLIST* pCyclist, LTVector& vPos, int nTrailID)
{
	ASSERT(pCyclist);
	if(!pCyclist)
		return false;

	LIGHT_CYCLE_TRAIL_POINT newPoint;
	LIGHT_CYCLE_TRAIL_POINT *pOldPoint;
	CreateTrailPointFromVector(newPoint,vPos);

	// See which trail we're dealing with
	LIGHT_CYCLE_TRAIL* pTrail;
	if(nTrailID == CURRENT_TRAIL_ID)
	{
		pTrail = pCyclist->pCurTrail;
	}
	else
	{
		pTrail = pCyclist->FindTrail((uint16)nTrailID);
	}

	ASSERT(pTrail);
	if(!pTrail)
	{
		// We tried to update a non-existant trail
		return false;
	}

	int nPoints = pTrail->collTrailPoints.size();

	if(nPoints > 0)
	{
		// Get the last point
		pOldPoint = &(pTrail->collTrailPoints[nPoints-1]);

		// Save the old forward vector
		LTVector vOldForward = pCyclist->vForward;

		// Compute the forward vector
		pCyclist->vForward.x = newPoint.GetX() - pOldPoint->GetX();
		pCyclist->vForward.y = newPoint.GetY() - pOldPoint->GetY();
		pCyclist->vForward.z = newPoint.GetZ() - pOldPoint->GetZ();
		pCyclist->vForward.Normalize();

		if(nPoints > 1)
		{
			// Check for a turn
			float fDot = (float)(fabs(vOldForward.Dot(pCyclist->vForward)));
			
			// Check for a turn
			if(fDot <= MATH_EPSILON)
			{
				// We have a turn, so we have to do two things:
				// 1) Change our last point into the actual turn point
				// 2) Add on our current location point

				LIGHT_CYCLE_TRAIL_POINT turnPoint;

				// Check to see which axis we were travelling on
				if(((float)fabs(vOldForward.z)) > MATH_EPSILON)
				{
					// We were travelling in the Z direction and now we've turned

					// Set the new forward vector
					if(newPoint.GetX() > pOldPoint->GetX())
					{
						pCyclist->vForward.x = 1.0f;
					}
					else
					{
						pCyclist->vForward.x = -1.0f;
					}

					pCyclist->vForward.z = 0.0f;

					// Now calculate the turn point

					/* o = old point, n = new point, t = turn point

						|	o
						|	|\
					   z|	| \
						|	t--n
						|
						+--------
							x 
					*/
					
					// Turn point is the old X and new Z
					turnPoint.SetX(pOldPoint->GetX());
					turnPoint.SetZ(newPoint.GetZ());
				}
				else
				{
					// We were travelling in the X direction and now we've turned

					// Set the new forward vector
					if(newPoint.GetZ() > pOldPoint->GetZ())
					{
						pCyclist->vForward.z = 1.0f;
					}
					else
					{
						pCyclist->vForward.z = -1.0f;
					}

					pCyclist->vForward.x = 0.0f;

					// Now calculate the turn point

					/* o = old point, n = new point, t = turn point

						|	o--t
						|	 \ |
					   z|	  \|
						|	   n
						|
						+-------
							x
					*/
					
					// Turn point is the old Z, and new X
					turnPoint.SetX(newPoint.GetX());
					turnPoint.SetZ(pOldPoint->GetZ());
				}

				turnPoint.SetY(newPoint.GetY());
				if(pOldPoint->GetY() > (newPoint.GetY() + MATH_EPSILON))
				{
					// We shouldn't be going up/down ramps!
					ASSERT(FALSE);
				}

				// Change the last point to the turn point
				pOldPoint->SetX(turnPoint.GetX());
				pOldPoint->SetY(turnPoint.GetY());
				pOldPoint->SetZ(turnPoint.GetZ());

				// Now add on our current location point
				pTrail->collTrailPoints.push_back(newPoint);

				/************************ TEMP */
						// Let's walk his list of points
						std::vector<LIGHT_CYCLE_TRAIL_POINT>::iterator iter;

						// Walk the list
						int nPoint = 0;
						g_pLTServer->CPrint("\n****\n");
						for(iter=pTrail->collTrailPoints.begin();iter!=pTrail->collTrailPoints.end();iter++)
						{
							g_pLTServer->CPrint("Point %d: <%f, %f, %f>\n",nPoint,iter->GetX(),iter->GetY(),iter->GetZ());
							nPoint++;
						}	
						g_pLTServer->CPrint("****\n");
				/************************ TEMP */
			}
			else
			{
				// We're continuing in the same direction, 
				// so we'll just change the last point to our location
				pOldPoint->SetX(newPoint.GetX());
				pOldPoint->SetY(newPoint.GetY());
				pOldPoint->SetZ(newPoint.GetZ());
			}
		}
		else
		{
			// We only have one point on our list (the starting point)
			// so add a new one
			pTrail->collTrailPoints.push_back(newPoint);
		}
	}
	else
	{
		// We shouldn't ever have no points when we update
		ASSERT(FALSE);
	}

	return true;
}