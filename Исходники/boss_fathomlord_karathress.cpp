        void UpdateAI(const uint32 diff)
        {
            //Only if not incombat check if the event is started
            if (!me->isInCombat() && pInstance && pInstance->GetData(DATA_KARATHRESSEVENT))
            {
                Unit *pTarget = Unit::GetUnit((*me), pInstance->GetData64(DATA_KARATHRESSEVENT_STARTER));

                if (pTarget)
                {
                    AttackStart(pTarget);
                }
            }

            //Return since we have no target
            if (!UpdateVictim())
                return;

            //someone evaded!
            if (pInstance && !pInstance->GetData(DATA_KARATHRESSEVENT))
            {
                EnterEvadeMode();
                return;
            }

            //WaterBoltVolley_Timer
            if (WaterBoltVolley_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_WATER_BOLT_VOLLEY);
                WaterBoltVolley_Timer = 30000;
            } else WaterBoltVolley_Timer -= diff;

            //TidalSurge_Timer
            if (TidalSurge_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_TIDAL_SURGE);
                // Hacky way to do it - won't trigger elseways
                me->getVictim()->CastSpell(me->getVictim(), SPELL_TIDAL_SURGE_FREEZE, true);
                TidalSurge_Timer = 15000+rand()%5000;
            } else TidalSurge_Timer -= diff;

            //Cyclone_Timer
            if (Cyclone_Timer <= diff)
            {
                //DoCast(me, SPELL_SUMMON_CYCLONE); // Doesn't work
                Cyclone_Timer = 30000+rand()%10000;
                Creature *Cyclone = me->SummonCreature(CREATURE_CYCLONE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), float(rand()%5), TEMPSUMMON_TIMED_DESPAWN, 15000);
                if (Cyclone)
                {
                    CAST_CRE(Cyclone)->SetFloatValue(OBJECT_FIELD_SCALE_X, 3.0f);
                    Cyclone->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    Cyclone->setFaction(me->getFaction());
                    Cyclone->CastSpell(Cyclone, SPELL_CYCLONE_CYCLONE, true);
                    Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);
                    if (pTarget)
                    {
                        Cyclone->AI()->AttackStart(pTarget);
                    }
                }
            } else Cyclone_Timer -= diff;

            //Heal_Timer
            if (Heal_Timer <= diff)
            {
                // It can be cast on any of the mobs
                Unit *pUnit = NULL;

                while (pUnit == NULL || !pUnit->isAlive())
                {
                    pUnit = selectAdvisorUnit();
                }

                if (pUnit && pUnit->isAlive())
                    DoCast(pUnit, SPELL_HEAL);
                Heal_Timer = 60000;
            } else Heal_Timer -= diff;

            DoMeleeAttackIfReady();
        }