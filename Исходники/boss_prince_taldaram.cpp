        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;
            if (uiPhaseTimer <= diff)
            {
                switch (Phase)
                {
                    case CASTING_FLAME_SPHERES:
                    {
                        Creature* pSpheres[3];

                        //DoCast(me, SPELL_FLAME_SPHERE_SUMMON_1);
                        pSpheres[0] = DoSpawnCreature(CREATURE_FLAME_SPHERE, 0, 0, 5, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 10*IN_MILLISECONDS);
                        Unit *pSphereTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);
                        if (pSphereTarget && pSpheres[0])
                        {
                            float angle,x,y;
                            angle = pSpheres[0]->GetAngle(pSphereTarget);
                            x = pSpheres[0]->GetPositionX() + DATA_SPHERE_DISTANCE * cos(angle);
                            y = pSpheres[0]->GetPositionY() + DATA_SPHERE_DISTANCE * sin(angle);
                            pSpheres[0]->GetMotionMaster()->MovePoint(0, x, y, pSpheres[0]->GetPositionZ());
                        }
                        if (IsHeroic())
                        {
                            //DoCast(me, H_SPELL_FLAME_SPHERE_SUMMON_1);
                            pSpheres[1] = DoSpawnCreature(H_CREATURE_FLAME_SPHERE_1, 0, 0, 5, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 10*IN_MILLISECONDS);
                            //DoCast(me, H_SPELL_FLAME_SPHERE_SUMMON_2);
                            pSpheres[2] = DoSpawnCreature(H_CREATURE_FLAME_SPHERE_2, 0, 0, 5, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 10*IN_MILLISECONDS);
                            if (pSphereTarget && pSpheres[1] && pSpheres[2])
                            {
                                float angle,x,y;
                                angle = pSpheres[1]->GetAngle(pSphereTarget) + DATA_SPHERE_ANGLE_OFFSET;
                                x = pSpheres[1]->GetPositionX() + DATA_SPHERE_DISTANCE/2 * cos(angle);
                                y = pSpheres[1]->GetPositionY() + DATA_SPHERE_DISTANCE/2 * sin(angle);
                                pSpheres[1]->GetMotionMaster()->MovePoint(0, x, y, pSpheres[1]->GetPositionZ());
                                angle = pSpheres[2]->GetAngle(pSphereTarget) - DATA_SPHERE_ANGLE_OFFSET;
                                x = pSpheres[2]->GetPositionX() + DATA_SPHERE_DISTANCE/2 * cos(angle);
                                y = pSpheres[2]->GetPositionY() + DATA_SPHERE_DISTANCE/2 * sin(angle);
                                pSpheres[2]->GetMotionMaster()->MovePoint(0, x, y, pSpheres[2]->GetPositionZ());
                            }
                        }

                        Phase = NORMAL;
                        uiPhaseTimer = 0;
                        break;
                    }
                    case JUST_VANISHED:
                        if (Unit *pEmbraceTarget = GetEmbraceTarget())
                        {
                            me->GetMotionMaster()->Clear();
                            me->SetSpeed(MOVE_WALK, 2.0f, true);
                            me->GetMotionMaster()->MoveChase(pEmbraceTarget);
                        }
                        Phase = VANISHED;
                        uiPhaseTimer = 1300;
                        break;
                    case VANISHED:
                        if (Unit *pEmbraceTarget = GetEmbraceTarget())
                            DoCast(pEmbraceTarget, SPELL_EMBRACE_OF_THE_VAMPYR);
                        me->GetMotionMaster()->Clear();
                        me->SetSpeed(MOVE_WALK, 1.0f, true);
                        me->GetMotionMaster()->MoveChase(me->getVictim());
                        Phase = FEEDING;
                        uiPhaseTimer = 20*IN_MILLISECONDS;
                        break;
                    case FEEDING:
                        Phase = NORMAL;
                        uiPhaseTimer = 0;
                        uiEmbraceTarget = 0;
                        break;
                    case NORMAL:
                        if (uiBloodthirstTimer <= diff)
                        {
                            DoCast(me->getVictim(), SPELL_BLOODTHIRST);
                            uiBloodthirstTimer = 10*IN_MILLISECONDS;
                        } else uiBloodthirstTimer -= diff;

                        if (uiFlamesphereTimer <= diff)
                        {
                            DoCast(me, SPELL_CONJURE_FLAME_SPHERE);
                            Phase = CASTING_FLAME_SPHERES;
                            uiPhaseTimer = 3*IN_MILLISECONDS + diff;
                            uiFlamesphereTimer = 15*IN_MILLISECONDS;
                        } else uiFlamesphereTimer -= diff;

                        if (uiVanishTimer <= diff)
                        {
                            //Count alive players
                            Unit *pTarget = NULL;
                            std::list<HostileReference *> t_list = me->getThreatManager().getThreatList();
                            std::vector<Unit *> target_list;
                            for (std::list<HostileReference *>::const_iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                            {
                                pTarget = Unit::GetUnit(*me, (*itr)->getUnitGuid());
                                // exclude pets & totems
                                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER && pTarget->isAlive())
                                    target_list.push_back(pTarget);
                                pTarget = NULL;
                            }
                            //He only vanishes if there are 3 or more alive players
                            if (target_list.size() > 2)
                            {
                                DoScriptText(RAND(SAY_VANISH_1,SAY_VANISH_2), me);
                                DoCast(me, SPELL_VANISH);
                                Phase = JUST_VANISHED;
                                uiPhaseTimer = 500;
                                if (Unit* pEmbraceTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                                    uiEmbraceTarget = pEmbraceTarget->GetGUID();

                            }
                            uiVanishTimer = urand(25*IN_MILLISECONDS,35*IN_MILLISECONDS);
                        } else uiVanishTimer -= diff;

                        DoMeleeAttackIfReady();
                    break;
                }
            } else uiPhaseTimer -= diff;
        }