 void SummonedCreatureDespawn(Creature* pSummoned) override
 {
     m_lZombieChowGuidList.remove(pSummoned->GetObjectGuid());
 }