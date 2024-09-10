    void SummonedMovementInform(Creature* pSummoned, uint32 uiType, uint32 uiPointId) override
    {
        if (pSummoned->GetEntry() != NPC_GLOB_OF_VISCIDUS || uiType != POINT_MOTION_TYPE || !uiPointId)
            return;

        m_lGlobesGuidList.remove(pSummoned->GetObjectGuid());
        pSummoned->CastSpell(m_creature, SPELL_REJOIN_VISCIDUS, TRIGGERED_OLD_TRIGGERED);
        pSummoned->ForcedDespawn(1000);

        if (m_lGlobesGuidList.empty())
        {
            m_creature->SetVisibility(VISIBILITY_ON);
            m_creature->SetStandState(UNIT_STAND_STATE_STAND);
            m_uiPhase = PHASE_NORMAL;

            SetCombatMovement(true);
            DoStartMovement(m_creature->getVictim());
        }
    }