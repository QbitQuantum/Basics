int CKernelOptions::exec(CMenuTarget * parent, const std::string & actionKey)
{
	int res = menu_return::RETURN_REPAINT;

	if (actionKey == "reset") {
		for (unsigned int i = 0; i < modules.size(); i++)
			modules[i].active = modules[i].active_orig;
		updateStatus();
		return res;
	}

	if (actionKey == "apply" || actionKey == "change") {
		bool needs_save = false;
		for (unsigned int i = 0; i < modules.size(); i++)
			if (modules[i].active != modules[i].active_orig) {
				needs_save = true;
				if (modules[i].active)
					loadModule(i);
				else
					unloadModule(i);
				modules[i].active_orig = modules[i].active;
			}
		if (needs_save)
			save();
		updateStatus();
		return res;
	}

	if (parent)
		parent->hide();

	Settings();

	return res;
}