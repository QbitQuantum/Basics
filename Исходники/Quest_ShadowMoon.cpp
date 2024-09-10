        void GossipHello(Object* pObject, Player* plr)
        {
            if(plr->HasQuest(10814))
            {
                GossipMenu* Menu;
                objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10613, plr);
                Menu->AddItem(GOSSIP_ICON_CHAT, plr->GetSession()->LocalizedGossipOption(471), 1);     // I am listening, Dragon

                Menu->SendTo(plr);
            }
        }