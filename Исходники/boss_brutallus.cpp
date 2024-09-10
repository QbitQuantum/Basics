        void UpdateAI(const uint32 diff)
        {
            if (IsIntro)
            {
                if (IntroPhaseTimer <= diff)
                    DoIntro();
                else IntroPhaseTimer -= diff;

                if (IntroPhase == 3 + 1)
                {
                    if (IntroFrostBoltTimer <= diff)
                    {
                        if (Creature* Madrigosa = Unit::GetCreature(*me, instance ? instance->GetData64(DATA_MADRIGOSA) : 0))
                        {
                            Madrigosa->CastSpell(me, SPELL_INTRO_FROSTBOLT, true);
                            IntroFrostBoltTimer = 2000;
                        }
                    } else IntroFrostBoltTimer -= diff;
                }
                if (!UpdateVictim())
                    return;
                DoMeleeAttackIfReady();
            }

            if (!UpdateVictim() || IsIntro)
                return;

            if (SlashTimer <= diff)
            {
                DoCast(me->getVictim(), SPELL_METEOR_SLASH);
                SlashTimer = 11000;
            } else SlashTimer -= diff;

            if (StompTimer <= diff)
            {
                DoScriptText(RAND(YELL_LOVE1, YELL_LOVE2, YELL_LOVE3), me);
                DoCast(me->getVictim(), SPELL_STOMP);
                StompTimer = 30000;
            } else StompTimer -= diff;

            if (BurnTimer <= diff)
            {
                std::list<Unit*> targets;
                SelectTargetList(targets, 10, SELECT_TARGET_RANDOM, 100, true);
                for (std::list<Unit*>::const_iterator i = targets.begin(); i != targets.end(); ++i)
                    if (!(*i)->HasAura(SPELL_BURN))
                    {
                        (*i)->CastSpell((*i), SPELL_BURN, true);
                        break;
                    }
                BurnTimer = urand(60000, 180000);
            } else BurnTimer -= diff;

            if (BerserkTimer < diff && !Enraged)
            {
                DoScriptText(YELL_BERSERK, me);
                DoCast(me, SPELL_BERSERK);
                Enraged = true;
            } else BerserkTimer -= diff;

            DoMeleeAttackIfReady();
        }