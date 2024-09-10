Vec2 MonsterPart::getBulletDierection()
{
    
    Vec2 toEnermy = parent->enermy->GetPosition() - parent->GetPosition();
    toEnermy.normalize();
    Vec2 dir = toEnermy * 2 + randVec2();
    dir.normalize();
    
    return dir;
}