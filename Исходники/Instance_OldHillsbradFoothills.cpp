        void GossipHello(Object* pObject, Player* Plr)
        {
            GossipMenu* Menu;
            if (!pObject->IsCreature())
                return;

            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), THRALL_ON_HELLO, Plr);
            Menu->AddItem(GOSSIP_ICON_CHAT, Plr->GetSession()->LocalizedGossipOption(THRALL_START_ESCORT), 1);

            Menu->SendTo(Plr);
        }