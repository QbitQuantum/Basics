 void SummonedCreatureJustDied(Creature* pSummoned) override
 {
     if (pSummoned->GetEntry() == NPC_VEKNISS_HATCHLING)
         m_lHatchlingsGUIDs.remove(pSummoned->GetObjectGuid());
 }