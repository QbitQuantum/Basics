void CharacterService::startMove(const std::shared_ptr<Character> &c, Direction dir)
{
    Level *currentLevel = c->level();
    Room *r = c->room();
    RoomExit *exit = r->exit(dir);
    if (exit) {
        MoveStartEvent(c, exit->targetRoom()).execute();

        Level *targetLevel = exit->targetRoom()->level();
        auto moveEndEvent = new MoveEndEvent(c, exit->targetRoom());
        auto moveEndTime = MUD->timeAfter(travelTime(c, exit->travelDistance()));
        if (currentLevel == targetLevel) {
            currentLevel->eventQueue()->push(moveEndTime, moveEndEvent);
        }
        else {
            MEQ->push(moveEndTime, moveEndEvent);
        }
    }

}