// FOR SYNCED MESSAGES
void CGame::ActionReceived(const Action& action, int playernum)
{
	if (action.command == "cheat") {
		SetBoolArg(gs->cheatEnabled, action.extra);
		if (gs->cheatEnabled)
			logOutput.Print("Cheating!");
		else
			logOutput.Print("No more cheating");
	}
	else if (action.command == "nohelp") {
		SetBoolArg(gs->noHelperAIs, action.extra);
		selectedUnits.PossibleCommandChange(NULL);
		logOutput.Print("LuaUI control is %s", gs->noHelperAIs ? "disabled" : "enabled");
	}
	else if (action.command == "nospecdraw") {
		bool buf;
		SetBoolArg(buf, action.extra);
		inMapDrawer->SetSpecMapDrawingAllowed(buf);
	}
	else if (action.command == "godmode") {
		if (!gs->cheatEnabled)
			logOutput.Print("godmode requires /cheat");
		else {
			SetBoolArg(gs->godMode, action.extra);
			CLuaUI::UpdateTeams();
			if (gs->godMode) {
				logOutput.Print("God Mode Enabled");
			} else {
				logOutput.Print("God Mode Disabled");
			}
			CPlayer::UpdateControlledTeams();
		}
	}
	else if (action.command == "globallos") {
		if (!gs->cheatEnabled) {
			logOutput.Print("globallos requires /cheat");
		} else {
			SetBoolArg(gs->globalLOS, action.extra);
			if (gs->globalLOS) {
				logOutput.Print("Global LOS Enabled");
			} else {
				logOutput.Print("Global LOS Disabled");
			}
		}
	}
	else if (action.command == "nocost" && gs->cheatEnabled) {
		if (unitDefHandler->ToggleNoCost()) {
			logOutput.Print("Everything is for free!");
		} else {
			logOutput.Print("Everything costs resources again!");
		}
	}
	else if (action.command == "give" && gs->cheatEnabled) {
		std::string s = "give "; //FIXME lazyness
		s += action.extra;

		// .give [amount] <unitName> [team] <@x,y,z>
		const vector<string> &args = CSimpleParser::Tokenize(s, 0);

		if (args.size() < 3) {
			logOutput.Print("Someone is spoofing invalid .give messages!");
			return;
		}

		float3 pos;
		if (sscanf(args[args.size() - 1].c_str(), "@%f,%f,%f", &pos.x, &pos.y, &pos.z) != 3) {
			logOutput.Print("Someone is spoofing invalid .give messages!");
			return;
		}

		int amount = 1;
		int team = playerHandler->Player(playernum)->team;
		int allyteam = -1;

		int amountArgIdx = -1;
		int teamArgIdx = -1;

		if (args.size() == 5) {
			amountArgIdx = 1;
			teamArgIdx = 3;
		}
		else if (args.size() == 4) {
			if (args[1].find_first_not_of("0123456789") == string::npos) {
				amountArgIdx = 1;
			} else {
				teamArgIdx = 2;
			}
		}

		if (amountArgIdx >= 0) {
			const string& amountStr = args[amountArgIdx];
			amount = atoi(amountStr.c_str());
			if ((amount < 0) || (amountStr.find_first_not_of("0123456789") != string::npos)) {
				logOutput.Print("Bad give amount: %s", amountStr.c_str());
				return;
			}
		}

		if (teamArgIdx >= 0) {
			const string& teamStr = args[teamArgIdx];
			team = atoi(teamStr.c_str());
			if ((team < 0) || (team >= teamHandler->ActiveTeams()) || (teamStr.find_first_not_of("0123456789") != string::npos)) {
				logOutput.Print("Bad give team: %s", teamStr.c_str());
				return;
			}
		}

		const string unitName = (amountArgIdx >= 0) ? args[2] : args[1];

		if (unitName == "all") {
			// player entered ".give all"
			int numRequestedUnits = unitDefHandler->unitDefs.size() - 1; /// defid=0 is not valid
			int currentNumUnits = teamHandler->Team(team)->units.size();
			int sqSize = (int) streflop::ceil(streflop::sqrt((float) numRequestedUnits));

			// make sure team unit-limit not exceeded
			if ((currentNumUnits + numRequestedUnits) > uh->MaxUnitsPerTeam()) {
				numRequestedUnits = uh->MaxUnitsPerTeam() - currentNumUnits;
			}

			// make sure square is entirely on the map
			float sqHalfMapSize = sqSize / 2 * 10 * SQUARE_SIZE;
			pos.x = std::max(sqHalfMapSize, std::min(pos.x, float3::maxxpos - sqHalfMapSize - 1));
			pos.z = std::max(sqHalfMapSize, std::min(pos.z, float3::maxzpos - sqHalfMapSize - 1));

			for (int a = 1; a <= numRequestedUnits; ++a) {
				float posx = pos.x + (a % sqSize - sqSize / 2) * 10 * SQUARE_SIZE;
				float posz = pos.z + (a / sqSize - sqSize / 2) * 10 * SQUARE_SIZE;
				float3 pos2 = float3(posx, pos.y, posz);
				const UnitDef* ud = unitDefHandler->GetUnitDefByID(a);
				if (ud) {
					const CUnit* unit = unitLoader.LoadUnit(ud, pos2, team, false, 0, NULL);
					if (unit) {
						unitLoader.FlattenGround(unit);
					}
				}
			}
		}
		else if (!unitName.empty()) {
			int numRequestedUnits = amount;
			int currentNumUnits = teamHandler->Team(team)->units.size();

			if (currentNumUnits >= uh->MaxUnitsPerTeam()) {
				LogObject() << "Unable to give any more units to team " << team << "(current: " << currentNumUnits << ", max: " << uh->MaxUnits() << ")";
				return;
			}

			// make sure team unit-limit is not exceeded
			if ((currentNumUnits + numRequestedUnits) > uh->MaxUnitsPerTeam()) {
				numRequestedUnits = uh->MaxUnitsPerTeam() - currentNumUnits;
			}

			const UnitDef* unitDef = unitDefHandler->GetUnitDefByName(unitName);

			if (unitDef != NULL) {
				int xsize = unitDef->xsize;
				int zsize = unitDef->zsize;
				int squareSize = (int) streflop::ceil(streflop::sqrt((float) numRequestedUnits));
				int total = numRequestedUnits;

				float3 minpos = pos;
				minpos.x -= ((squareSize - 1) * xsize * SQUARE_SIZE) / 2;
				minpos.z -= ((squareSize - 1) * zsize * SQUARE_SIZE) / 2;

				for (int z = 0; z < squareSize; ++z) {
					for (int x = 0; x < squareSize && total > 0; ++x) {
						float minposx = minpos.x + x * xsize * SQUARE_SIZE;
						float minposz = minpos.z + z * zsize * SQUARE_SIZE;
						const float3 upos(minposx, minpos.y, minposz);
						const CUnit* unit = unitLoader.LoadUnit(unitDef, upos, team, false, 0, NULL);

						if (unit) {
							unitLoader.FlattenGround(unit);
						}
						--total;
					}
				}

				logOutput.Print("Giving %i %s to team %i", numRequestedUnits, unitName.c_str(), team);
			} else {
				if (teamArgIdx < 0) {
					team = -1; // default to world features
					allyteam = -1;
				} else {
					allyteam = teamHandler->AllyTeam(team);
				}

				const FeatureDef* featureDef = featureHandler->GetFeatureDef(unitName);
				if (featureDef) {
					int xsize = featureDef->xsize;
					int zsize = featureDef->zsize;
					int squareSize = (int) streflop::ceil(streflop::sqrt((float) numRequestedUnits));
					int total = amount; // FIXME -- feature count limit?

					float3 minpos = pos;
					minpos.x -= ((squareSize - 1) * xsize * SQUARE_SIZE) / 2;
					minpos.z -= ((squareSize - 1) * zsize * SQUARE_SIZE) / 2;

					for (int z = 0; z < squareSize; ++z) {
						for (int x = 0; x < squareSize && total > 0; ++x) {
							float minposx = minpos.x + x * xsize * SQUARE_SIZE;
							float minposz = minpos.z + z * zsize * SQUARE_SIZE;
							float minposy = ground->GetHeight2(minposx, minposz);
							const float3 upos(minposx, minposy, minposz);

							CFeature* feature = new CFeature();
							feature->Initialize(upos, featureDef, 0, 0, team, allyteam, "");
							--total;
						}
					}

					logOutput.Print("Giving %i %s (feature) to team %i",
									numRequestedUnits, unitName.c_str(), team);
				}
				else {
					logOutput.Print(unitName + " is not a valid unitname");
				}
			}
		}
	}
	else if (action.command == "destroy" && gs->cheatEnabled) {
		std::stringstream ss(action.extra);
		logOutput.Print("Killing units: %s", action.extra.c_str());
		do {
			unsigned id;
			ss >> id;
			if (!ss)
				break;
			if (id >= uh->units.size())
				continue;
			if (uh->units[id] == NULL)
				continue;
			uh->units[id]->KillUnit(false, false, 0);
		} while (true);
	}