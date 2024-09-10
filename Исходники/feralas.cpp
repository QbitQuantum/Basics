 void EnterCombat(Unit* /*who*/)
 {
     //For an small probability the npc says something when he get aggro
     if (urand(0, 9) > 7)
         DoScriptText(RAND(SAY_OOX_AGGRO1, SAY_OOX_AGGRO2), me);
 }