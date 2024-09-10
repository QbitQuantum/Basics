double CScript::ViewPlayerAllVariableList(const char* cmd, char* retStr)
{
	CPlayer* pPlayer=dynamic_cast<CPlayer*>(p_SrcShape);
	if(pPlayer)
	{
		char szVarInfo[5120];
		_snprintf(szVarInfo, 5120, "All Normal Var Num: %d", pPlayer->GetVariableList()->GetVarNum());
		pPlayer->SendNotifyMessage(szVarInfo, 0xFFFFFFFF, 0x0, eNOTIFYPOS_LEFT_BOTTOM);

		CVariableList::VarList* pVarList = pPlayer->GetVariableList()->GetVarList();
		if(pVarList)
		{
			CVariableList::varlistitr varItr = pVarList->begin();
			for(; varItr != pVarList->end(); varItr++)
			{
				if(varItr->second->Array < 0)
					_snprintf(szVarInfo, 5120, "%s : %s", varItr->first.c_str(), varItr->second->strValue);
				else if(varItr->second->Array == 0)
				{
					_snprintf(szVarInfo, 5120, "%s : %f", varItr->first.c_str(), *((double*)varItr->second->strValue));
				}
				else if(varItr->second->Array > 0)
				{
					_snprintf(szVarInfo, 5120, "%s : ", varItr->first.c_str());

					char szArray[1024];
					for(int i=0; i<varItr->second->Array; i++)
					{
						gcvt(varItr->second->Value[i], 10, szArray);
						strcat(szVarInfo, szArray);
						strcat(szVarInfo, ";");
					}
				}
				pPlayer->SendNotifyMessage(szVarInfo, 0xFFFFFFFF, 0x0, eNOTIFYPOS_LEFT_BOTTOM);
			}
		}

		_snprintf(szVarInfo, 5120, "All GUID Var Num: %d", pPlayer->GetVariableList()->GetGuidNum());
		pPlayer->SendNotifyMessage(szVarInfo, 0xFFFFFFFF, 0x0, eNOTIFYPOS_LEFT_BOTTOM);

		CVariableList::GuidList* pGuidList = pPlayer->GetVariableList()->GetGuidList();
		if(pGuidList)
		{
			CVariableList::GuidList::iterator guidItr = pGuidList->begin();
			for(; guidItr != pGuidList->end(); guidItr++)
			{
				char szGuid[128];
				guidItr->second->tostring(szGuid);
				_snprintf(szVarInfo, 128, "%s : %s", guidItr->first.c_str(), szGuid);
				pPlayer->SendNotifyMessage(szVarInfo, 0xFFFFFFFF, 0x0, eNOTIFYPOS_LEFT_BOTTOM);
			}
		}
	}

	return 0.0f;
}