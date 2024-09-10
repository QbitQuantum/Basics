void ObjectController::_handleBoardTransport(uint64 targetId,Message* message,ObjectControllerCmdProperties* cmdProperties)
{
    PlayerObject*	playerObject	= dynamic_cast<PlayerObject*>(mObject);

    ObjectSet		inRangeObjects;
    float			boardingRange	= 25.0;

    if(playerObject->states.getPosture() == CreaturePosture_SkillAnimating)
    {
        gMessageLib->SendSystemMessage(::common::OutOfBand("error_message", "wrong_state"), playerObject);
        return;
    }

    BString str;
    message->getStringUnicode16(str);
    str.convert(BSTRType_ANSI);
    str.toLower();

    if((str.getCrc() != BString("transport").getCrc()))
    {
        gMessageLib->SendSystemMessage(::common::OutOfBand("travel", "boarding_what_shuttle"), playerObject);
        return;
    }

    gSpatialIndexManager->getObjectsInRange(playerObject,&inRangeObjects,ObjType_Creature | ObjType_NPC, boardingRange, true);

	// iterate through the results
	ObjectSet::iterator it = inRangeObjects.begin();

	while(it != inRangeObjects.end())
	{
        if(Shuttle* shuttle = dynamic_cast<Shuttle*>(*it))
        {
            // in range check
            if(playerObject->getParentId() !=  shuttle->getParentId())
            {
                gMessageLib->SendSystemMessage(::common::OutOfBand("travel", "boarding_too_far"), playerObject);
                return;
            }

            if (!shuttle->availableInPort())
            {
                gMessageLib->SendSystemMessage(::common::OutOfBand("travel", "shuttle_not_available"), playerObject);
                return;
            }

            shuttle->useShuttle(playerObject);

            return;
        }

        ++it;
    }

    gMessageLib->SendSystemMessage(::common::OutOfBand("structure/structure_messages", "boarding_what_shuttle"), playerObject);
}