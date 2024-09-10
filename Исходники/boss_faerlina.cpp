 void KilledUnit(Unit* /*victim*/)
 {
     if (!urand(0, 2))
         DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2), me);
 }