 void KilledUnit(Unit* who)
 {
     if (who && who->GetEntry() != ENTRY_VAZRUDEN)
         DoScriptText(RAND(SAY_KILL_1, SAY_KILL_2), me);
 }