 void KilledUnit(Unit* victim)
 {
     if (victim->GetTypeId() == TYPEID_PLAYER)
         Talk(RAND(SAY_PLAYER_KILL_01, SAY_PLAYER_KILL_02));
 }