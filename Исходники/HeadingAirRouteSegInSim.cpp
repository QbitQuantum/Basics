void HeadingAirRouteSegInSim::CalculateClearanceItems(AirsideFlightInSim* pFlight,FlightRouteInSim* pRoute, ClearanceItem& lastItem, AirsideResource* pNextRes, Clearance& newClearance)
{
	ElapsedTime tEnter = m_pFirstIntersection->getInputPoint()->GetOccupyInstance(pFlight).GetEnterTime();
	ElapsedTime tExit = m_pSecondIntersection->getInputPoint()->GetOccupyInstance(pFlight).GetEnterTime();
	double dSped1 = m_pFirstIntersection->getInputPoint()->GetOccupyInstance(pFlight).GetSpeed();
	double dSped2 = m_pSecondIntersection->getInputPoint()->GetOccupyInstance(pFlight).GetSpeed();
	double dAlt1 = lastItem.GetAltitude();
	double dAlt2 = pRoute->GetRoutePointProperty(m_pSecondIntersection->getInputPoint()).GetAlt();

	ASSERT(dSped1 == lastItem.GetSpeed());	//the speed should be same as last item
	ASSERT(tEnter == lastItem.GetTime());	//the time should be same as last item

	SetEnterTime(pFlight, tEnter,OnTerminal, dSped1);
	SetExitTime(pFlight,tExit);

	AirRoutePointInSim* pPoint = m_pFirstIntersection->getInputPoint();

	CPoint2008 nextPos = GetVectorAvailablePosition(tEnter, tExit, dSped1, dSped2, pNextRes, pFlight);

	CPoint2008 curPos = lastItem.GetPosition();
	if (nextPos != m_pSecondIntersection->getInputPoint()->GetPosition())
	{
		double dDistToNext = curPos.distance(nextPos);
		if (m_HeadingType == Direct )
		{
			double dDistToSecond = nextPos.distance(m_pSecondIntersection->getInputPoint()->GetPosition());
			double dRate = dDistToNext/(dDistToNext + nextPos.distance(m_pSecondIntersection->getInputPoint()->GetPosition()));

			ClearanceItem newItem(this,lastItem.GetMode(),0);
			newItem.SetPosition(nextPos);
			double dNextSpd = dSped1 + (dSped2 - dSped1)*dRate;
			newItem.SetSpeed(dNextSpd);
			ElapsedTime dT =  ElapsedTime(2.0* dDistToNext/(lastItem.GetSpeed() + dNextSpd)) + lastItem.GetTime();
			newItem.SetTime(dT);
			double dNextAlt = dAlt1 + (dAlt2 - dAlt1)* dRate;
			newItem.SetAltitude(dNextAlt);
			lastItem = newItem;
			newClearance.AddItem(newItem);
		}
		else
		{
			CPoint2008 projectPoint = GetProjectionPosition(nextPos,pNextRes,pFlight);
			double dTotalDist = dDistToNext + nextPos.distance(projectPoint) + projectPoint.distance(m_pSecondIntersection->getInputPoint()->GetPosition());
			
			double dRate = dDistToNext/dTotalDist;
			ClearanceItem newItem(this,lastItem.GetMode(),0);
			newItem.SetPosition(nextPos);
			double dNextSpd = dSped1 + (dSped2 - dSped1)*dRate;
			newItem.SetSpeed(dNextSpd);
			ElapsedTime dT = ElapsedTime(double(tExit - tEnter)*dRate) + lastItem.GetTime();
			newItem.SetTime(dT);

			double dNextAlt = dAlt1/* + (dAlt2 - dAlt1)* dRate*/;
			newItem.SetAltitude(dNextAlt);
			lastItem = newItem;
			newClearance.AddItem(newItem);


			double dRate2 = (dDistToNext + nextPos.distance(projectPoint))/dTotalDist;
			ClearanceItem nextItem = lastItem;
			nextItem.SetPosition(projectPoint);
			dNextSpd = dSped1 + (dSped2 - dSped1)*dRate2;
			nextItem.SetSpeed(dNextSpd);
			dT = ElapsedTime(double(tExit - tEnter)*(dRate2 - dRate)) + lastItem.GetTime();
			nextItem.SetTime(dT);
			ASSERT(dT < tExit);
			dNextAlt = dAlt1 + (dAlt2 - dAlt1)* (dRate2 - dRate)/(1 - dRate);
			nextItem.SetAltitude(dNextAlt);
			lastItem = nextItem;
			newClearance.AddItem(nextItem);
		}


	}

	pPoint = m_pSecondIntersection->getInputPoint();
	ClearanceItem newItem2(this,lastItem.GetMode(),0);
	newItem2.SetPosition(pPoint->GetPosition());
	newItem2.SetSpeed(dSped2);
	newItem2.SetTime(tExit);
	newItem2.SetAltitude(dAlt2);
	lastItem = newItem2;
	newClearance.AddItem(newItem2);


}