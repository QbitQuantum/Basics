void BouncyBee::checkBombaCollision(Bomba *bomba)
{
    if (!bomba)
        return;
    if (intersects(bomba))
    {
        bomba->setRemove(true);
        hit(bomba->getDamage());
    }
}    