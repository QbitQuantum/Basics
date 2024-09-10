void CMobController::Move()
{
    if (!PMob->PAI->CanFollowPath())
    {
        return;
    }
    if (PMob->PAI->PathFind->IsFollowingScriptedPath() && PMob->PAI->CanFollowPath())
    {
        PMob->PAI->PathFind->FollowPath();
        return;
    }

    // attempt to teleport
    if (PMob->getMobMod(MOBMOD_TELEPORT_TYPE) == 1)
    {
        if (m_Tick >= m_LastSpecialTime + std::chrono::milliseconds(PMob->getBigMobMod(MOBMOD_TELEPORT_CD)))
        {
            CMobSkill* teleportBegin = battleutils::GetMobSkill(PMob->getMobMod(MOBMOD_TELEPORT_START));

            if (teleportBegin)
            {
                m_LastSpecialTime = m_Tick;
                MobSkill(PMob->targid, teleportBegin->getID());
            }
        }
    }

    bool move = PMob->PAI->PathFind->IsFollowingPath();
    float attack_range = PMob->GetMeleeRange();

    if (PMob->getMobMod(MOBMOD_ATTACK_SKILL_LIST) > 0)
    {
        auto skillList {battleutils::GetMobSkillList(PMob->getMobMod(MOBMOD_ATTACK_SKILL_LIST))};

        if (!skillList.empty())
        {
            auto skill {battleutils::GetMobSkill(skillList.front())};
            if (skill)
            {
                attack_range = skill->getDistance();
            }
        }
    }

    float currentDistance = distance(PMob->loc.p, PTarget->loc.p);
    if (PMob->getMobMod(MOBMOD_SHARE_POS) > 0)
    {
        CMobEntity* posShare = (CMobEntity*)PMob->GetEntity(PMob->getMobMod(MOBMOD_SHARE_POS) + PMob->targid, TYPE_MOB);
        PMob->loc = posShare->loc;
    }
    else if (((currentDistance > attack_range - 0.2f) || move) && PMob->PAI->CanFollowPath())
    {
        //#TODO: can this be moved to scripts entirely?
        if (PMob->getMobMod(MOBMOD_DRAW_IN) > 0)
        {
            if (currentDistance >= PMob->GetMeleeRange() * 2 && battleutils::DrawIn(PTarget, PMob, PMob->GetMeleeRange() - 0.2f))
                FaceTarget();
        }
        if (PMob->speed != 0 && PMob->getMobMod(MOBMOD_NO_MOVE) == 0 && m_Tick >= m_LastSpecialTime)
        {
            // attempt to teleport to target (if in range)
            if (PMob->getMobMod(MOBMOD_TELEPORT_TYPE) == 2)
            {
                CMobSkill* teleportBegin = battleutils::GetMobSkill(PMob->getMobMod(MOBMOD_TELEPORT_START));

                if (teleportBegin && currentDistance <= teleportBegin->getDistance())
                {
                    MobSkill(PMob->targid, teleportBegin->getID());
                    m_LastSpecialTime = m_Tick;
                    return;
                }
            }
            else if (CanMoveForward(currentDistance))
            {
                if (!PMob->PAI->PathFind->IsFollowingPath() || distanceSquared(PMob->PAI->PathFind->GetDestination(), PTarget->loc.p) > 10)
                {
                    //path to the target if we don't have a path already
                    PMob->PAI->PathFind->PathInRange(PTarget->loc.p, attack_range - 0.2f, PATHFLAG_WALLHACK | PATHFLAG_RUN);
                }
                PMob->PAI->PathFind->FollowPath();
                if (!PMob->PAI->PathFind->IsFollowingPath())
                {
                    //arrived at target - move if there is another mob under me
                    if (PTarget->objtype == TYPE_PC)
                    {
                        for (auto PSpawnedMob : static_cast<CCharEntity*>(PTarget)->SpawnMOBList)
                        {
                            if (PSpawnedMob.second != PMob && !PSpawnedMob.second->PAI->PathFind->IsFollowingPath() && distance(PSpawnedMob.second->loc.p, PMob->loc.p) < 1.f)
                            {
                                auto angle = getangle(PMob->loc.p, PTarget->loc.p) + 64;
                                position_t new_pos {PMob->loc.p.x - (cosf(rotationToRadian(angle)) * 1.5f),
                                    PTarget->loc.p.y, PMob->loc.p.z + (sinf(rotationToRadian(angle)) * 1.5f), 0, 0};
                                if (PMob->PAI->PathFind->ValidPosition(new_pos))
                                {
                                    PMob->PAI->PathFind->PathTo(new_pos, PATHFLAG_WALLHACK | PATHFLAG_RUN);
                                }
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                FaceTarget();
            }
        }
    }
    else
    {
        FaceTarget();
    }
}