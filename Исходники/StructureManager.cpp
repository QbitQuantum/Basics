bool StructureManager::containsStructure(int gid, Vec2 location) {
    for (BrokenStructure* e : *structarray) {
        if (e->getGID() == gid &&
                location.distance(e->location) == 0)
            return true;
    }
    return false;
}