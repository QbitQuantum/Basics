 void EnterCombat(Unit* who)
 {
     DoScriptText(RAND(SAY_AGGRO_1, SAY_AGGRO_2), me, who);
 }