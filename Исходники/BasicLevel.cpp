R3Point SpawnLocation() {
    R3Point playerPos = globals.player->GetPosition();
    R3Vector playerDir = globals.player->GetDirection();
    R3Vector playerLeft = R3Vector(R3posy_vector);
    playerLeft.Cross(playerDir);
    return playerPos + Util::SymmetricRandom() * 15.0 * playerLeft + 
                        Util::SymmetricRandom() * 15.0 * R3posy_vector + 
                        (Util::UnitRandom() + 0.3) * 100.0 * playerDir;
}