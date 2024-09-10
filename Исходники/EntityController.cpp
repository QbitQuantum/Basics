TID EntityController::GetClosestEnemyEntityInSight()
{
    if (!IsControllingEntity() ||
        !EntityExists())
        return false;

    EntityList enemies;

    int closestDist = INT_MAX;
    TID closestId = INVALID_TID;
    Vector2 selfPos = Entity()->Position();
    Vector2 otherPos = Vector2::Inf();
    int los = Entity()->Type()->P(TP_LineOfSight);

    // For now, just select the closest entity in sight
    for (auto& entityR : g_Game->Enemy()->Entities())
    {
        if (!Entity()->CanAttack(entityR.first))
            continue;

        otherPos = entityR.second->Position();
        int dist = selfPos.Distance(otherPos);

        if (dist < los && dist < closestDist)
        {
            closestId = entityR.first;
            closestDist = dist;
        }
    }

    return closestId;
}