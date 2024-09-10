 void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * EnteredCode)
 {
     GossipMenu* Menu;
     switch(IntId)
     {
     case 1:
     {
         objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2236, Plr);
         Menu->AddItem(2, RHA_GOSSIP_ITEM_2, 2);
         Menu->SendTo(Plr);
     }
     break;
     case 2:
     {
         objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2237, Plr);
         Menu->AddItem(2, RHA_GOSSIP_ITEM_3, 3);
         Menu->SendTo(Plr);
     }
     break;
     case 3:
     {
         objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2238, Plr);
         Menu->AddItem(2, RHA_GOSSIP_ITEM_4, 4);
         Menu->SendTo(Plr);
     }
     break;
     case 4:
     {
         objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2239, Plr);
         Menu->AddItem(2, RHA_GOSSIP_ITEM_5, 5);
         Menu->SendTo(Plr);
     }
     break;
     case 5:
     {
         Plr->Gossip_Complete();
         sQuestMgr.OnPlayerExploreArea(Plr, 3702);
     }
     break;
     }
 }