/**
 * Loads a given power tree and sets up the menu accordingly
 *
 * @param filename Path to the file that will be loaded
 */
void MenuPowers::loadPowerTree(const std::string &filename) {
	// only load the power tree once per instance
	if (tree_loaded) return;

	// First, parse the power tree file

	FileParser infile;
	// @CLASS MenuPowers: Power tree layout|Description of powers/trees/
	if (infile.open(filename)) {
		while (infile.next()) {
			if (infile.new_section) {
				// for sections that are stored in collections, add a new object here
				if (infile.section == "power") {
					slots.push_back(NULL);
					upgradeButtons.push_back(NULL);
					power_cell.push_back(Power_Menu_Cell());
				}
				else if (infile.section == "upgrade")
					power_cell_upgrade.push_back(Power_Menu_Cell());
				else if (infile.section == "tab")
					tabs.push_back(Power_Menu_Tab());
			}

			if (infile.section == "") {
				// @ATTR background|filename|Filename of the default background image
				if (infile.key == "background") default_background = infile.val;
			}
			else if (infile.section == "tab")
				loadTab(infile);
			else if (infile.section == "power")
				loadPower(infile);
			else if (infile.section == "upgrade")
				loadUpgrade(infile);
		}
		infile.close();
	}

	// save a copy of the base level powers, as they get overwritten during upgrades
	power_cell_base = power_cell;

	// store the appropriate level for all upgrades
	for (size_t i=0; i<power_cell_upgrade.size(); ++i) {
		for (size_t j=0; j<power_cell_base.size(); j++) {
			std::vector<int>::iterator it = std::find(power_cell_base[j].upgrades.begin(), power_cell_base[j].upgrades.end(), power_cell_upgrade[i].id);
			if (it != power_cell_base[j].upgrades.end()) {
				power_cell_upgrade[i].upgrade_level = static_cast<int>(std::distance(power_cell_base[j].upgrades.begin(), it) + 2);
				break;
			}
		}
	}

	// combine base and upgrade powers into a single list
	for (size_t i=0; i<power_cell_base.size(); ++i) {
		power_cell_all.push_back(power_cell_base[i]);
	}
	for (size_t i=0; i<power_cell_upgrade.size(); ++i) {
		power_cell_all.push_back(power_cell_upgrade[i]);
	}

	// save cell indexes for required powers
	for (size_t i=0; i<power_cell_all.size(); ++i) {
		for (size_t j=0; j<power_cell_all[i].requires_power.size(); ++j) {
			int cell_index = getCellByPowerIndex(power_cell_all[i].requires_power[j], power_cell_all);
			power_cell_all[i].requires_power_cell.push_back(cell_index);
		}
	}

	// load any specified graphics into the tree_surf vector
	Image *graphics;
	if (tabs.empty() && default_background != "") {
		graphics = render_device->loadImage(default_background);
		if (graphics) {
			tree_surf.push_back(graphics->createSprite());
			graphics->unref();
		}
	}
	else {
		for (size_t i=0; i<tabs.size(); ++i) {
			if (tabs[i].background == "")
				tabs[i].background = default_background;

			if (tabs[i].background == "") {
				tree_surf.push_back(NULL);
				continue;
			}

			graphics = render_device->loadImage(tabs[i].background);
			if (graphics) {
				tree_surf.push_back(graphics->createSprite());
				graphics->unref();
			}
			else {
				tree_surf.push_back(NULL);
			}
		}
	}

	// If we have more than one tab, create tab_control
	if (!tabs.empty()) {
		tab_control = new WidgetTabControl();

		if (tab_control) {
			// Initialize the tab control.
			tab_control->setMainArea(window_area.x+tab_area.x, window_area.y+tab_area.y, tab_area.w, tab_area.h);

			// Define the header.
			for (size_t i=0; i<tabs.size(); i++)
				tab_control->setTabTitle(static_cast<unsigned>(i), msg->get(tabs[i].title));
			tab_control->updateHeader();

			tablist.add(tab_control);
		}

		tablist_pow.resize(tabs.size());
	}

	// create power slots
	for (size_t i=0; i<slots.size(); i++) {
		if (static_cast<size_t>(power_cell[i].id) < powers->powers.size()) {
			slots[i] = new WidgetSlot(powers->powers[power_cell[i].id].icon);
			slots[i]->setBasePos(power_cell[i].pos.x, power_cell[i].pos.y);

			if (!tablist_pow.empty()) {
				tablist_pow[power_cell[i].tab].add(slots[i]);
				tablist_pow[power_cell[i].tab].setPrevTabList(&tablist);
				tablist_pow[power_cell[i].tab].lock();
			}
			else {
				tablist.add(slots[i]);
			}

			if (upgradeButtons[i] != NULL) {
				upgradeButtons[i]->setBasePos(power_cell[i].pos.x + ICON_SIZE, power_cell[i].pos.y);
			}
		}
	}

	applyPowerUpgrades();

	tree_loaded = true;

	align();
}