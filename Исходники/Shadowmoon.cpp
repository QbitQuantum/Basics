    void GossipSelectOption(ObjectPointer pObject, PlayerPointer plr, uint32 Id, uint32 IntId, const char * Code)
    {
		if(pObject->GetTypeId()!=TYPEID_UNIT)
			return;
		
        switch(IntId)
        {
        case 1:
			{
				GossipMenu * Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10614, plr);
				Menu->AddItem( 0, "But you are dragons! How could orcs do this to you?", 2);
				Menu->SendTo(plr);
            }break;
        case 2:
			{
				GossipMenu * Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10615, plr);
				Menu->AddItem( 0, "Your mate?", 3);
				Menu->SendTo(plr);
            }break;
        case 3:
			{
				GossipMenu * Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10616, plr);
				Menu->AddItem( 0, "I have battled many beasts, dragon. I will help you.", 4);
				Menu->SendTo(plr);
            }break;
        case 4:
			{
				QuestLogEntry *pQuest = plr->GetQuestLogForEntry(10814);
				if ( pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0] )
				{
					pQuest->SetMobCount(0, 1);
					pQuest->SendUpdateAddKill(0);
					pQuest->UpdatePlayerFields();
				}
            }break;
		}
    }