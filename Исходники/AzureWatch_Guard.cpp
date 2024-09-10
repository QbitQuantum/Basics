    void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
    {
        GossipMenu *Menu;
        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10066, Plr);
        Menu->AddItem(0, "Bank"					, 1);
        Menu->AddItem(0, "Hippogryph Master"	, 2);
        Menu->AddItem(0, "Guild Master"			, 3);
        Menu->AddItem(0, "Inn"					, 4);
        Menu->AddItem(0, "Stable"				, 5);
        Menu->AddItem(0, "Class Trainer"		, 6);
		Menu->AddItem(0, "Profession Trainer"	, 7);
        if(AutoSend)
            Menu->SendTo(Plr);
    }