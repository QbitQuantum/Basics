// Ulduar Teleporter
void UlduarTeleporter::GossipHello(ObjectPointer  pObject, PlayerPointer Plr, bool AutoSend)
{
	GossipMenu *Menu;
    objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 0, Plr);

    Menu->AddItem(0, "Teleport to the Expedition Base Camp.", 0);
    Menu->AddItem(0, "Teleport to the Formation Grounds.", 1);
    Menu->AddItem(0, "Teleport to the Colossal Forge.", 2);

    if(AutoSend)
		Menu->SendTo(Plr);
};