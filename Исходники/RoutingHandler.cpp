void CKadHandler::HandleRouteReq(const CVariant& RouteReq, CKadNode* pNode, CComChannel* pChannel)
{
	if(GetParent<CKademlia>()->Cfg()->GetBool("DebugRU"))
		LogLine(LOG_DEBUG, L"Recived 'Route Resuest' from %s", pNode->GetID().ToHex().c_str());

	CVariant RouteRes(CVariant::EMap);

	SKadData* pData = pChannel->GetData<SKadData>();
	CPointer<CKadRelay> pRelay = pData->pLookup->Cast<CKadRelay>();
	if(!pRelay)
	{
		if(!RouteReq.Has("TID")) // this is optional it is not send on a refresn
			throw CException(LOG_ERROR, L"Invalid Lookup Request");

		if(pData->pLookup)
			throw CException(LOG_ERROR, L"Recived Route Resuest for a lookup that is not a CKadRelay");

		CLookupManager* pLookupManager = GetParent<CKademlia>()->Manager();
		pRelay = pLookupManager->GetRelayEx(RouteReq["EID"], RouteReq["TID"]); // find already existing relay for this Entity and target combination
		//ASSERT(pRelay == pLookupManager->GetLookup(RouteReq["LID"])->Cast<CKadRelay>()); // lookup ID should be consistent

		if(!pRelay)
		{
			pRelay = new CKadRelay(RouteReq["TID"], pLookupManager);
			if(pRelay->InitRelay(RouteReq)) // if false it means the lookup is invalid
			{
				pRelay->SetHopLimit(RouteReq.Get("JMPS"));
				pRelay->SetJumpCount(RouteReq.Get("HOPS"));

				pRelay->SetBrancheCount(RouteReq.Get("BRCH"));

				pRelay->SetLookupID(RouteReq["LID"]);
				pLookupManager->StartLookup(pRelay.Obj());

				if(RouteReq.Has("TRACE"))
					pRelay->EnableTrace();
			}
		}

		// For this cahnnel the relay was new, setup BC
		pData->pLookup = CPointer<CKadLookup>(pRelay, true); // weak pointer
		pChannel->AddUpLimit(pData->pLookup->GetUpLimit());
		pChannel->AddDownLimit(pData->pLookup->GetDownLimit());
	}

	string Error = pRelay->AddDownLink(pNode, pChannel); // add or update
	if(!Error.empty())
		RouteRes["ERR"] = Error;

	if(GetParent<CKademlia>()->Cfg()->GetBool("DebugRU"))
		LogLine(LOG_DEBUG, L"Sending 'Route Response' to %s", pNode->GetID().ToHex().c_str());
	pChannel->QueuePacket(KAD_ROUTE_RESPONSE, RouteRes);
}