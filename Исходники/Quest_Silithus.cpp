		void GossipHello(Object* pObject, Player* Plr)
		{
			GossipMenu* Menu;
			QuestLogEntry* en = Plr->GetQuestLogForEntry(8304);

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 7736, Plr);

			if(en && en->GetMobCount(1) < en->GetQuest()->required_mobcount[1])
				Menu->AddItem(0, "Hello, Rutgar. The Commander has sent me here to gather some information about his missing wife.", 3);

			Menu->SendTo(Plr);
		}