            // *** HANDLED FUNCTION ***
            //Update AI is called Every single map update (roughly once every 50ms if a player is within the grid)
            void UpdateAI(const uint32 uiDiff)
            {
                //Out of combat timers
                if (!me->getVictim())
                {
                    //Random Say timer
                    if (m_uiSayTimer <= uiDiff)
                    {
                        //Random switch between 5 outcomes
                        DoScriptText(RAND(SAY_RANDOM_0, SAY_RANDOM_1, SAY_RANDOM_2, SAY_RANDOM_3, SAY_RANDOM_4), me);

                        m_uiSayTimer = 45000;                      //Say something agian in 45 seconds
                    }
                    else
                        m_uiSayTimer -= uiDiff;

                    //Rebuff timer
                    if (m_uiRebuffTimer <= uiDiff)
                    {
                        DoCast(me, SPELL_BUFF);
                        m_uiRebuffTimer = 900000;                  //Rebuff agian in 15 minutes
                    }
                    else
                        m_uiRebuffTimer -= uiDiff;
                }

                //Return since we have no target
                if (!UpdateVictim())
                    return;

                //Spell 1 timer
                if (m_uiSpell1Timer <= uiDiff)
                {
                    //Cast spell one on our current target.
                    if (rand()%50 > 10)
                        DoCast(me->getVictim(), SPELL_ONE_ALT);
                    else if (me->IsWithinDist(me->getVictim(), 25.0f))
                        DoCast(me->getVictim(), SPELL_ONE);

                    m_uiSpell1Timer = 5000;
                }
                else
                    m_uiSpell1Timer -= uiDiff;

                //Spell 2 timer
                if (m_uiSpell2Timer <= uiDiff)
                {
                    //Cast spell two on our current target.
                    DoCast(me->getVictim(), SPELL_TWO);
                    m_uiSpell2Timer = 37000;
                }
                else
                    m_uiSpell2Timer -= uiDiff;

                //Beserk timer
                if (m_uiPhase > 1)
                {
                    //Spell 3 timer
                    if (m_uiSpell3Timer <= uiDiff)
                    {
                        //Cast spell one on our current target.
                        DoCast(me->getVictim(), SPELL_THREE);

                        m_uiSpell3Timer = 19000;
                    }
                    else
                        m_uiSpell3Timer -= uiDiff;

                    if (m_uiBeserkTimer <= uiDiff)
                    {
                        //Say our line then cast uber death spell
                        DoScriptText(SAY_BERSERK, me, me->getVictim());
                        DoCast(me->getVictim(), SPELL_BERSERK);

                        //Cast our beserk spell agian in 12 seconds if we didn't kill everyone
                        m_uiBeserkTimer = 12000;
                    }
                    else
                        m_uiBeserkTimer -= uiDiff;
                }
                else if (m_uiPhase == 1)                            //Phase timer
                {
                    if (m_uiPhaseTimer <= uiDiff)
                    {
                        //Go to next phase
                        ++m_uiPhase;
                        DoScriptText(SAY_PHASE, me);
                        DoCast(me, SPELL_FRENZY);
                    }
                    else
                        m_uiPhaseTimer -= uiDiff;
                }

                DoMeleeAttackIfReady();
            }