    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

        //Check for Frost Bolt
        if (FrostBolt_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_FROST_BOLT);
            FrostBolt_Timer = (rand()%60)*1000;
        }else FrostBolt_Timer -= diff;

        //Check for Frost Bolt Nova
        if (FrostBoltNova_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_FROST_BOLT_NOVA);
            FrostBoltNova_Timer = 15000;
        }else FrostBoltNova_Timer -= diff;

        //Check for Chains Of Kelthuzad
        if (ChainsOfKelthuzad_Timer < diff)
        {
            //DoCast(m_creature->getVictim(),SPELL_CHAINS_OF_KELTHUZAD);

            //if (rand()%2)
                //DoScriptText(SAY_CHAIN1, m_creature);
            //else
                //DoScriptText(SAY_CHAIN2, m_creature);

            ChainsOfKelthuzad_Timer = (rand()%30+30)*1000;
        }else ChainsOfKelthuzad_Timer -= diff;

        //Check for Mana Detonation
        if (ManaDetonation_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_MANA_DETONATION);

            if (rand()%2)
                DoScriptText(SAY_SPECIAL1_MANA_DET, m_creature);

            ManaDetonation_Timer = 20000;
        }else ManaDetonation_Timer -= diff;

        //Check for Shadow Fissure
        if (ShadowFisure_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_SHADOW_FISURE);

            if (rand()%2)
                DoScriptText(SAY_SPECIAL3_MANA_DET, m_creature);

            ShadowFisure_Timer = 25000;
        }else ShadowFisure_Timer -= diff;

        //Check for Frost Blast
        if (FrostBlast_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_FROST_BLAST);

            if (rand()%2)
                DoScriptText(SAY_FROST_BLAST, m_creature);

            FrostBlast_Timer = (rand()%30+30)*1000;
        }else FrostBlast_Timer -= diff;

        //start phase 3 when we are 40% health
        if (!Phase3 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 40)
        {
            Phase3 = true;
            DoScriptText(SAY_REQUEST_AID, m_creature);
            //here Lich King should respond to KelThuzad but I don't know which creature to make talk
            //so for now just make Kelthuzad says it.
            DoScriptText(SAY_ANSWER_REQUEST, m_creature);
        }

        if (Phase3 && (GuardiansOfIcecrown_Count < 5))
        {
            if (GuardiansOfIcecrown_Timer < diff)
            {
                //Summon a Guardian of Icecrown in a random alcove (Creature # 16441)
                //uint32 TimeToWalk;
                Creature* pUnit = NULL;

                float Walk_Pos_X;
                float Walk_Pos_Y;
                float Walk_Pos_Z;

                switch(rand()%6)
                {
                    case 0:
                        pUnit = m_creature->SummonCreature(16441,ADDX_LEFT_FAR,ADDY_LEFT_FAR,ADDZ_LEFT_FAR,ADDO_LEFT_FAR,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,1000);
                        //Setting walk position
                        Walk_Pos_X = WALKX_LEFT_FAR;
                        Walk_Pos_Y = WALKY_LEFT_FAR;
                        Walk_Pos_Z = WALKZ_LEFT_FAR;
                        break;
                    case 1:
                        pUnit = m_creature->SummonCreature(16441,ADDX_LEFT_MIDDLE,ADDY_LEFT_MIDDLE,ADDZ_LEFT_MIDDLE,ADDO_LEFT_MIDDLE,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,1000);
                        //Start moving guardian towards the center of the room
                        Walk_Pos_X = WALKX_LEFT_MIDDLE;
                        Walk_Pos_Y = WALKY_LEFT_MIDDLE;
                        Walk_Pos_Z = WALKZ_LEFT_MIDDLE;
                        break;
                    case 2:
                        pUnit = m_creature->SummonCreature(16441,ADDX_LEFT_NEAR,ADDY_LEFT_NEAR,ADDZ_LEFT_NEAR,ADDO_LEFT_NEAR,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,1000);
                        //Start moving guardian towards the center of the room
                        Walk_Pos_X = WALKX_LEFT_NEAR;
                        Walk_Pos_Y = WALKY_LEFT_NEAR;
                        Walk_Pos_Z = WALKZ_LEFT_NEAR;
                        break;
                    case 3:
                        pUnit = m_creature->SummonCreature(16441,ADDX_RIGHT_FAR,ADDY_RIGHT_FAR,ADDZ_RIGHT_FAR,ADDO_RIGHT_FAR,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,1000);
                        //Start moving guardian towards the center of the room
                        Walk_Pos_X = WALKX_RIGHT_FAR;
                        Walk_Pos_Y = WALKY_RIGHT_FAR;
                        Walk_Pos_Z = WALKZ_RIGHT_FAR;
                        break;
                    case 4:
                        pUnit = m_creature->SummonCreature(16441,ADDX_RIGHT_MIDDLE,ADDY_RIGHT_MIDDLE,ADDZ_RIGHT_MIDDLE,ADDO_RIGHT_MIDDLE,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,1000);
                        //Start moving guardian towards the center of the room
                        Walk_Pos_X = WALKX_RIGHT_MIDDLE;
                        Walk_Pos_Y = WALKY_RIGHT_MIDDLE;
                        Walk_Pos_Z = WALKZ_RIGHT_MIDDLE;
                        break;
                    case 5:
                        pUnit = m_creature->SummonCreature(16441,ADDX_RIGHT_NEAR,ADDY_RIGHT_NEAR,ADDZ_RIGHT_NEAR,ADDO_RIGHT_NEAR,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,1000);
                        //Start moving guardian towards the center of the room
                        Walk_Pos_X = WALKX_RIGHT_NEAR;
                        Walk_Pos_Y = WALKY_RIGHT_NEAR;
                        Walk_Pos_Z = WALKZ_RIGHT_NEAR;
                        break;
                }

                if (pUnit)
                {
                    //if we find no one to figth walk to the center
                    if (!pUnit->isInCombat())
                        pUnit->SendMonsterMoveWithSpeed(Walk_Pos_X,Walk_Pos_Y,Walk_Pos_Z);

                    //Safe storing of creatures
                    GuardiansOfIcecrown[GuardiansOfIcecrown_Count] = pUnit->GetGUID();

                    //Update guardian count
                    GuardiansOfIcecrown_Count++;
                }

                //5 seconds until summoning next guardian
                GuardiansOfIcecrown_Timer = 5000;
            }else GuardiansOfIcecrown_Timer -= diff;
        }

        DoMeleeAttackIfReady();
    }