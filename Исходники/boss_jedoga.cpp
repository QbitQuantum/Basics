    void SummonedCreatureJustDied(Creature* pSummoned) override
    {
        if (pSummoned->GetEntry() == NPC_TWILIGHT_VOLUNTEER)
        {
            m_lVolunteerGuidList.remove(pSummoned->GetObjectGuid());

            if (m_pInstance)
            {
                if (Creature* pTemp = m_creature->GetMap()->GetCreature(m_pInstance->SelectJedogaSacrificeControllerGuid()))
                    pTemp->RemoveAurasDueToSpell(SPELL_SACRIFICE_VISUAL);
            }

            m_creature->GetMotionMaster()->MovePoint(POINT_ID_COMBAT, aJedogaLandingLoc[0], aJedogaLandingLoc[1], aJedogaLandingLoc[2]);
        }
    }