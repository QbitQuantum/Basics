void AirsideFollowMeCarInSim::ServicingFlight()
{
	double dDist = m_pServiceFlight->GetDistInResource() + m_pServiceFlight->GetLogEntry().GetAirsideDescStruct().dLength;
	CPoint2008 CarPos = m_pServiceFlight->GetResource()->GetDistancePoint(dDist);

	SetMode(OnService);
	SetSpeed(m_pServiceFlight->GetSpeed());
	ElapsedTime tTime = ElapsedTime(2.0*CarPos.distance(GetPosition())/GetSpeed()) + GetTime();
	SetTime(tTime);
	if(GetResource() != m_pServiceFlight->GetResource())
		GetResource()->SetExitTime(this,tTime);
	SetResource(m_pServiceFlight->GetResource());
	SetPosition(CarPos);
	SetDistInResource(dDist);
	WirteLog(CarPos,GetSpeed(),tTime);

	m_pServiceFlight->SetBeginFollowMeCarService();

	AirsideFollowMeCarServiceEvent* pEvent = new AirsideFollowMeCarServiceEvent(m_pServiceFlight);
	pEvent->setTime(tTime);
	pEvent->addEvent();
}