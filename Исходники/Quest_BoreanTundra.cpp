    void GossipHello(Object* pObject, Player* pPlayer)
    {
        GossipMenu* Menu;

        objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, pPlayer);

        Menu->AddItem(0, GOSSIP_ITEM_FREE_FLIGHT, 1);
        Menu->AddItem(3, GOSSIP_ITEM_FLIGHT, 2);

        Menu->SendTo(pPlayer);
    };