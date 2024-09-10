//static
LLFloater* LLFloaterReg::getInstance(const std::string& name, const LLSD& key) 
{
	LLFloater* res = findInstance(name, key);
	if (!res)
	{
		const LLFloaterBuildFunc& build_func = sBuildMap[name].mFunc;
		const std::string& xui_file = sBuildMap[name].mFile;
		if (build_func)
		{
			const std::string& groupname = sGroupMap[name];
			if (!groupname.empty())
			{
				instance_list_t& list = sInstanceMap[groupname];
				int index = list.size();

				res = build_func(key);
				
				bool success = res->buildFromFile(xui_file, NULL);
				if (!success)
				{
					llwarns << "Failed to build floater type: '" << name << "'." << llendl;
					return NULL;
				}
					
				// Note: key should eventually be a non optional LLFloater arg; for now, set mKey to be safe
				res->mKey = key;
				res->setInstanceName(name);
				
				// AO: Mark certain floaters (sidebar tab floaters) as needing to be pseudo-hidden on minimization.
				// At the moment we flag this pseudo hiding with the presence of a dummy control in floater_side_bar_tab.xml
				// and the name of the floater window. This should be refactored into a floater attribute.
				llinfos << "trying to restore variables for name: " << name << llendl;
				std::string pat = "side_bar_tab";
				size_t found = name.find(pat);
				if (found!=std::string::npos)
				{
					if (!res->hasChild("showMinimized"))
						res->setHideOnMinimize(true);
				}
				
				res->applySavedVariables(); // Can't apply rect and dock state until setting instance name
				if (res->mAutoTile && !res->getHost() && index > 0)
				{
					const LLRect& cur_rect = res->getRect();
					LLRect next_rect = getFloaterRect(groupname);
					next_rect.setLeftTopAndSize(next_rect.mLeft, next_rect.mTop, cur_rect.getWidth(), cur_rect.getHeight());
					res->setRect(next_rect);
					res->setRectControl(LLStringUtil::null); // don't save rect of tiled floaters
					gFloaterView->adjustToFitScreen(res, true);
				}
				else
				{
					gFloaterView->adjustToFitScreen(res, false);
				}
				list.push_back(res);
			}
		}
		if (!res)
		{
			llwarns << "Floater type: '" << name << "' not registered." << llendl;
		}
	}
	return res;
}