        void GossipHello(Object* pObject, Player* pPlayer)
        {
            GossipMenu* menu;
            objmgr.CreateGossipMenuForPlayer(&menu, pObject->GetGUID(), MORRIDUNE_ON_HELLO, pPlayer);

            if (pPlayer->IsTeamAlliance())
                menu->AddItem(GOSSIP_ICON_CHAT, pPlayer->GetSession()->LocalizedGossipOption(MORRIDUNE_OPTION_1), 1);
            else
                menu->AddItem(GOSSIP_ICON_CHAT, pPlayer->GetSession()->LocalizedGossipOption(MORRIDUNE_OPTION_2), 2);

            menu->SendTo(pPlayer);
        }