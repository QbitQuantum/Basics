    void KilledUnit(Unit* pVictim) override
    {
        // Note: this is called from the Shade, Channeler and Sorcerer script
        // If the function is changed in the future, please review this.
        switch (pVictim->GetEntry())
        {
            case NPC_SHADE_OF_AKAMA:
                m_uiPhase = PHASE_EPILOGUE;

                m_creature->GetMotionMaster()->MovePoint(PHASE_EPILOGUE, afAkamaWP[1].m_fX, afAkamaWP[1].m_fY, afAkamaWP[1].m_fZ);
                break;
            case NPC_ASH_SORCERER:
                // Decrease the sorcerer counter
                m_lSorcerersGUIDList.remove(pVictim->GetObjectGuid());
                break;
            case NPC_ASH_CHANNELER:

                ++m_uiChannelersDead;

                // Move the shade to Akama when all channelers are dead
                // Note: the boss should be already slowly moving, but this isn't possible because of the missing stack for the speed debuff
                if (m_uiChannelersDead == MAX_CHANNELERS)
                {
                    if (m_pInstance)
                    {
                        if (Creature* pShade = m_pInstance->GetSingleCreatureFromStorage(NPC_SHADE_OF_AKAMA))
                        {
                            float fX, fY, fZ;
                            m_creature->GetContactPoint(pShade, fX, fY, fZ);
                            pShade->GetMotionMaster()->MovePoint(1, fX, fY, fZ);
                        }
                    }
                }
                break;
        }
    }