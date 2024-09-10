bool CraftingManager::HandleCreatePrototype(Object* object, Object* target,Message* message, ObjectControllerCmdProperties* cmdProperties)
{
    PlayerObject*		player	= dynamic_cast<PlayerObject*>(object);
    CraftingSession*	session	= player->getCraftingSession();
    BString				dataStr;
    uint32				mode,counter;

    if(!session)
        return false;

    message->getStringUnicode16(dataStr);

    if(swscanf(dataStr.getUnicode16(),L"%u %u",&counter,&mode) != 2)
    {
        gCraftingSessionFactory->destroySession(player->getCraftingSession());
        return false;
    }

    session->createPrototype(mode,counter);
    return true;
}