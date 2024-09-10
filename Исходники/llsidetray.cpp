LLPanel* LLSideTray::openChildPanel(LLSideTrayTab* tab, const std::string& panel_name, const LLSD& params)
{
	LLView* view = tab->findChildView(panel_name, true);
	if (!view) return NULL;

	std::string tab_name = tab->getName();

	bool tab_attached = isTabAttached(tab_name);

	if (tab_attached && LLUI::sSettingGroups["config"]->getBOOL("OpenSidePanelsInFloaters"))
	{
		tab->toggleTabDocked();
		tab_attached = false;
	}

	// Select tab and expand Side Tray only when a tab is attached.
	if (tab_attached)
	{
		selectTabByName(tab_name);
		if (mCollapsed)
			expandSideBar();
	}
	else
	{
		LLFloater* floater_tab = LLFloaterReg::getInstance("side_bar_tab", tab_name);
		if (!floater_tab) return NULL;

		floater_tab->openFloater(tab_name);
	}

	LLSideTrayPanelContainer* container = dynamic_cast<LLSideTrayPanelContainer*>(view->getParent());
	if (container)
	{
		LLSD new_params = params;
		new_params[LLSideTrayPanelContainer::PARAM_SUB_PANEL_NAME] = panel_name;
		container->onOpen(new_params);

		return container->getCurrentPanel();
	}

	LLPanel* panel = dynamic_cast<LLPanel*>(view);
	if (panel)
	{
		panel->onOpen(params);
	}

	return panel;
}