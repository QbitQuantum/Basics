        void GossipHello(Object* pObject, Player* pPlayer)
        {
            GossipMenu* Menu;
            objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 12252, pPlayer);

            if(pPlayer->HasQuest(11532) || pPlayer->HasQuest(11533))
                Menu->AddItem(ICON_CHAT, pPlayer->GetSession()->LocalizedGossipOption(466), 1);     // Speaking of action, I've been ordered to undertake an air strike.

            if(pPlayer->HasQuest(11543) || pPlayer->HasQuest(11542))
                Menu->AddItem(ICON_CHAT, pPlayer->GetSession()->LocalizedGossipOption(467), 2);     // I need to intercept the Dawnblade reinforcements.

            Menu->SendTo(pPlayer);
        }