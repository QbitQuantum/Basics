    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
        GossipMenu *Menu;
                
		switch(pObject->GetEntry())
		{
			case TAXI_BRACK:
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, Plr);
				if (Plr->GetQuestLogForEntry(10162) || Plr->GetQuestLogForEntry(10347))
				{
					Menu->AddItem(0, GOSSIP_MISSIONA, 1);
				}

				if (Plr->GetQuestLogForEntry(10129))
				{
					Menu->AddItem(0, GOSSIP_MISSIONB,2);
				}

				Menu->AddItem(0, GOSSIP_SPINERIDGE, 3);
			}break;
			case TAXI_DABIREE:
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, Plr);
				if ( Plr->GetQuestLogForEntry(10146) )
				{
					Menu->AddItem(0, GOSSIP_MISSIONB,2);
				}
				
				Menu->AddItem(0, GOSSIP_SHATTPOINT,4);
			}break;         
			case TAXI_WINDBELLOW:
 			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, Plr);
				if ( Plr->GetQuestLogForEntry(10163) || Plr->GetQuestLogForEntry(10346) )
				{
						Menu->AddItem( 0, GOSSIP_MISSIONA,              1);
				}
				
				Menu->AddItem( 0, GOSSIP_HONORPOINT,    5);
			}break;
			case TAXI_LEAFBEARD:
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, Plr);
				Menu->AddItem( 0, GOSSIP_SHATTPOINT,    4);                             
			}break;
		}

        if(AutoSend)
            Menu->SendTo(Plr);
    }