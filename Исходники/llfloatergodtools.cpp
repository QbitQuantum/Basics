// static
void LLFloaterGodTools::show(void *)
{
	LLFloaterGodTools* god_tools = instance();
	god_tools->open();
	LLPanel *panel = god_tools->childGetVisibleTab("GodTools Tabs");
	if (panel) panel->setFocus(TRUE);
	if (god_tools->mPanelObjectTools) god_tools->mPanelObjectTools->setTargetAvatar(LLUUID::null);

	if (gAgent.getRegionHost() != god_tools->mCurrentHost)
	{
		// we're in a new region
		god_tools->sendRegionInfoRequest();
	}
}