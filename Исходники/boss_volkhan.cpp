        void UpdateAI(const uint32 uiDiff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            //exploit fix, remove later
            if (m_uiCheckZ <= uiDiff)
            {
                if (me->GetPositionZ() < 50.0f)
                {
                    EnterEvadeMode();
                    return;
                }
                m_uiCheckZ = 1000;
            }
            else m_uiCheckZ -= uiDiff;

            if (m_bIsStriking && !m_bMove)
            {
                if (m_uiPause_Timer <= uiDiff)
                {
                    if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != TARGETED_MOTION_TYPE)
                    {
                        if (me->getVictim())
                            me->GetMotionMaster()->MoveChase(me->getVictim());
                    }

                    m_bHasTemper = false;
                    m_bIsStriking = false;
                    m_uiPause_Timer = 1500;
                }
                else
                    m_uiPause_Timer -= uiDiff;

                return;
            }

            // ShatteringStomp all the Time, 
            if (!m_bHasTemper && !m_bMove)
            {
                if (m_uiShatteringStomp_Timer <= uiDiff)
                {
                    DoScriptText(RAND(SAY_STOMP_1,SAY_STOMP_2), me);

                    DoCast(me, DUNGEON_MODE(SPELL_SHATTERING_STOMP_N,SPELL_SHATTERING_STOMP_H));

                    if (Creature* temp = me->FindNearestCreature(NPC_BRITTLE_GOLEM,99))
                    {
                    DoScriptText(EMOTE_SHATTER, me);
                    m_bCanShatterGolem = true;
                }

                    m_uiShatteringStomp_Timer = 30000;
                }
                else
                    m_uiShatteringStomp_Timer -= uiDiff;
            }

            // Shatter Golems 3 seconds after Shattering Stomp
            if (m_bCanShatterGolem)
            {
                if (m_uiShatter_Timer <= uiDiff)
                {
                    ShatterGolem();
                    m_uiShatter_Timer = 3000;
                    m_bCanShatterGolem = false;
                }
                else
                    m_uiShatter_Timer -= uiDiff;
            }

            Creature* pAnvil = m_pInstance->instance->GetCreature(m_pInstance->GetData64(DATA_VOLKHAN_ANVIL));

            float fX, fY, fZ;
            me->GetContactPoint(pAnvil, fX, fY, fZ, INTERACTION_DISTANCE);

            // Health check
            if (!m_bCanShatterGolem && me->HealthBelowPct(100 - 20 * m_uiHealthAmountModifier) && !m_bMove)
            {
                ++m_uiHealthAmountModifier;

                if (me->IsNonMeleeSpellCasted(false))
                    me->InterruptNonMeleeSpells(false);

                DoScriptText(RAND(SAY_FORGE_1, SAY_FORGE_2), me);


                if (me->GetDistance(pAnvil) > 5)
                {
                    me->GetMotionMaster()->Clear();
                    me->SetReactState(REACT_PASSIVE);
                    me->GetMotionMaster()->MovePoint(5,fX,fY,fZ);
            }

                    DoScriptText(EMOTE_TO_ANVIL, me);
                m_bMove=true;
                    }

            if (me->IsWithinMeleeRange(pAnvil,5) && m_bMove)
            {
                me->GetMotionMaster()->Clear();
                            me->SetReactState(REACT_AGGRESSIVE);
                m_bHasTemper = true;
                m_bMove=false;
                        for (uint8 i = 0; i < MAX_GOLEM; ++i)
                {
                    DoCast(SPELL_SUMMON_MOLTEN_GOLEM);
                }
                DoCast(SPELL_TEMPER);
                    m_bIsStriking = true;
            }

            if (me->GetMotionMaster()->GetCurrentMovementGeneratorType()!=POINT_MOTION_TYPE && m_bMove)
                //if (m_uiCheckTimer<=uiDiff)
                {
                    me->GetMotionMaster()->MovePoint(5,fX,fY,fZ);
                    m_uiCheckTimer=1100;
                }
                //else
                    //m_uiCheckTimer-=uiDiff;


            DoMeleeAttackIfReady();
        }