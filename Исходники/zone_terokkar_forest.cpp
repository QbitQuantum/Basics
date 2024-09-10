 void Reset() override
 {
     Initialize();
     me->SetStandState(UNIT_STAND_STATE_STAND);
     me->setFaction(FACTION_HOSTILE);
 }