            void UpdateAI(const uint32 diff)
            {
                if (!Intro)
                {
                    if (!instance)
                        return;

                    if (Intro_Timer <= diff)
                    {
                        switch (Intro_Phase)
                        {
                        case 1:
                            DoScriptText(SAY_INTRO, me);
                            instance->HandleGameObject(instance->GetData64(DATA_SPHERE_SHIELD), true);
                            ++Intro_Phase;
                            Intro_Timer = 25000;
                            break;
                        case 2:
                            DoScriptText(SAY_AGGRO, me);
                            if (Unit* mellic = Unit::GetUnit(*me, instance->GetData64(DATA_MELLICHAR)))
                            {
                                //should have a better way to do this. possibly spell exist.
                                mellic->setDeathState(JUST_DIED);
                                mellic->SetHealth(0);
                                instance->SetData(TYPE_SHIELD_OPEN, IN_PROGRESS);
                            }
                            ++Intro_Phase;
                            Intro_Timer = 3000;
                            break;
                        case 3:
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                            Intro = true;
                            break;
                        }
                    }
                    else
                        Intro_Timer -=diff;
                }
                if (!UpdateVictim())
                    return;

                if (!IsImage66 && !HealthAbovePct(66))
                {
                    DoSplit(66);
                    IsImage66 = true;
                }
                if (!IsImage33 && !HealthAbovePct(33))
                {
                    DoSplit(33);
                    IsImage33 = true;
                }

                if (MindRend_Timer <= diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1))
                        DoCast(target, SPELL_MIND_REND);
                    else
                        DoCast(me->getVictim(), SPELL_MIND_REND);

                    MindRend_Timer = 8000;
                }
                else
                    MindRend_Timer -=diff;

                if (Fear_Timer <= diff)
                {
                    if (me->IsNonMeleeSpellCasted(false))
                        return;

                    DoScriptText(RAND(SAY_FEAR_1, SAY_FEAR_2), me);

                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1))
                        DoCast(target, SPELL_FEAR);
                    else
                        DoCast(me->getVictim(), SPELL_FEAR);

                    Fear_Timer = 25000;
                }
                else
                    Fear_Timer -=diff;

                if (Domination_Timer <= diff)
                {
                    if (me->IsNonMeleeSpellCasted(false))
                        return;

                    DoScriptText(RAND(SAY_MIND_1, SAY_MIND_2), me);

                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1))
                        DoCast(target, SPELL_DOMINATION);
                    else
                        DoCast(me->getVictim(), SPELL_DOMINATION);

                    Domination_Timer = 16000+rand()%16000;
                }
                else
                    Domination_Timer -=diff;

                if (IsHeroic())
                {
                    if (ManaBurn_Timer <= diff)
                    {
                        if (me->IsNonMeleeSpellCasted(false))
                            return;

                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1))
                            DoCast(target, H_SPELL_MANA_BURN);

                        ManaBurn_Timer = 16000+rand()%16000;
                    }
                    else
                        ManaBurn_Timer -=diff;
                }
                DoMeleeAttackIfReady();
            }