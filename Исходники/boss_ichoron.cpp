 void KilledUnit(Unit * victim)
 {
     if (victim == me)
         return;
     DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2,SAY_SLAY_3), me);
 }