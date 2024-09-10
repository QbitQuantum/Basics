void ArmyController::CalcEnemyData()
{
    Vector2 selfPos = Center();
    Vector2 otherPos = Vector2::Inf();

    m_closestEnemy.clear();
    m_enemyData.clear();

    for (auto& entityR : g_Game->Enemy()->Entities())
    {
        if (entityR.second->Exists() &&
            entityR.second->P(OP_IsTargetable))
        {
            otherPos = entityR.second->Position();
            int dist = selfPos.Distance(otherPos);
            m_closestEnemy.insert(make_pair(dist, entityR.first));

            auto& dat = m_enemyData[entityR.first];
            dat.Id = entityR.first;
            dat.DistanceToCenter = dist;
            dat.TargetEntityId = entityR.second->TargetId();
        }
    }

    // No enemy close to me
    if (m_closestEnemy.empty())
    {
        m_targetEntityId = INVALID_TID;
    }
    // The closest enemy to me is in sight, and it is not my last chosen one
    else if (m_targetEntityId != m_closestEnemy.begin()->second)
    {
        m_targetEntityId = m_closestEnemy.begin()->second;
        LogInfo("%s chosen enemy target %s", ToString().c_str(), g_Game->Enemy()->GetEntity(m_targetEntityId)->ToString(true).c_str());
    }
}