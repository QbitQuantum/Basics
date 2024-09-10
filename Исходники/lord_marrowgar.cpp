	void KilledUnit(Unit *victim)
    {
        DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2), me);
    }