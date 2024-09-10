void LLFloaterDirectory::focusCurrentPanel()
{
	LLTabContainerCommon* tabs = LLUICtrlFactory::getTabContainerByName(this, "Directory Tabs");
	if (!tabs) return;

	LLPanel* panel = tabs->getCurrentPanel();
	if (!panel) return;

	panel->setFocus(TRUE);
}