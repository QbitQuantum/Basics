    void SummonedCreatureJustDied(Creature* pSummoned) override
    {
        switch (pSummoned->GetEntry())
        {
            case NPC_INFINITE_ADVERSARY:
            case NPC_INFINITE_AGENT:
            case NPC_INFINITE_HUNTER:
                m_lSummonedGuidsList.remove(pSummoned->GetObjectGuid());

                if (m_lSummonedGuidsList.empty())
                    SetEscortPaused(false);
                break;
            case NPC_LORD_EPOCH:
                m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                break;
        }
    }