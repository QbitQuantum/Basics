        void UpdateAI(const uint32 diff)
        {
            switch (Phase)
            {
                case FLYING:
                    if (!UpdateVictim())
                        return;

                    if (me->GetPositionX() >= 519)
                    {
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
                        if (!m_bSaidEmote)
                        {
                            DoScriptText(EMOTE_RANGE, me);
                            m_bSaidEmote = true;
                        }
                    }
                    else
                    {
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
                        m_bSaidEmote = false;
                    }

                    if (m_uiMountTimer && m_uiMountTimer <= diff)
                    {
                        me->Mount(DATA_MOUNT);
                        me->SetCanFly(true);
                        m_uiMountTimer = 0;
                    } else m_uiMountTimer -= diff;

                    if (m_uiSummonTimer <= diff)
                    {
                        SpawnMobs();
                        m_uiSummonTimer = 25000;
                    } else m_uiSummonTimer -= diff;

                    if (m_uiMovementTimer <= diff)
                    {
                        switch (m_uiWaypointId)
                        {
                            case 0:
                                me->GetMotionMaster()->MovePoint(0, Location[1].GetPositionX(), Location[1].GetPositionY(), Location[1].GetPositionZ());
                                m_uiMovementTimer = 5000;
                                break;
                            case 1:
                                me->GetMotionMaster()->MovePoint(0, Location[2].GetPositionX(), Location[2].GetPositionY(), Location[2].GetPositionZ());
                                m_uiMovementTimer = 2000;
                                break;
                            case 2:
                                me->GetMotionMaster()->MovePoint(0, Location[3].GetPositionX(), Location[3].GetPositionY(), Location[3].GetPositionZ());
                                m_uiMovementTimer = 15000;
                                break;
                            case 3:
                                me->GetMotionMaster()->MovePoint(0, Location[69].GetPositionX(), Location[69].GetPositionY(), Location[69].GetPositionZ());
                                DoScriptText(RAND(SAY_DRAKE_BREATH_1, SAY_DRAKE_BREATH_2), me);
                                DoScriptText(EMOTE_BREATH, me);
                                m_uiMovementTimer = 2500;
                                break;
                            case 4:
                                me->GetMotionMaster()->MovePoint(0, Location[70].GetPositionX(), Location[70].GetPositionY(), Location[70].GetPositionZ());
                                m_uiMovementTimer = 2000;
                                SpawnTrigger();
                                break;
                            case 5:
                                me->GetMotionMaster()->MovePoint(0, Location[71].GetPositionX(), Location[71].GetPositionY(), Location[71].GetPositionZ());
                                m_uiMovementTimer = 3000;
                                break;
                            case 6:
                                me->GetMotionMaster()->MovePoint(0, Location[3].GetPositionX(), Location[3].GetPositionY(), Location[3].GetPositionZ());
                                m_uiWaypointId = 2;
                                m_uiMovementTimer = 15000;
                                break;
                        }
                        m_uiWaypointId++;
                    } else m_uiMovementTimer -= diff;
                    break;
                case SKADI:
                    //Return since we have no target
                    if (!UpdateVictim())
                        return;

                    if (m_uiCrushTimer <= diff)
                    {
                        DoCastVictim(SPELL_CRUSH);
                        m_uiCrushTimer = 8000;
                    } else m_uiCrushTimer -= diff;

                    if (m_uiPoisonedSpearTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(target, SPELL_POISONED_SPEAR);
                        m_uiPoisonedSpearTimer = 10000;
                    } else m_uiPoisonedSpearTimer -= diff;

                    if (m_uiWhirlwindTimer <= diff)
                    {
                        DoCastAOE(SPELL_WHIRLWIND);
                        m_uiWhirlwindTimer = 20000;
                    } else m_uiWhirlwindTimer -= diff;

                    DoMeleeAttackIfReady();
                    break;
            }
        }