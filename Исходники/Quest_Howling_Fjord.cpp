	void GossipHello(Object* pObject, Player * plr, bool AutoSend)
    {
		GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, plr);
        Menu->AddItem( 0, "Where would you like to fly too ?", 2); 
        if( plr->GetQuestLogForEntry(11332)!= NULL)
			Menu->AddItem( 0, "Greer, i need a gryphon to ride and some bombs to drop on New Agamand!", 1 );
       

        if(AutoSend)
            Menu->SendTo(plr);
    }