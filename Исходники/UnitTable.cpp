void CUnitTable::Init() {
	// get the unitdefs and stick them in the unitTypes[] array
	numOfUnits = ai->cb->GetNumUnitDefs();
	unitList = new const UnitDef*[numOfUnits];
	ai->cb->GetUnitDefList(unitList);

	// one more than needed because [0] is a dummy object (so
	// UnitDef->id can be used to adress that unit in array)
	unitTypes = new UnitType[numOfUnits + 1];

	// add units to UnitTable
	for (int i = 1; i <= numOfUnits; i++) {
		unitTypes[i].def = unitList[i - 1];
		// side has not been assigned - will be done later
		unitTypes[i].category = -1;

		// GetUnitDefList() filled our unitList
		// partially with null UnitDef*'s (bad,
		// nothing much to do if this happens)
		assert(unitTypes[i].def != 0x0);

		// get build options
		for (map<int, string>::const_iterator j = unitTypes[i].def->buildOptions.begin(); j != unitTypes[i].def->buildOptions.end(); j++) {
			const char* buildOptionName = j->second.c_str();
			const UnitDef* buildOptionDef = ai->cb->GetUnitDef(buildOptionName);
			unitTypes[i].canBuildList.push_back(buildOptionDef->id);
		}
	}

	// now set sides and create buildtree for each
	// note: this skips Lua commanders completely!
	for (int s = 0; s < numOfSides; s++) {
		// set side of start unit (eg. commander) and continue recursively
		int unitDefID = startUnits[s];
		unitTypes[unitDefID].sides.insert(s);

		CalcBuildTree(unitDefID, s);
	}

	// add unit to different groups
	for (int i = 1; i <= numOfUnits; i++) {
		UnitType* me = &unitTypes[i];

		// KLOOTNOTE: this is a hack to make KAIK recognize Lua
		// commanders ((which are unreachable from the starting
		// units in the mod hierarchy and so will be skipped by
		// CalcBuildTree(), meaning me->sides stays empty)) as
		// builders, but the ground_builders[side] list for this
		// unit might not exist (and will never actually contain
		// this unitDef ID)
		if (/* me->def->isCommander && */ me->def->buildOptions.size() > 0) {
			me->category = CAT_BUILDER;
		}

		for (std::set<int>::iterator it = me->sides.begin(); it != me->sides.end(); it++) {
			int mySide = *it;
			int UnitCost = int(me->def->metalCost * METAL2ENERGY + me->def->energyCost);
			me->TargetCategories.resize(me->def->weapons.size());

			if (me->def->filename.find(".lua") != std::string::npos) {
				// can't parse these without a Lua parser
				for (unsigned int w = 0; w != me->def->weapons.size(); w++) {
					me->TargetCategories[w] = "";
				}
			} else {
				CSunParser attackerParser(ai);
				attackerParser.LoadVirtualFile(me->def->filename.c_str());

				for (unsigned int w = 0; w != me->def->weapons.size(); w++) {
					char weaponnumber[10] = "";
					itoa(w, weaponnumber, 10);
					attackerParser.GetDef(me->TargetCategories[w], "-1", string("UNITINFO\\OnlyTargetCategory") + string(weaponnumber));
				}
			}


			me->DPSvsUnit.resize(numOfUnits + 1);

			// calculate this unit type's DPS against all other unit types
			for (int v = 1; v <= numOfUnits; v++) {
				me->DPSvsUnit[v] = GetDPSvsUnit(me->def, unitTypes[v].def);
			}

			// speed > 0 means we are mobile, minWaterDepth <= 0 means we
			// are allergic to water and cannot be in it (positive values
			// are inverted internally)
			if (me->def->speed > 0.0f /* && me->def->minWaterDepth <= 0 */) {
				if (me->def->buildOptions.size() > 0) {
					ground_builders[mySide].push_back(i);
					me->category = CAT_BUILDER;
				}
				else if (!me->def->weapons.empty() && !me->def->weapons.begin()->def->stockpile) {
					ground_attackers[mySide].push_back(i);
					me->category = CAT_G_ATTACK;
				}
			}



			else if (!me->def->canfly) {
				if (true /* me->def->minWaterDepth <= 0 */) {
					if (me->def->buildOptions.size() >= 1 && me->def->builder) {
						if ((((me->def)->TEDClassString) == "PLANT") || (((me->def)->speed) > 0.0f)) {
							me->isHub = false;
						} else {
							me->isHub = true;
						}

						ground_factories[mySide].push_back(i);
						me->category = CAT_FACTORY;
					}
					else {
						const WeaponDef* weapon = (me->def->weapons.empty())? 0: me->def->weapons.begin()->def;

						if (weapon && !weapon->stockpile && me->def->extractsMetal == 0.0f) {
							// we don't want armed extractors to be seen as general-purpose defense
							if (!weapon->waterweapon) {
								// filter out depth-charge launchers etc
								ground_defences[mySide].push_back(i);
								me->category = CAT_DEFENCE;
							}
						}

						if (me->def->stockpileWeaponDef) {
							if (me->def->stockpileWeaponDef->targetable) {
								// nuke
								nuke_silos[mySide].push_back(i);
								me->category = CAT_NUKE;
							}
							if (me->def->stockpileWeaponDef->interceptor) {
								// anti-nuke, not implemented yet
							}
						}

						if (me->def->shieldWeaponDef && me->def->shieldWeaponDef->isShield) {
							// shield, not implemented yet
							// me->category = CAT_SHIELD;
						}

						if (me->def->makesMetal) {
							metal_makers[mySide].push_back(i);
							me->category = CAT_MMAKER;
						}
						if (me->def->extractsMetal > 0.0f) {
							metal_extractors[mySide].push_back(i);
							me->category = CAT_MEX;
						}
						if (((me->def->energyMake - me->def->energyUpkeep) / UnitCost) > 0.002 || me->def->tidalGenerator || me->def->windGenerator) {
							if (/* me->def->minWaterDepth <= 0 && */ !me->def->needGeo) {
								// filter tidals and geothermals
								ground_energy[mySide].push_back(i);
								me->category = CAT_ENERGY;
							}
						}
						if (me->def->energyStorage / UnitCost > 0.2) {
							energy_storages[mySide].push_back(i);
							me->category = CAT_ESTOR;
						}
						if (me->def->metalStorage / UnitCost > 0.1) {
							metal_storages[mySide].push_back(i);
							me->category = CAT_MSTOR;
						}
					}
				}
			}
		}
	}

	ReadModConfig();
	// dump generated unit table to file
	DebugPrint();
}