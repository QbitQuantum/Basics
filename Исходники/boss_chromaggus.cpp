    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        //Shimmer_Timer Timer
        if (Shimmer_Timer <= diff)
        {
            //Remove old vulnerabilty spell
            if (CurrentVurln_Spell)
                me->RemoveAurasDueToSpell(CurrentVurln_Spell);

            //Cast new random vulnerabilty on self
            uint32 spell = RAND(SPELL_FIRE_VULNERABILITY, SPELL_FROST_VULNERABILITY,
                SPELL_SHADOW_VULNERABILITY, SPELL_NATURE_VULNERABILITY, SPELL_ARCANE_VULNERABILITY);

            DoCast(me, spell);
            CurrentVurln_Spell = spell;

            DoScriptText(EMOTE_SHIMMER, me);
            Shimmer_Timer = 45000;
        } else Shimmer_Timer -= diff;

        //Breath1_Timer
        if (Breath1_Timer <= diff)
        {
            DoCast(me->getVictim(), Breath1_Spell);
            Breath1_Timer = 60000;
        } else Breath1_Timer -= diff;

        //Breath2_Timer
        if (Breath2_Timer <= diff)
        {
            DoCast(me->getVictim(), Breath2_Spell);
            Breath2_Timer = 60000;
        } else Breath2_Timer -= diff;

        //Affliction_Timer
        if (Affliction_Timer <= diff)
        {
            std::list<HostileReference*> threatlist = me->getThreatManager().getThreatList();
            for (std::list<HostileReference*>::const_iterator i = threatlist.begin(); i != threatlist.end(); ++i)
            {
                Unit* pUnit;
                if ((*i) && (*i)->getSource())
                {
                    pUnit = Unit::GetUnit((*me), (*i)->getUnitGuid());
                    if (pUnit)
                    {
                        //Cast affliction
                        DoCast(pUnit, RAND(SPELL_BROODAF_BLUE, SPELL_BROODAF_BLACK,
                                           SPELL_BROODAF_RED, SPELL_BROODAF_BRONZE, SPELL_BROODAF_GREEN), true);

                        //Chromatic mutation if target is effected by all afflictions
                        if (pUnit->HasAura(SPELL_BROODAF_BLUE, 0)
                            && pUnit->HasAura(SPELL_BROODAF_BLACK, 0)
                            && pUnit->HasAura(SPELL_BROODAF_RED, 0)
                            && pUnit->HasAura(SPELL_BROODAF_BRONZE, 0)
                            && pUnit->HasAura(SPELL_BROODAF_GREEN, 0))
                        {
                            //pTarget->RemoveAllAuras();
                            //DoCast(pTarget, SPELL_CHROMATIC_MUT_1);

                            //Chromatic mutation is causing issues
                            //Assuming it is caused by a lack of core support for Charm
                            //So instead we instant kill our target

                            //WORKAROUND
                            if (pUnit->GetTypeId() == TYPEID_PLAYER)
                                pUnit->CastSpell(pUnit, 5, false);
                        }
                    }
                }
            }

            Affliction_Timer = 10000;
        } else Affliction_Timer -= diff;

        //Frenzy_Timer
        if (Frenzy_Timer <= diff)
        {
            DoCast(me, SPELL_FRENZY);
            DoScriptText(EMOTE_FRENZY, me);
            Frenzy_Timer = urand(10000,15000);
        } else Frenzy_Timer -= diff;

        //Enrage if not already enraged and below 20%
        if (!Enraged && (me->GetHealth()*100 / me->GetMaxHealth()) < 20)
        {
            DoCast(me, SPELL_ENRAGE);
            Enraged = true;
        }

        DoMeleeAttackIfReady();
    }