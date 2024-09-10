	void send_MainPage(Object * pObject, Player* Plr)
	{
		if( Plr == false )
			return; 

		GossipMenu *Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, Plr);
		Menu->SetTextID( 20050 );
		Menu->AddItem( 0, "Queue for Maze Event",2);
		Menu->SendTo(Plr);
	}