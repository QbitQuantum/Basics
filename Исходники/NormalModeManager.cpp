int NormalGameModeManager::saveInternalState(uint8_t** out) {
    uint8_t* tmp;
    int parent = GameModeManager::saveInternalState(&tmp);
    int s = sizeof(level) + sizeof(remain) + sizeof(limit);
    uint8_t* ptr = *out = new uint8_t[parent + s];
    MEMPCPY(uint8_t*, ptr, tmp, parent);
    MEMPCPY(uint8_t*, ptr, &level, sizeof(level));
    MEMPCPY(uint8_t*, ptr,  &remain[0], sizeof(remain));
    MEMPCPY(uint8_t*, ptr,  &limit, sizeof(limit));

    TRANSFORM(herisson)->position.x = GameModeManager::position(time / limit);

    delete[] tmp;
    return (parent + s);
}