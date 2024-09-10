 void SummonedCreatureDespawn(Creature* pSummoned) override
 {
     m_lSummonedBombGUIDs.remove(pSummoned->GetObjectGuid());
 }