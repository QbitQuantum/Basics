    void GossipHello(Object* pObject, Player * plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11469, plr);

		if(plr->GetQuestLogForEntry(11223))
        Menu->AddItem( 0, GOSSIP_ARCHMAGE_MALIN, 1);
        
        if(AutoSend)
            Menu->SendTo(plr);
    }