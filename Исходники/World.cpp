bool World::resetTet(TetrominoType* type) {
    Vec2d* newCoords = new Vec2d(spawnPoint);
    if (nextTet == nullptr) {
        TetrominoType* randomType = typeFactory->getRandomType();
        int spawnOffset = randomType->getHeight();
        newCoords->setY(newCoords->getY() - spawnOffset);
        activeTet = tetFactory->getTetromino(randomType, newCoords)->withDirection(defaultDirection);
    } else {
        delete activeTet;
        activeTet = nextTet;
    }

    type = typeFactory->getRandomType();
    int spawnOffset = type->getHeight();
    delete newCoords;

    newCoords = new Vec2d(spawnPoint);
    if (mode == INFINITY_MODE) newCoords->setX((rand() % 8) + 1);
    newCoords->setY(newCoords->getY() - spawnOffset);
    nextTet = tetFactory->getTetromino(type, newCoords)->withDirection(defaultDirection);
    
    Translation translation = Translation(activeTet->getCoords());
    
    vector<Quad*>* resetQuads = translation.transform(activeTet->getQuads());
    bool success = !heap->collidesWithQuads(resetQuads);
    
    Quad::deleteQuads(resetQuads, true);

    delete newCoords;
    
    return success;
}