void ObjectController::_handleTip(uint64 targetId,Message* message,ObjectControllerCmdProperties* cmdProperties)
{

    // Message can appear as follows:
    //
    // (uint32)playerID bank	<- banktip in case the client knows the target
    // (uint32)playerID			<- inventory tip in case the client knows the target
    // (string)playerName bank	<- banktip in case the client doesn't know the target
    //
    // can't inventory-tip someone out of range so we can assume
    // the client will send the ID rather than the name in case
    // of an inventory tip.
    BString attribute, str;
    message->getStringUnicode16(str);
    attribute = str;
    attribute.convert(BSTRType_ANSI);

    PlayerObject*	player		 = dynamic_cast<PlayerObject*>(mObject);
    PlayerObject*	target		 = dynamic_cast<PlayerObject*>(gWorldManager->getObjectById(targetId));

    BString			targetName;
    BString			dataStr;
    //int32			amount		 = 0;
    //uint64			transferType = 0;
    BStringVector	dataElements;
    BString			bank;

    attribute.getRawData()[attribute.getLength()] = 0;

    uint32 elementCount = attribute.split(dataElements,' ');

    //do we have the right number of attributes?
    if((elementCount <1) || (elementCount >3))
    {
        gMessageLib->SendSystemMessage(::common::OutOfBand("base_player", "prose_tip_invalid_param", L"", L"", str.getUnicode16()), player);
        return;
    }

    BString lower = dataElements[elementCount-1];

    // Have to convert BEFORE using toLower, since the conversion done there is removed It will assert().
    // Either do the conversion HERE, or better fix the toLower so it handles unicode also.
    dataStr.convert(BSTRType_ANSI);
    lower.toLower();

    //check for banktip
    if((lower.getCrc() == BString("bank").getCrc())&&(elementCount > 1))
    {
        uint32 amount	= atoi(dataElements[elementCount-2].getAnsi());
        bool havetarget = false;

        BString name;
        if(target && (target != player))
        {
            havetarget = true;
            name = target->GetCreature()->getFirstName().c_str();
        }

        if(elementCount == 3)
        {
            havetarget = true;
            name = dataElements[0];
        }

        if((amount >0)&& (amount < 999999999)&&(havetarget))
        {
            //now call the treasury, find that offline bloke and get going
            gTreasuryManager->bankTipOffline(amount,player,name);
            return;
        }

        if(targetId && (!havetarget))
        {
            //please note that this is rather complex as we have a targetid even if we explicitly names a target
            gMessageLib->SendSystemMessage(L"You may only /tip or /tip bank to other players.", player);
            return;
        }
    }

    if(target == player)
    {
        gMessageLib->SendSystemMessage(L"You may only /tip or /tip bank to other players.", player);
        return;
    }

    if((elementCount == 1)&&(target))
    {
        uint32 amount	= atoi(dataElements[0].getAnsi());
        if(amount>0 && (amount < 1000001))
        {
            gTreasuryManager->inventoryTipOnline(amount,player,target);
            return;
        }
    }

    if(targetId && (!target))
    {
        //please note that this is rather complex as we have a targetid even if we explicitely name a target
        gMessageLib->SendSystemMessage(L"You may only /tip or /tip bank to other players.", player);
        return;
    }

    gMessageLib->SendSystemMessage(::common::OutOfBand("base_player", "prose_tip_invalid_param", L"", L"", str.getUnicode16()), player);
    return;


}