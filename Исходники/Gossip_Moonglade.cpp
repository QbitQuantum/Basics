    void GossipHello(Object* pObject, Player * plr, bool AutoSend)
    {
        GossipMenu *Menu;
		if(plr->getClass() == DRUID && plr->getRace() == RACE_TAUREN){
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4918, plr);
			Menu->AddItem( 0, GOSSIP_BUNTHEN_PLAINSWIND, 1);
		}else if(plr->getClass() == DRUID && plr->getRace() == RACE_NIGHTELF){
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4917, plr);
		}else{
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4916, plr);
        };
        if(AutoSend)
            Menu->SendTo(plr);
    }