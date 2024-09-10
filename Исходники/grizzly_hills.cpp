    void UpdateEscortAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // special script for snake fight
        if (m_uiActivateMummiesTimer)
        {
            if (m_uiActivateMummiesTimer <= uiDiff)
            {
                if (Creature* pTecahuna = m_creature->GetMap()->GetCreature(m_tecahunaGuid))
                {
                    // activate 2 mummies at each turn
                    for (uint8 i = 0; i < 2; ++i)
                    {
                        if (Creature* pBunny = m_creature->GetMap()->GetCreature(m_lImmolationBunnyGuids.front()))
                        {
                            pTecahuna->CastSpell(pBunny, SPELL_TECAHUNA_SPIRIT_BEAM, TRIGGERED_OLD_TRIGGERED);
                            pBunny->CastSpell(pBunny, SPELL_SUMMON_DRAKKARI_KING, TRIGGERED_OLD_TRIGGERED, NULL, NULL, m_creature->GetObjectGuid());
                            pBunny->RemoveAurasDueToSpell(SPELL_BUNNY_IMMOLATION);
                            m_lImmolationBunnyGuids.remove(m_lImmolationBunnyGuids.front());
                        }
                    }
                }

                // set timer based on the remaining mummies
                if (m_lImmolationBunnyGuids.empty())
                    m_uiActivateMummiesTimer = 0;
                else
                    m_uiActivateMummiesTimer = urand(5000, 10000);
            }
            else
                m_uiActivateMummiesTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }