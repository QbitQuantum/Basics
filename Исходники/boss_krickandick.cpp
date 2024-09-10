        void UpdateAI(const uint32 diff)
        {
            if (!me->isInCombat())
                return;

            if (!me->getVictim() && me->getThreatManager().isThreatListEmpty())
            {
                EnterEvadeMode();
                return;
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            switch(events.ExecuteEvent())
            {
                case EVENT_PURSUE:
                    if (Creature* pKrick = GetKrick())
                        DoScriptText(RAND(SAY_KRICK_CHASE_1, SAY_KRICK_CHASE_2, SAY_KRICK_CHASE_3), pKrick);

                    if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    {
                        me->Attack(pTarget, false);
                        DoScriptText(SAY_ICK_CHASE_1, me, pTarget);
                        DoCast(pTarget, SPELL_PURSUED);
                    }

                    DoCast(SPELL_CONFUSION);
                    events.ScheduleEvent(EVENT_PURSUE, 30000, GCD_1);
                    return;

                case EVENT_MIGHTY_KICK:
                    DoCast(me->getVictim(), SPELL_MIGHTY_KICK);
                    events.ScheduleEvent(EVENT_MIGHTY_KICK, 25000, GCD_1);
                    return;

                case EVENT_POISON_NOVA:
                    if (Creature* pKrick = GetKrick())
                        DoScriptText(SAY_KRICK_POISON_NOVA, pKrick);

                    DoScriptText(SAY_ICK_POISON_NOVA, me);
                    DoCastAOE(SPELL_POISON_NOVA);
                    events.ScheduleEvent(EVENT_POISON_NOVA, 30000, GCD_1);
                    return;

                case EVENT_TOXIC_WASTE:
                    DoCast(me->getVictim(), SPELL_TOXIC_WASTE);
                    events.ScheduleEvent(EVENT_TOXIC_WASTE, 5000);
                    return;

                case EVENT_SHADOW_BOLT:
                    DoCast(me->getVictim(), SPELL_SHADOW_BOLT);
                    events.ScheduleEvent(EVENT_SHADOW_BOLT, 15000);
                    return;

                case EVENT_EXPLOSIVE_BARRAGE:
                    if (Creature *pKrick = GetKrick())
                    {
                        DoScriptText(SAY_KRICK_BARRAGE_1, pKrick);
                        DoScriptText(SAY_KRICK_BARRAGE_2, pKrick);
                    }

                    DoCastAOE(SPELL_EXPLOSIVE_BARRAGE);
                    me->GetMotionMaster()->MoveIdle();
                    events.DelayEvents(20000, GCD_1); // 2 sec cast + 18 sec
                    events.ScheduleEvent(EVENT_END_EXPLOSIVE_BARRAGE, 20000);
                    return;

                case EVENT_END_EXPLOSIVE_BARRAGE:
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveChase(me->getVictim());
                    events.ScheduleEvent(EVENT_EXPLOSIVE_BARRAGE, 25000);
                    break;
            }

            DoMeleeAttackIfReady();
        }