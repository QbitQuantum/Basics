//-----------------------------------------------------------------------------
// rebuild()
//-----------------------------------------------------------------------------
void LLUICtrlFactory::rebuild()
{
	built_panel_t built_panels = mBuiltPanels;
	mBuiltPanels.clear();
	built_panel_t::iterator built_panel_it;
	for (built_panel_it = built_panels.begin();
		built_panel_it != built_panels.end();
		++built_panel_it)
	{
		std::string filename = built_panel_it->second;
		LLPanel* panelp = built_panel_it->first.get();
		if (!panelp)
		{
			continue;
		}
		llinfos << "Rebuilding UI panel " << panelp->getName() 
			<< " from " << filename
			<< llendl;
		BOOL visible = panelp->getVisible();
		panelp->setVisible(FALSE);
		panelp->setFocus(FALSE);
		panelp->deleteAllChildren();

		buildPanel(panelp, filename.c_str(), &panelp->getFactoryMap());
		panelp->setVisible(visible);
	}

	built_floater_t::iterator built_floater_it;
	for (built_floater_it = mBuiltFloaters.begin();
		built_floater_it != mBuiltFloaters.end();
		++built_floater_it)
	{
		LLFloater* floaterp = built_floater_it->first.get();
		if (!floaterp)
		{
			continue;
		}
		std::string filename = built_floater_it->second;
		llinfos << "Rebuilding UI floater " << floaterp->getName()
			<< " from " << filename
			<< llendl;
		BOOL visible = floaterp->getVisible();
		floaterp->setVisible(FALSE);
		floaterp->setFocus(FALSE);
		floaterp->deleteAllChildren();

		gFloaterView->removeChild(floaterp);
		buildFloater(floaterp, filename, &floaterp->getFactoryMap());
		floaterp->setVisible(visible);
	}
}