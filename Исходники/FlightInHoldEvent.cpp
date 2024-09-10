int FlightInHoldEvent::Process()
{
	if (m_pCFlight->GetMode() == OnTerminate)
		return 0;


	//ASSERT(m_pCFlight->GetUID() != 34);
	double totalLength = m_pHold->GetPath().GetTotalLength();
	double dist = 0.0;
	if (m_pCFlight->GetResource() == m_pHold)	//already enter hold
		dist = m_pCFlight->GetDistInResource() + double(time - m_pCFlight->GetTime())* m_pCFlight->GetSpeed();

	CPoint2008 pos = m_pHold->GetDistancePoint(((int)dist)% ((int)totalLength));

	if (pos == m_pCFlight->GetPosition())
		pos.setZ(m_pCFlight->GetCurState().m_dAlt);
	else
	{

		//flight down to next height level, the descend angle must no more than 3 degree
		double dAlt =  m_pHold->getAvailableHeight(m_pCFlight);
		if (dAlt != m_pCFlight->GetCurState().m_dAlt)
		{
			double dStep = m_pHold->getAvailableHeight(m_pCFlight) - m_pCFlight->GetCurState().m_dAlt;
			double dStepHeight = (dist-m_pCFlight->GetDistInResource())*tan(ARCMath::DegreesToRadians(3.0));
			if (dStep >0)
				dAlt = m_pCFlight->GetCurState().m_dAlt + (dStepHeight<dStep?dStepHeight:dStep);
			else 
				dAlt = m_pCFlight->GetCurState().m_dAlt - (dStepHeight<-dStep?dStepHeight:-dStep);				
		}
		pos.setZ(dAlt);
	}

	ClearanceItem nextItem(m_pHold,OnWaitInHold,((int)dist)% ((int)totalLength));
	nextItem.SetPosition(pos);
	nextItem.SetTime(time);
	nextItem.SetSpeed(m_pCFlight->GetSpeed());
	nextItem.SetAltitude(pos.getZ());

	m_pCFlight->PerformClearanceItem(nextItem);

	if (m_pHold != NULL)		//the flight max holding time cannot exceed 24h
	{
		AirWayPointInSim* pWaypoint = m_pHold->GetWaypointInSim();
		ElapsedTime tEnter = m_pHold->GetOccupyInstance(m_pCFlight).GetEnterTime();
		if (tEnter + MAXHOLDINGTIME <= time)
		{

			CString strWarn;
			strWarn.Format("The Flight's holding time in %s too long",m_pHold->PrintResource()) ;
			CString strError = _T("AIRCRAFT TERMINATE");
			AirsideSimErrorShown::SimWarning(m_pCFlight,strWarn,strError);

			ClearanceItem newItem(NULL, OnTerminate,0);
			nextItem.SetTime(time);
			nextItem.SetSpeed(0);

			m_pCFlight->PerformClearanceItem(newItem);
			return 0;
		}

		ElapsedTime tMinLap = ElapsedTime((0.33*totalLength)/m_pCFlight->GetSpeed());
		if (m_tHoldTime >= 0L && (m_tHoldTime - tEnter) < tMinLap)
		{
			m_tHoldTime = tEnter + tMinLap;
		}
	}


	if(m_pHold->GetHeadFlightCount(m_pCFlight)>0)	//the flight is not at the lowest level in hold
	{
		double stepLength = totalLength/8.0;
		ElapsedTime nextTime = time + ElapsedTime(stepLength/m_pCFlight->GetSpeed());
		if (m_tHoldTime > 0L && nextTime > m_tHoldTime )
			m_tHoldTime = (nextTime + 10L);

		//ASSERT(m_pCFlight->GetUID() != 31);
		FlightInHoldEvent* pNextEvent = new FlightInHoldEvent(m_pCFlight,m_pHold, m_tHoldTime);
		pNextEvent->setTime(nextTime);
		pNextEvent->addEvent();

		return 0;
	}

	CPoint2008 WPpos = m_pHold->GetDistancePoint(0.0);
//	ElapsedTime dTime = ElapsedTime(pos.distance(WPpos)/m_pCFlight->GetSpeed());

	double dMoveDist = totalLength - m_pCFlight->GetDistInResource();
	ElapsedTime dTime = ElapsedTime(dMoveDist/m_pCFlight->GetSpeed());

	if ((m_tHoldTime >0L && (time+dTime) >= m_tHoldTime))
	{
		ClearanceItem newItem((AirsideResource*)m_pHold->GetWaypointInSim() ,OnWaitInHold, 0.0);
		WPpos.setZ(pos.getZ());
		newItem.SetPosition(WPpos);
		newItem.SetTime(time+dTime);
		newItem.SetSpeed(m_pCFlight->GetSpeed());
		newItem.SetAltitude(pos.getZ());
		Clearance nextClearance;
		ClearanceItem newItemCopy = newItem;
		bool bExit = m_pHold->GetAirRouteNetwork()->IsFlightNeedHolding(m_pCFlight,m_pHold,newItemCopy,nextClearance);
		if (bExit)
		{
			if (m_pCFlight->GetCurDelayLog()->mConflictLocation == FlightConflict::RUNWAY )
			{
				ElapsedTime tAvailableTime = newItem.GetTime();
				ElapsedTime tDelay = m_pCFlight->GetCurDelayLog()->mDelayTime;
				ElapsedTime tStartTime = tAvailableTime - tDelay;
				ResourceDesc resDesc;
				m_pCFlight->GetLandingRunway()->getDesc(resDesc);
				AirsideFlightRunwayDelayLog* pLog = new AirsideFlightRunwayDelayLog(resDesc, tStartTime.asSeconds(), OnLanding, tAvailableTime.asSeconds(), tDelay.asSeconds(), FlightRunwayDelay::LandingRoll);
				pLog->sReasonDetail = "Wave crossings";
				m_pCFlight->LogEventItem(pLog);
			}

			m_pCFlight->EndDelay(newItem);			//end holding delay
			if (nextClearance.GetItemCount())
			{
				ClearanceItem& firstItem = nextClearance.ItemAt(0);
				ElapsedTime startTime = time;
				ElapsedTime endTime = firstItem.GetTime();
				ElapsedTime detaTime = endTime - startTime;
				CString strStartTime = startTime.printTime();
				CString strEndTime = endTime.printTime();
				if (detaTime > 0l && firstItem.GetPosition() == newItem.GetPosition())
				{
					double dHeight = 0.0;
					if (firstItem.GetTime() == newItem.GetTime())
					{
						double stepLength = totalLength/8.0;
						ElapsedTime nextTime = ElapsedTime(stepLength/m_pCFlight->GetSpeed());
						startTime += nextTime;
						CPoint2008 pt;
						for (; startTime < endTime; startTime += nextTime)
						{
							stepIt(startTime,pt);
						}
						stepIt(endTime,pt);
						dHeight = pt.getZ();
					}
					else
					{
						double stepLength = totalLength/8.0;
						ElapsedTime nextTime = ElapsedTime(stepLength/m_pCFlight->GetSpeed());
						startTime += nextTime;
						CPoint2008 pt;
						ElapsedTime tPreTime;
						ElapsedTime tNextTime;
						for (; startTime < endTime; startTime += nextTime)
						{
							double dRouteDist = m_pCFlight->GetDistInResource();
							CPoint2008 flightPos = m_pHold->GetDistancePoint(((int)dRouteDist)% ((int)totalLength));
							ElapsedTime dMoveTime = ElapsedTime(flightPos.distance(WPpos)/m_pCFlight->GetSpeed());
							ElapsedTime tSumTime = startTime + dMoveTime;
							if (tSumTime >= endTime)
							{
								tNextTime = tSumTime - endTime;
								break;
							}
							else
							{
								tPreTime = endTime - tSumTime;
							}
							stepIt(startTime,pt);
						}
						if (tPreTime.getPrecisely() || tNextTime.getPrecisely())
						{
							double dRate = tPreTime / (tPreTime + tNextTime);
							ElapsedTime tMoveTime = nextTime * dRate;
							stepIt(startTime + tMoveTime - nextTime,pt);
						}
						
						//step end item
						{
							CPoint2008 WPpos = m_pHold->GetDistancePoint(0.0);
							ClearanceItem newItem((AirsideResource*)m_pHold->GetWaypointInSim() ,OnWaitInHold, 0.0);
							//WPpos.setZ(pt.getZ());
							double dAlt =  m_pHold->getAvailableHeight(m_pCFlight);
							if (dAlt != m_pCFlight->GetCurState().m_dAlt)
							{
								double dStep = m_pHold->getAvailableHeight(m_pCFlight) - m_pCFlight->GetCurState().m_dAlt;
								double dStepHeight = (dist-m_pCFlight->GetDistInResource())*tan(ARCMath::DegreesToRadians(3.0));
								if (dStep >0)
									dAlt = m_pCFlight->GetCurState().m_dAlt + (dStepHeight<dStep?dStepHeight:dStep);
								else 
									dAlt = m_pCFlight->GetCurState().m_dAlt - (dStepHeight<-dStep?dStepHeight:-dStep);				
							}

							dHeight = dAlt;
							WPpos.setZ(dAlt);
							newItem.SetPosition(WPpos);
							newItem.SetTime(endTime);
							newItem.SetSpeed(m_pCFlight->GetSpeed());
							//	newItem.SetAltitude(pt.getZ());
							newItem.SetAltitude(dAlt);
							m_pCFlight->PerformClearanceItem(newItem);
						}
					}

					firstItem.SetPosition(WPpos);
				//	firstItem.SetAltitude(pt.getZ());
					firstItem.SetAltitude(dHeight);
				}
				else
				{
					m_pCFlight->PerformClearanceItem(newItem);
				}
			}
			else
			{
				m_pCFlight->PerformClearanceItem(newItem);
			}
			m_pCFlight->PerformClearance(nextClearance);
			FlightWakeupEvent* pEvent = new FlightWakeupEvent(m_pCFlight);
			pEvent->setTime(m_pCFlight->GetTime());
			pEvent->addEvent();

		}

		return 0;
	}

	double stepLength = totalLength/8.0;
	ElapsedTime nextTime = time + ElapsedTime(stepLength/m_pCFlight->GetSpeed());
	if ( m_tHoldTime > 0L && nextTime > m_tHoldTime)
		nextTime = m_tHoldTime;

	//ASSERT(m_pCFlight->GetUID() != 31);
	FlightInHoldEvent* pNextEvent = new FlightInHoldEvent(m_pCFlight,m_pHold, m_tHoldTime);
	pNextEvent->setTime(nextTime);
	pNextEvent->addEvent();

	return 0;
	
}