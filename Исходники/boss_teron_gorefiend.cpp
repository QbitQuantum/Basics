    void UpdateAI(const uint32 diff)
    {
        if (Intro)
        {
            if (AggroTimer <= diff)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                DoScriptText(SAY_AGGRO, me);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                Intro = false;
                if (AggroTargetGUID)
                {
                    Unit* pUnit = Unit::GetUnit((*me), AggroTargetGUID);
                    if (pUnit)
                        AttackStart(pUnit);

                    DoZoneInCombat();
                }
                else
                {
                    EnterEvadeMode();
                    return;
                }
            } else AggroTimer -= diff;
        }

        if (!UpdateVictim() || Intro)
            return;

        if (SummonShadowsTimer <= diff)
        {
            //MindControlGhost();

            for (uint8 i = 0; i < 2; ++i)
            {
                Creature* Shadow = NULL;
                float X = CalculateRandomLocation(me->GetPositionX(), 10);
                Shadow = me->SummonCreature(CREATURE_SHADOWY_CONSTRUCT, X, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 0);
                if (Shadow)
                {
                    Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 1);
                    if (!pTarget)
                        pTarget = me->getVictim();

                    if (pTarget)
                        Shadow->AI()->AttackStart(pTarget);
                }
            }
            SummonShadowsTimer = 60000;
        } else SummonShadowsTimer -= diff;

        if (SummonDoomBlossomTimer <= diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
            {
                float X = CalculateRandomLocation(pTarget->GetPositionX(), 20);
                float Y = CalculateRandomLocation(pTarget->GetPositionY(), 20);
                float Z = pTarget->GetPositionZ();
                Z = me->GetMap()->GetHeight(X, Y, Z);
                Creature* DoomBlossom = me->SummonCreature(CREATURE_DOOM_BLOSSOM, X, Y, Z, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);
                if (DoomBlossom)
                {
                    DoomBlossom->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    DoomBlossom->setFaction(me->getFaction());
                    DoomBlossom->AddThreat(pTarget, 1.0f);
                    CAST_AI(mob_doom_blossomAI, DoomBlossom->AI())->SetTeronGUID(me->GetGUID());
                    pTarget->CombatStart(DoomBlossom);
                    SetThreatList(DoomBlossom);
                    SummonDoomBlossomTimer = 35000;
                }
            }
        } else SummonDoomBlossomTimer -= diff;

        if (IncinerateTimer <= diff)
        {
            Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 1);
            if (!pTarget)
                pTarget = me->getVictim();

            if (pTarget)
            {
                DoScriptText(RAND(SAY_SPECIAL1,SAY_SPECIAL2), me);
                DoCast(pTarget, SPELL_INCINERATE);
                IncinerateTimer = 20000 + rand()%31 * 1000;
            }
        } else IncinerateTimer -= diff;

        if (CrushingShadowsTimer <= diff)
        {
            Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);
            if (pTarget && pTarget->isAlive())
                DoCast(pTarget, SPELL_CRUSHING_SHADOWS);
            CrushingShadowsTimer = 10000 + rand()%16 * 1000;
        } else CrushingShadowsTimer -= diff;

        /*** NOTE FOR FUTURE DEV: UNCOMMENT BELOW ONLY IF MIND CONTROL IS FULLY IMPLEMENTED **/
        /*if (ShadowOfDeathTimer <= diff)
        {
            Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 1);

            if (!pTarget)
               pTarget = me->getVictim();

            if (pTarget && pTarget->isAlive() && pTarget->GetTypeId() == TYPEID_PLAYER)
            {
                DoCast(pTarget, SPELL_SHADOW_OF_DEATH);
                GhostGUID = pTarget->GetGUID();
                ShadowOfDeathTimer = 30000;
                SummonShadowsTimer = 53000; // Make it VERY close but slightly less so that we can check if the aura is still on the player
            }
        } else ShadowOfDeathTimer -= diff;*/

        if (RandomYellTimer <= diff)
        {
            DoScriptText(RAND(SAY_SPELL1,SAY_SPELL2), me);
            RandomYellTimer = 50000 + rand()%51 * 1000;
        } else RandomYellTimer -= diff;

        if (!me->HasAura(SPELL_BERSERK, 0))
        {
            if (EnrageTimer <= diff)
        {
            DoCast(me, SPELL_BERSERK);
            DoScriptText(SAY_ENRAGE, me);
        } else EnrageTimer -= diff;
        }

        DoMeleeAttackIfReady();
    }