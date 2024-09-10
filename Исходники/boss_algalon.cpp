    // Activate a random Constellation
    void ActivateRandomConstellation()
    {
        // spawn a new set of constellations if empty
        if (m_lConstellationsGuids.empty())
        {
            DoSpawnConstellations();
            m_uiConstellationTimer = 5000;
            return;
        }

        GuidList::iterator iter = m_lConstellationsGuids.begin();
        advance(iter, urand(0, m_lConstellationsGuids.size() - 1));

        if (Creature* pConstellation = m_creature->GetMap()->GetCreature(*iter))
        {
            // follow second top aggro player
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1, uint32(0), SELECT_FLAG_PLAYER))
            {
                pConstellation->GetMotionMaster()->MoveFollow(pTarget, CONTACT_DISTANCE, 0);
                SendAIEvent(AI_EVENT_CUSTOM_A, m_creature, pConstellation);
                ++m_uiActiveConstelations;
            }
        }

        m_lConstellationsGuids.remove(*iter);
    }