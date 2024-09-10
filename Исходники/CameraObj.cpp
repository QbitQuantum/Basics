void CameraObj::HandleTrigger(HOBJECT hSender, HSTRING hMsg)
{
	if (!g_pServerDE) return;

	char* pMsg = g_pServerDE->GetStringData(hMsg);
	if (!pMsg) return;

	// Turn the camera on
	if (_mbsicmp((const unsigned char*)pMsg, (const unsigned char*)"ON") == 0)
	{
		SetActive(DTRUE);
	}
	
	// Turn the camera off
	else if (_mbsicmp((const unsigned char*)pMsg, (const unsigned char*)"OFF") == 0)
	{
		SetActive(DFALSE);
	}

	// Link to a named object
	else if (strnicmp(pMsg, "LINK", 4) == 0)
	{ 
		if (_mbstrlen(pMsg) >= 6)
		{
			// Skip ahead to the name of the object
			pMsg += 5;

			ObjectList*	pList = g_pServerDE->FindNamedObjects(pMsg);
    		if (pList)
			{
				ObjectLink* pLink = pList->m_pFirstLink;
				if (pLink)
    			{
					SetLinkObject(pLink->m_hObject);
	    		}

				g_pServerDE->RelinquishList(pList);
			}
		}
		else
		{
			SetLinkObject(DNULL);
		}
	}
}