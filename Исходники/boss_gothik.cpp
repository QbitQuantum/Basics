        void SummonedCreatureJustDied(Creature* pSummoned) override
        {
            m_lSummonedAddGuids.remove(pSummoned->GetObjectGuid());

            if (!m_pInstance)
                return;

            m_pInstance->SetData64(DATA64_GOTH_RIGHT_ANCHOR, pSummoned->GetObjectGuid().GetRawValue());
            if (Creature* pAnchor = m_creature->GetMap()->GetCreature(ObjectGuid(m_pInstance->GetData64(DATA64_GOTH_RIGHT_ANCHOR))))
            {
                switch (pSummoned->GetEntry())
                {
                    // Wrong caster, it expected to be pSummoned.
                    // Mangos deletes the spell event at caster death, so for delayed spell like this
                    // it's just a workaround. Does not affect other than the visual though (+ spell takes longer to "travel")
                case NPC_UNREL_TRAINEE:         m_creature->CastSpell(pAnchor, SPELL_A_TO_ANCHOR_1, true, NULL, NULL, pSummoned->GetObjectGuid()); break;
                case NPC_UNREL_DEATH_KNIGHT:    m_creature->CastSpell(pAnchor, SPELL_B_TO_ANCHOR_1, true, NULL, NULL, pSummoned->GetObjectGuid()); break;
                case NPC_UNREL_RIDER:           m_creature->CastSpell(pAnchor, SPELL_C_TO_ANCHOR_1, true, NULL, NULL, pSummoned->GetObjectGuid()); break;
                }
            }
        }