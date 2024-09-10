		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			Creature* pCreature = (pObject->IsCreature()) ? (TO_CREATURE(pObject)) : NULL;
			if(pCreature == NULL)
				return;

			GossipMenu* Menu;
			switch(IntId)
			{
				case 1:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 13612, plr);
						Menu->AddItem(0, GOSSIP_SCOUTMENU2, 2);
						Menu->SendTo(plr);
					}
					break;
				case 2:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 13613, plr);
						Menu->AddItem(0, GOSSIP_SCOUTMENU3, 3);
						Menu->SendTo(plr);
					}
					break;
				case 3:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 13614, plr);
						Menu->SendTo(plr);

						QuestLogEntry* qle = plr->GetQuestLogForEntry(12864);
						if(qle == NULL || qle->GetMobCount(0) != 0)
							return;

						qle->SetMobCount(0, 1);
						qle->SendUpdateAddKill(0);
						qle->UpdatePlayerFields();
					}
					break;
			}
		}