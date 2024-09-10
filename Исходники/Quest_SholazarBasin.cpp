		void GossipHello(Object* pObject, Player* plr)
		{
			if(plr->HasQuest(12645))
			{
				GossipMenu* Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, plr);
				Menu->AddItem(0, GOSSIP_TASTETEST, 1);

				Menu->SendTo(plr);
			}
		}