    void UpdateAI(const uint32 uiDiff)
    {
// Phase_Idle
        if (m_uiPhase == PHASE_IDLE)
        {
            if (m_uiOrdersTimer < uiDiff)
            {
                switch (rand()%5)
                {
                case 0:
                    DoScriptText(SAY_OFFCOMBAT1, m_creature);
                    break;
                case 1:
                    DoScriptText(SAY_OFFCOMBAT2, m_creature);
                    break;
                case 2:
                    DoScriptText(SAY_OFFCOMBAT3, m_creature);
                    break;
                case 3:
                    DoScriptText(SAY_OFFCOMBAT4, m_creature);
                    break;
                case 4:
                    DoScriptText(SAY_OFFCOMBAT5, m_creature);
                    break;
                }
                m_uiOrdersTimer = 30000;
            }
            else m_uiOrdersTimer -= uiDiff;
            // break;   // might be needed went know till play testing
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Legion Lighting all phases
        if (m_uiLegionLightingTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_LEGION_LIGHTING);
            m_uiLegionLightingTimer = 11000;
        } else m_uiLegionLightingTimer -= uiDiff;

        // soul flay all phases
        if (m_uiSoulFlayTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_SOULFLAY);
            m_uiSoulFlayTimer = 7000;
        } else m_uiSoulFlayTimer -= uiDiff;

// Phase_One
        if (m_uiPhase == PHASE_ONE)
        {
            if (m_uiShieldOrbTimer < uiDiff)  // needs a trigger like a bool that keeps it from casting at everytime the bool would reset every phase or something not sure yet 8)
            {
                for(uint8 i = 0; i < m_uiMaxShieldOrbs; ++i)
                {
                    float angle = (float) rand()*360/RAND_MAX + 1;
                    float homeX = m_creature->GetPositionX() + 20*cos(angle*(M_PI/180));
                    float homeY = m_creature->GetPositionY() + 20*sin(angle*(M_PI/180));
                    m_creature->SummonCreature(NPC_SHIELD_ORB, homeX, homeY, m_creature->GetPositionZ()+15, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                }
                m_uiShieldOrbTimer = 50000;
            }
            else m_uiShieldOrbTimer -= uiDiff;

            //if (m_creature->GetHealthPercent() < 85.0f)
            //m_uiPhase = PHASE_TWO;
        }


    }