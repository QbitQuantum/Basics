 void KilledUnit(Unit* Victim)
 {
     if(!(rand()%5))
         DoScriptText(SAY_SLAY, me);
 }