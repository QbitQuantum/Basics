bool CModelToolCharDataTable::LoadProperty(const char * lpszFullPathFileName)
{
	CNtlXMLDoc doc;
	if(doc.Create() == false)
	{
		_ASSERT(0);
		return false;
	}
	
	if(doc.Load( const_cast<char *>(lpszFullPathFileName) ) == false)
	{
		_ASSERT(0);
		return false;
	}
	
	char szBuffer[1024];

	if( !doc.GetDataWithXPath(const_cast<char *>(XML_PROP_NAME_ATTRIBUTE), szBuffer, sizeof(szBuffer)) )
	{
		_ASSERT(0);
		return false;
	}

	sMODELTOOL_CHAR_TBLDAT	*pModelToolCharData = new sMODELTOOL_CHAR_TBLDAT;

	Add(szBuffer, pModelToolCharData);

	IXMLDOMNodeList *pAnimDataList = doc.SelectNodeList(XML_PROP_ANIM_DATA_ELEMENT);
	IXMLDOMNode* pAnimDataNode = NULL;

	IXMLDOMNodeList *pAnimEventList = NULL;
	IXMLDOMNode* pAnimEventNode = NULL;

	long	lAnimDataNodeNum = 0;
	long	lAnimEventNodeNum = 0;

	int		nAnimKeyID = 0;
	float	fDurationTime = 0.f;

	BYTE	byPushCount = 0;
	BYTE	byKnockDownCount = 0;
    bool    bKB2Push = false;
	BYTE	byHitCount = 0;
	float	aHitTime[NTL_MAX_SIZE_HIT];

	pAnimDataList->get_length(&lAnimDataNodeNum);
	for(long m = 0; m < lAnimDataNodeNum ; ++m)
	{
		pAnimDataList->get_item(m,&pAnimDataNode);

		if(!doc.GetTextWithAttributeName(pAnimDataNode, XML_PROP_ANIM_DATA_ELEMENT_KEYID_ATTRIBUTE, szBuffer, sizeof(szBuffer)))
		{
			_ASSERT(0);
			return false;
		}
		nAnimKeyID = atoi(szBuffer);

		if(!doc.GetTextWithAttributeName(pAnimDataNode, XML_PROP_ANIM_DATA_ELEMENT_PLAYTIME_ATTRIBUTE, szBuffer, sizeof(szBuffer)))
		{
			_ASSERT(0);
			return false;
		}

		fDurationTime = (float)atof(szBuffer);
		
		pAnimDataNode->selectNodes(L"ANIM_EVENT", &pAnimEventList);
		pAnimEventList->get_length(&lAnimEventNodeNum);

		memset(aHitTime, 0, sizeof(aHitTime));
		for(long n = 0; n < lAnimEventNodeNum; ++n)
		{
			pAnimEventList->get_item(n, &pAnimEventNode);

			if(!doc.GetTextWithAttributeName(pAnimEventNode, XML_PROP_ANIM_DATA_ELEMENT_EVENTID_ATTRIBUTE, szBuffer, sizeof(szBuffer)))
			{
				_ASSERT(0);
				return false;
			}
	
			int nAnimEventID = EVENT_ANIM_NONE;
			int nBehavior = TARGET_BEHAVIOR_NONE;

			nAnimEventID = atoi(szBuffer);

			if(nAnimEventID == EVENT_ANIM_HIT)
			{
				if(!doc.GetTextWithAttributeName(pAnimEventNode, XML_PROP_ANIM_DATA_ELEMENT_HITBEHAVIOR_ATTRIBUTE, szBuffer, sizeof(szBuffer)))
				{
					_ASSERT(0);
					return false;
				}
				
				nBehavior = atoi(szBuffer);

				if(nBehavior == TARGET_BEHAVIOR_PUSH)
				{
					byPushCount++;
				}
				else if(nBehavior == TARGET_BEHAVIOR_KNOCK_DOWN)
				{
					byKnockDownCount++;
					if( byKnockDownCount > 1 )
					{
						_ASSERT(0);
						return false;
					}
				}

				// Hit time
				if(!doc.GetTextWithAttributeName(pAnimEventNode, XML_PROP_ANIM_DATA_ELEMENT_HITTIME_ATTRIBUTE, szBuffer, sizeof(szBuffer)))
				{
					_ASSERT(0);
					return false;
				}

				aHitTime[byHitCount] = (float)atof(szBuffer);
				byHitCount++;

				if(byHitCount > NTL_MAX_SIZE_HIT)
					_ASSERT(0);


				// KB2PUSH
				if(!doc.GetTextWithAttributeName(pAnimEventNode, XML_PROP_ANIM_DATA_ELEMENT_HITKB2PUSH_ATTRIBUTE, szBuffer, sizeof(szBuffer)))
				{
					_ASSERT(0);
					return false;
				}

				if(atoi(szBuffer) == 0)
				{
					bKB2Push = false;
				}
				else
				{
					bKB2Push = true;
				}
			}
            else if(nAnimEventID == EVENT_ANIM_SKILL_CANCEL)
            {
                // time
                if(!doc.GetTextWithAttributeName(pAnimEventNode, XML_PROP_ANIM_DATA_ELEMENT_HITTIME_ATTRIBUTE, szBuffer, sizeof(szBuffer)))
                {
                    _ASSERT(0);
                    return false;
                }

                pModelToolCharData->AddSkillCancelTime(nAnimKeyID, (float)atof(szBuffer));
            }
			
			if(pAnimEventNode)
			{
				pAnimEventNode->Release();
				pAnimEventNode = NULL;
			}
		}

		if( nAnimKeyID != -1 )
			pModelToolCharData->Add(nAnimKeyID, fDurationTime, byPushCount, byKnockDownCount, byHitCount, aHitTime, bKB2Push);

		nAnimKeyID = 0;
		fDurationTime = 0;
		byPushCount = 0;
		byKnockDownCount = 0;
		byHitCount = 0;

		if(pAnimEventList)
		{
			pAnimEventList->Release();
			pAnimEventList = NULL;
		}
		
		if(pAnimDataNode)
		{
			pAnimDataNode->Release(); 
			pAnimDataNode = NULL;
		}
	}

	//pModelToolCharData->GetChainAttack(PC_CLASS_HUMAN_FIGHTER, ITEM_TYPE_UNKNOWN, 6);
	if(pAnimDataList)
	{
		pAnimDataList->Release(); 
		pAnimDataList = NULL;
	}

	char *pTokenStart = NULL;
	char *pTokenEnd = NULL;
	char szToken[64];

	if( !doc.GetDataWithXPath("MODEL_SCRIPT/HEADER/ANIM_BBOX", szBuffer, sizeof(szBuffer)) )
	{
		_ASSERT(0);
		return false;
	}
	
	CNtlVector vTemp;
	pTokenStart = szBuffer;
	pTokenEnd = strstr( szBuffer, ";");
	strncpy_s(szToken, sizeof(szToken), pTokenStart, pTokenEnd - pTokenStart);
	vTemp.x = (float) atof(szToken);

	pTokenStart = pTokenEnd + 1;
	pTokenEnd = strstr( pTokenStart, ";");
	strncpy_s(szToken, sizeof(szToken), pTokenStart, pTokenEnd - pTokenStart);
	vTemp.y = (float) atof(szToken);

	pTokenStart = pTokenEnd + 1;
	strncpy_s(szToken, sizeof(szToken), pTokenStart, strlen(szBuffer));
	vTemp.z = (float) atof(szToken);

	pModelToolCharData->m_vMin.x = -(vTemp.x / 2.0f);
	pModelToolCharData->m_vMin.y = 0.0f;
	pModelToolCharData->m_vMin.z = -(vTemp.z / 2.0f);
	
	pModelToolCharData->m_vMax.x = vTemp.x / 2.0f;
	pModelToolCharData->m_vMax.y = vTemp.y;
	pModelToolCharData->m_vMax.z = vTemp.z / 2.0f;

	if( !doc.GetDataWithXPath("MODEL_SCRIPT/BONE_DATA/BASE_SCALE", szBuffer, sizeof(szBuffer)) )
	{
		_ASSERT(0);
		return false;
	}

	pModelToolCharData->m_fScale = (float) atof(szBuffer);
	
	return true;
}