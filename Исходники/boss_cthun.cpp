        void UpdateAI(uint32 diff) override
        {
            //Check if we have a target
            if (!UpdateVictim())
                return;

            uint32 currentPhase = instance->GetData(DATA_CTHUN_PHASE);
            if (currentPhase == PHASE_EYE_GREEN_BEAM || currentPhase == PHASE_EYE_RED_BEAM)
            {
                // EyeTentacleTimer
                if (EyeTentacleTimer <= diff)
                {
                    //Spawn the 8 Eye Tentacles in the corret spots
                    SpawnEyeTentacle(0, 20);                //south
                    SpawnEyeTentacle(10, 10);               //south west
                    SpawnEyeTentacle(20, 0);                //west
                    SpawnEyeTentacle(10, -10);              //north west

                    SpawnEyeTentacle(0, -20);               //north
                    SpawnEyeTentacle(-10, -10);             //north east
                    SpawnEyeTentacle(-20, 0);               // east
                    SpawnEyeTentacle(-10, 10);              // south east

                    EyeTentacleTimer = 45000;
                } else EyeTentacleTimer -= diff;
            }

            switch (currentPhase)
            {
                case PHASE_EYE_GREEN_BEAM:
                    //BeamTimer
                    if (BeamTimer <= diff)
                    {
                        //SPELL_GREEN_BEAM
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        {
                            me->InterruptNonMeleeSpells(false);
                            DoCast(target, SPELL_GREEN_BEAM);

                            //Correctly update our target
                            me->SetTarget(target->GetGUID());
                        }

                        //Beam every 3 seconds
                        BeamTimer = 3000;
                    } else BeamTimer -= diff;

                    //ClawTentacleTimer
                    if (ClawTentacleTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        {
                            Creature* Spawned = NULL;

                            //Spawn claw tentacle on the random target
                            Spawned = me->SummonCreature(NPC_CLAW_TENTACLE, *target, TEMPSUMMON_CORPSE_DESPAWN, 500);

                            if (Spawned && Spawned->AI())
                                Spawned->AI()->AttackStart(target);
                        }

                        //One claw tentacle every 12.5 seconds
                        ClawTentacleTimer = 12500;
                    } else ClawTentacleTimer -= diff;

                    //PhaseTimer
                    if (PhaseTimer <= diff)
                    {
                        //Switch to Dark Beam
                        instance->SetData(DATA_CTHUN_PHASE, PHASE_EYE_RED_BEAM);

                        me->InterruptNonMeleeSpells(false);
                        me->SetReactState(REACT_PASSIVE);

                        //Remove any target
                        me->SetTarget(ObjectGuid::Empty);

                        //Select random target for dark beam to start on
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        {
                            //Face our target
                            DarkGlareAngle = me->GetAngle(target);
                            DarkGlareTickTimer = 1000;
                            DarkGlareTick = 0;
                            ClockWise = RAND(true, false);
                        }

                        //Add red coloration to C'thun
                        DoCast(me, SPELL_RED_COLORATION, true);

                        //Freeze animation
                        DoCast(me, SPELL_FREEZE_ANIM);
                        me->SetOrientation(DarkGlareAngle);
                        me->StopMoving();

                        //Darkbeam for 35 seconds
                        PhaseTimer = 35000;
                    } else PhaseTimer -= diff;

                    break;

                case PHASE_EYE_RED_BEAM:
                    if (DarkGlareTick < 35)
                    {
                        if (DarkGlareTickTimer <= diff)
                        {
                            //Set angle and cast
                            if (ClockWise)
                                me->SetOrientation(DarkGlareAngle + DarkGlareTick * float(M_PI) / 35);
                            else
                                me->SetOrientation(DarkGlareAngle - DarkGlareTick * float(M_PI) / 35);

                            me->StopMoving();

                            //Actual dark glare cast, maybe something missing here?
                            DoCast(me, SPELL_DARK_GLARE, false);

                            //Increase tick
                            ++DarkGlareTick;

                            //1 second per tick
                            DarkGlareTickTimer = 1000;
                        } else DarkGlareTickTimer -= diff;
                    }

                    //PhaseTimer
                    if (PhaseTimer <= diff)
                    {
                        //Switch to Eye Beam
                        instance->SetData(DATA_CTHUN_PHASE, PHASE_EYE_GREEN_BEAM);

                        BeamTimer = 3000;
                        ClawTentacleTimer = 12500;              //4 per Eye beam phase (unsure if they spawn during Dark beam)

                        me->InterruptNonMeleeSpells(false);

                        //Remove Red coloration from c'thun
                        me->RemoveAurasDueToSpell(SPELL_RED_COLORATION);
                        me->RemoveAurasDueToSpell(SPELL_FREEZE_ANIM);

                        //set it back to aggressive
                        me->SetReactState(REACT_AGGRESSIVE);

                        //Eye Beam for 50 seconds
                        PhaseTimer = 50000;
                    } else PhaseTimer -= diff;

                    break;

                //Transition phase
                case PHASE_CTHUN_TRANSITION:
                    //Remove any target
                    me->SetTarget(ObjectGuid::Empty);
                    me->SetHealth(0);
                    me->SetVisible(false);
                    break;

                //Dead phase
                case PHASE_CTHUN_DONE:
                    Creature* pPortal= me->FindNearestCreature(NPC_CTHUN_PORTAL, 10);
                    if (pPortal)
                        pPortal->DespawnOrUnsummon();

                    me->DespawnOrUnsummon();
                    break;
            }
        }