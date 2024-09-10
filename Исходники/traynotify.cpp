void NotifyArea::read_config()
{
	bool clock_visible = true;

	 // read notification icon settings from XML configuration
	XMLPos cfg_pos = g_Globals.get_cfg();

#ifndef __MINGW32__	// SHRestricted() missing in MinGW (as of 29.10.2003)
	if (!g_Globals._SHRestricted || !SHRestricted(REST_HIDECLOCK))
#endif
	{
		if (cfg_pos.go_down("desktopbar")) {
			clock_visible = XMLBoolRef(XMLPos(cfg_pos,"options"), "show-clock", !get_hide_clock_from_registry());
			cfg_pos.back();
		}
	}

	if (cfg_pos.go_down("notify-icons")) {
		XMLPos options(cfg_pos, "options");

		_hide_inactive = XMLBool(options, "hide-inactive", true);	///@todo read default setting from registry
		_show_hidden = XMLBool(options, "show-hidden", false);	///@todo read default setting from registry
		_show_button = XMLBool(options, "show-button", true);

		XMLChildrenFilter icons(cfg_pos, "icon");

		for(XMLChildrenFilter::iterator it=icons.begin(); it!=icons.end(); ++it) {
			const XMLNode& node = **it;

			NotifyIconConfig cfg;

			cfg._name = node.get("name").c_str();
			cfg._tipText = node.get("text").c_str();
			cfg._windowTitle = node.get("window").c_str();
			cfg._modulePath = node.get("module").c_str();
			const string& mode = node.get("show");

			if (mode == "show")
				cfg._mode = NIM_SHOW;
			else if (mode == "hide")
				cfg._mode = NIM_HIDE;
			else //if (mode == "auto")
				cfg._mode = NIM_HIDE;

			_cfg.push_back(cfg);
		}

		cfg_pos.back();
	}

	show_clock(clock_visible);
}