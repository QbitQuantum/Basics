        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (HealthBelowPct(10) && !Enraged)
            {
                Enraged = true;
                DoCast(me, SPELL_ENRAGE, true);
                DoScriptText(SAY_ENRAGE, me);
            }

            //Randomly cast one beam.
            if (BeamTimer <= diff)
            {
                Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0);
                if (!pTarget || !pTarget->isAlive())
                    return;

                BeamTimer = 9000;

                switch(CurrentBeam)
                {
                    case 0:
                        DoCast(pTarget, SPELL_BEAM_SINISTER);
                        break;
                    case 1:
                        DoCast(pTarget, SPELL_BEAM_VILE);
                        break;
                    case 2:
                        DoCast(pTarget, SPELL_BEAM_WICKED);
                        break;
                    case 3:
                        DoCast(pTarget, SPELL_BEAM_SINFUL);
                        break;
                }
                ++BeamCount;
                uint32 Beam = CurrentBeam;
                if (BeamCount > 3)
                    while (CurrentBeam == Beam)
                        CurrentBeam = rand()%3;

            } else BeamTimer -= diff;

            // Random Prismatic Shield every 15 seconds.
            if (PrismaticShieldTimer <= diff)
            {
                uint32 random = rand()%6;
                if (PrismaticAuras[random])
                    DoCast(me, PrismaticAuras[random]);
                PrismaticShieldTimer = 15000;
            } else PrismaticShieldTimer -= diff;

            // Select 3 random targets (can select same target more than once), teleport to a random location then make them cast explosions until they get away from each other.
            if (FatalAttractionTimer <= diff)
            {
                ExplosionCount = 0;

                TeleportPlayers();

                DoScriptText(RAND(SAY_SPELL2,SAY_SPELL3), me);
                FatalAttractionExplodeTimer = 2000;
                FatalAttractionTimer = 40000 + rand()%31 * 1000;
            } else FatalAttractionTimer -= diff;

            if (FatalAttractionExplodeTimer <= diff)
            {
                // Just make them explode three times... they're supposed to keep exploding while they are in range, but it'll take too much code. I'll try to think of an efficient way for it later.
                if (ExplosionCount < 3)
                {
                    for (uint8 i = 0; i < 3; ++i)
                    {
                        Unit* pUnit = NULL;
                        if (TargetGUID[i])
                        {
                            pUnit = Unit::GetUnit((*me), TargetGUID[i]);
                            if (pUnit)
                                pUnit->CastSpell(pUnit, SPELL_ATTRACTION, true);
                            TargetGUID[i] = 0;
                        }
                    }

                    ++ExplosionCount;
                    FatalAttractionExplodeTimer = 1000;
                }
                else
                {
                    FatalAttractionExplodeTimer = FatalAttractionTimer + 2000;
                    ExplosionCount = 0;
                }
            } else FatalAttractionExplodeTimer -= diff;

            if (ShriekTimer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SILENCING_SHRIEK);
                ShriekTimer = 25000+rand()%10 * 1000;
            } else ShriekTimer -= diff;

            if (SaberTimer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SABER_LASH);
                SaberTimer = 25000+rand()%10 * 1000;
            } else SaberTimer -= diff;

            //Enrage
            if (!me->HasAura(SPELL_BERSERK))
            {
                if (EnrageTimer <= diff)
                {
                    DoCast(me, SPELL_BERSERK);
                    DoScriptText(SAY_ENRAGE, me);
                } else EnrageTimer -= diff;
            }

            //Random taunts
            if (RandomYellTimer <= diff)
            {
                DoScriptText(RAND(SAY_TAUNT1,SAY_TAUNT2,SAY_TAUNT3), me);
                RandomYellTimer = 60000 + rand()%91 * 1000;
            } else RandomYellTimer -= diff;

            DoMeleeAttackIfReady();
        }