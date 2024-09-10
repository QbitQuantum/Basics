 void SummonedCreatureJustDied(Creature* pSummoned) override
 {
     if (pSummoned->GetEntry() == NPC_GRUBBIS)
     {
         if (m_pInstance)
             m_pInstance->SetData(TYPE_GRUBBIS, DONE);
         m_uiPhaseTimer = 1000;
     }
     m_luiSummonedMobGUIDs.remove(pSummoned->GetObjectGuid());
 }