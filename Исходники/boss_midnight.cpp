    void UpdateAI(const uint32 diff)
    {
        if (ResetTimer)
        {
            if (ResetTimer <= diff)
            {
                ResetTimer = 0;
                Unit *pMidnight = Unit::GetUnit(*m_creature, Midnight);
                if (pMidnight)
                {
                    pMidnight->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    pMidnight->SetVisibility(VISIBILITY_ON);
                }
                Midnight = 0;
                m_creature->SetVisibility(VISIBILITY_OFF);
                m_creature->Kill(m_creature);
            }
        } else ResetTimer -= diff;

        //Return since we have no target
        if (!UpdateVictim())
            return;

        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE))
            return;

        if (CleaveTimer <= diff)
        {
            DoCast(m_creature->getVictim(), SPELL_SHADOWCLEAVE);
            CleaveTimer = urand(10000,15000);
        } else CleaveTimer -= diff;

        if (CurseTimer <= diff)
        {
            DoCast(m_creature->getVictim(), SPELL_INTANGIBLE_PRESENCE);
            CurseTimer = 30000;
        } else CurseTimer -= diff;

        if (RandomYellTimer <= diff)
        {
            DoScriptText(RAND(SAY_RANDOM1,SAY_RANDOM2), m_creature);
            RandomYellTimer = urand(30000,60000);
        } else RandomYellTimer -= diff;

        if (m_creature->GetUInt32Value(UNIT_FIELD_DISPLAYID) == MOUNTED_DISPLAYID)
        {
            if (ChargeTimer <= diff)
            {
                Unit *pTarget;
                std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
                std::vector<Unit *> target_list;
                for (std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                {
                    pTarget = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid());
                    if (pTarget && !pTarget->IsWithinDist(m_creature, ATTACK_DISTANCE, false))
                        target_list.push_back(pTarget);
                    pTarget = NULL;
                }
                if (target_list.size())
                    pTarget = *(target_list.begin()+rand()%target_list.size());

                DoCast(pTarget, SPELL_BERSERKER_CHARGE);
                ChargeTimer = 20000;
            } else ChargeTimer -= diff;
        }
        else
        {
            if ((m_creature->GetHealth()*100)/m_creature->GetMaxHealth() < 25)
            {
                Creature *pMidnight = Unit::GetCreature(*m_creature, Midnight);
                if (pMidnight && pMidnight->GetTypeId() == TYPEID_UNIT)
                {
                    CAST_AI(boss_midnightAI, (pMidnight->AI()))->Mount(m_creature);
                    m_creature->SetHealth(pMidnight->GetHealth());
                    DoResetThreat();
                }
            }
        }

        DoMeleeAttackIfReady();
    }