CVariant CKademlia::SetupRoute(const CUInt128& TargetID, CPrivateKey* pEntityKey, int HopLimit, int JumpCount, bool bTrace)
{
	if(!m_pKadHandler)
		return CVariant();

	CPointer<CKadRoute> pRoute = new CKadRouteImpl(TargetID, pEntityKey, m_pLookupManager);

	if(HopLimit != -1)
		pRoute->SetHopLimit(HopLimit);
	if(JumpCount != -1)
		pRoute->SetJumpCount(JumpCount);
	if(bTrace)
		pRoute->EnableTrace();

	if(CKadRoute* pOldRoute = m_pLookupManager->GetRelay(pRoute->GetEntityID())->Cast<CKadRoute>())
		m_pLookupManager->StopLookup(pOldRoute);

	m_pLookupManager->StartLookup(pRoute.Obj());

	return pRoute->GetEntityID();
}