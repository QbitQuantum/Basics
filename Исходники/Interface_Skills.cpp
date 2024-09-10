Unit* STDCALL skillsPageMouseDown(sWinMessage* msg)
{
	Unit* ptChar = D2GetClientPlayer();

	if ( active_SkillsPoints && !onRealm && D2isLODGame() && isOnButtonUnassignSkill(D2GetMouseX(),D2GetMouseY()))
	{
		log_msg("push down left button unassign skill\n");
		btnSkillIsDown = 1;
		D2PlaySound(4,0,0,0,0);
		freeMessage(msg);
		return NULL;
	}
	return ptChar;
}