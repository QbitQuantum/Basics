int TilesAttackGameModeManager::saveInternalState(uint8_t** out) {
    uint8_t* tmp;
    int parent = GameModeManager::saveInternalState(&tmp);
    int s = sizeof(leavesDone);
    uint8_t* ptr = *out = new uint8_t[parent + s];
    MEMPCPY(uint8_t*, ptr, tmp, parent);
    MEMPCPY(uint8_t*, ptr, &leavesDone, sizeof(leavesDone));

	TRANSFORM(herisson)->position.x = GameModeManager::position(leavesDone);

    delete[] tmp;
    return (parent + s);
}