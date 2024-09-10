    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 13349, Plr);

        Menu->AddItem(0, "Arena Vendor"		    , 1);
        Menu->AddItem(0, "Arena Battlemaster"   , 2);
        Menu->AddItem(0, "Black Market"         , 3);
        Menu->AddItem(0, "Exit of Dalaran"	    , 4);

        if(AutoSend)
            Menu->SendTo(Plr);
    }