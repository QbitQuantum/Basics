LTBOOL CScreenFailure::HandleKeyDown(int key, int rep)
{
	if (key == VK_F9)
	{
		g_pMissionMgr->StartGameFromQuickSave();
		return LTTRUE;
	}
	else if (g_fDuration > g_fMinDelay)
	{
		Escape();
		return LTTRUE;
	}
	return LTFALSE;

}