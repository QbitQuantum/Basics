		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 60035, plr);
			Menu->AddItem(0, "What can I purchase?", 1);
			Menu->AddItem(0, "What are Darkmoon Faire Prize Tickets and how do I get them?", 2);
			Menu->AddItem(0, "What are Darkmoon Cards?", 3);
			Menu->AddItem(0, "What other things can I do at the faire?", 4);

			Menu->SendTo(plr);
		}