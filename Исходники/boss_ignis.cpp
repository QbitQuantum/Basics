            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_JET:
                            me->MonsterTextEmote(EMOTE_JETS, 0, true);
                            DoCast(me, SPELL_FLAME_JETS);
                            events.ScheduleEvent(EVENT_JET, urand(35000, 40000));
                            break;
                        case EVENT_SLAG_POT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            {
                                DoScriptText(SAY_SLAG_POT, me);
                                _slagPotGUID = target->GetGUID();
                                DoCast(target, SPELL_GRAB);
                                events.DelayEvents(3000);
                                events.ScheduleEvent(EVENT_GRAB_POT, 500);
                            }
                            events.ScheduleEvent(EVENT_SLAG_POT, RAID_MODE(30000, 15000));
                            break;
                        case EVENT_GRAB_POT:
                            if (Unit* slagPotTarget = ObjectAccessor::GetUnit(*me, _slagPotGUID))
                            {
                                slagPotTarget->EnterVehicle(me, 0);
                                events.CancelEvent(EVENT_GRAB_POT);
                                events.ScheduleEvent(EVENT_CHANGE_POT, 1000);
                            }
                            break;
                        case EVENT_CHANGE_POT:
                            if (Unit* slagPotTarget = ObjectAccessor::GetUnit(*me, _slagPotGUID))
                            {
                                slagPotTarget->AddAura(SPELL_SLAG_POT, slagPotTarget);
                                slagPotTarget->EnterVehicle(me, 1);
                                events.CancelEvent(EVENT_CHANGE_POT);
                                events.ScheduleEvent(EVENT_END_POT, 10000);
                            }
                            break;
                        case EVENT_END_POT:
                            if (Unit* slagPotTarget = ObjectAccessor::GetUnit(*me, _slagPotGUID))
                            {
                                slagPotTarget->ExitVehicle();
                                slagPotTarget = NULL;
                                _slagPotGUID = 0;
                                events.CancelEvent(EVENT_END_POT);
                            }
                            break;
                        case EVENT_SCORCH:
                            DoScriptText(RAND(SAY_SCORCH_1, SAY_SCORCH_2), me);
                            if (Unit* target = me->getVictim())
                                me->SummonCreature(NPC_GROUND_SCORCH, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 45000);
                            DoCast(SPELL_SCORCH);
                            events.ScheduleEvent(EVENT_SCORCH, 25000);
                            break;
                        case EVENT_CONSTRUCT:
                            DoScriptText(SAY_SUMMON, me);
                            DoSummon(NPC_IRON_CONSTRUCT, ConstructSpawnPosition[urand(0, CONSTRUCT_SPAWN_POINTS - 1)], 30000, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT);
                            DoCast(SPELL_STRENGHT);
                            DoCast(me, SPELL_ACTIVATE_CONSTRUCT);
                            events.ScheduleEvent(EVENT_CONSTRUCT, RAID_MODE(40000, 30000));
                            break;
                        case EVENT_BERSERK:
                            DoCast(me, SPELL_BERSERK, true);
                            DoScriptText(SAY_BERSERK, me);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }