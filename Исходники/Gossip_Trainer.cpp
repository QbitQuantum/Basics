    void GossipHello(Object * pObject, Player * plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 7245, plr);
        
		Menu->AddItem( 0, "Please teach me how to become a hammersmith, Lilith.", 1);
		Menu->AddItem( 0, "I wish to unlearn Hammersmithing!", 2);

        if(AutoSend)
            Menu->SendTo(plr);
    }