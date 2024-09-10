void AAIConfig::LoadConfig(AAI *ai)
{
	// this size equals the one used in "AIAICallback::GetValue(AIVAL_LOCATE_FILE_..."
	char filename[2048];
	char buffer[500];

	MAX_UNITS = ai->Getcb()->GetMaxUnits();

	FILE* file = NULL;

	STRCPY_T(buffer, sizeof(buffer), MAIN_PATH);
	STRCAT_T(buffer, sizeof(buffer), MOD_CFG_PATH);
	const std::string modHumanName = MakeFileSystemCompatible(ai->Getcb()->GetModHumanName());
	STRCAT_T(buffer, sizeof(buffer), modHumanName.c_str());
	STRCAT_T(buffer, sizeof(buffer), ".cfg");
	STRCPY_T(filename, sizeof(filename), buffer);
	ai->Getcb()->GetValue(AIVAL_LOCATE_FILE_R, filename);
	file = fopen(filename, "r");
	if (file == NULL) {
		ai->Log("Mod config file %s not found\n", filename);
		ai->Log("Now trying with legacy mod config file name ...\n");
		STRCPY_T(buffer, sizeof(buffer), MAIN_PATH);
		STRCAT_T(buffer, sizeof(buffer), MOD_CFG_PATH);
		const std::string modName = MakeFileSystemCompatible(ai->Getcb()->GetModName());
		STRCAT_T(buffer, sizeof(buffer), modName.c_str());
		ReplaceExtension(buffer, filename, sizeof(filename), ".cfg");
		ai->Getcb()->GetValue(AIVAL_LOCATE_FILE_R, filename);
		file = fopen(filename, "r");
	}
	if (file == NULL) {
		ai->Log("Mod config file %s not found\n", filename);
		ai->Log("Now trying with version independent mod config file name ...\n");
		STRCPY_T(buffer, sizeof(buffer), MAIN_PATH);
		STRCAT_T(buffer, sizeof(buffer), MOD_CFG_PATH);
		const std::string modShortName = MakeFileSystemCompatible(ai->Getcb()->GetModShortName());
		STRCAT_T(buffer, sizeof(buffer), modShortName.c_str());
		STRCAT_T(buffer, sizeof(buffer), ".cfg");
		STRCPY_T(filename, sizeof(filename), buffer);
		ai->Getcb()->GetValue(AIVAL_LOCATE_FILE_R, filename);
		file = fopen(filename, "r");
	}
	if (file == NULL) {
		ai->Log("Mod config file %s not found\n", filename);
		ai->Log("Give up trying to find mod config file (required).\n");
		initialized = false;
		return;
	}

	char keyword[50];
	int ival;
	float fval;
	const UnitDef *def;

	bool error = false;
//	bool loaded = false;

	if(file)
	{
		ai->Log("Using mod config file %s\n", filename);

		while(EOF != fscanf(file, "%s", keyword))
		{
			if(!strcmp(keyword,"SIDES"))
			{
				fscanf(file, "%i", &ival);
				SIDES = ival;
			}
			else if(!strcmp(keyword, "START_UNITS"))
			{
				START_UNITS = new char*[SIDES];

				for(int i = 0; i < SIDES; i++)
				{
					START_UNITS[i] = new char[20];
					fscanf(file, "%s", filename);
					STRCPY(START_UNITS[i], filename);

					if(!ai->Getcb()->GetUnitDef(START_UNITS[i]))
					{
						ai->Log("ERROR: loading starting units - could not find unit %s\n", START_UNITS[i]);
						error = true;
						break;
					}
				}
			}
			else if(!strcmp(keyword, "SIDE_NAMES"))
			{
				SIDE_NAMES = new char*[SIDES];

				for(int i = 0; i < SIDES; i++)
				{
					SIDE_NAMES[i] = new char[80];
					fscanf(file, "%s", filename);
					STRCPY(SIDE_NAMES[i], filename);
				}
			}
			else if(!strcmp(keyword, "SCOUTS"))
			{
				// get number of scouts
				fscanf(file, "%i", &ival);

				for(int i = 0; i < ival; ++i)
				{
					fscanf(file, "%s", filename);
					if(ai->Getcb()->GetUnitDef(filename))
						SCOUTS.push_back(ai->Getcb()->GetUnitDef(filename)->id);
					else
					{
						ai->Log("ERROR: loading scouts - could not find unit %s\n", filename);
						error = true;
						break;
					}
				}
			}
			else if(!strcmp(keyword, "ATTACKERS"))
			{
				// get number of attackers
				fscanf(file, "%i", &ival);

				for(int i = 0; i < ival; ++i)
				{
					fscanf(file, "%s", filename);
					if(ai->Getcb()->GetUnitDef(filename))
						ATTACKERS.push_back(ai->Getcb()->GetUnitDef(filename)->id);
					else
					{
						ai->Log("ERROR: loading attackers - could not find unit %s\n", filename);
						error = true;
						break;
					}
				}
			}
			else if(!strcmp(keyword, "TRANSPORTERS"))
			{
				// get number of transporters
				fscanf(file, "%i", &ival);

				for(int i = 0; i < ival; ++i)
				{
					fscanf(file, "%s", filename);
					if(ai->Getcb()->GetUnitDef(filename))
						TRANSPORTERS.push_back(ai->Getcb()->GetUnitDef(filename)->id);
					else
					{
						ai->Log("ERROR: loading transporters - could not find unit %s\n", filename);
						error = true;
						break;
					}
				}
			}
			else if(!strcmp(keyword, "DONT_BUILD"))
			{
				// get number of units that should not be built
				fscanf(file, "%i", &ival);

				for(int i = 0; i < ival; ++i)
				{
					fscanf(file, "%s", filename);
					if(ai->Getcb()->GetUnitDef(filename))
						DONT_BUILD.push_back(ai->Getcb()->GetUnitDef(filename)->id);
					else
					{
						ai->Log("ERROR: loading dont_build units - could not find unit %s\n", filename);
						error = true;
						break;
					}
				}
			}
			else if(!strcmp(keyword, "COST_MULTIPLIER"))
			{
				// get the unit def
				fscanf(file, "%s", filename);
				def = ai->Getcb()->GetUnitDef(filename);

				if(def)
				{
					fscanf(file, "%f", &fval);

					CostMultiplier temp;
					temp.id = def->id;
					temp.multiplier = fval;

					cost_multipliers.push_back(temp);
				}
				else
				{
					ai->Log("ERROR: could not set cost multiplier - could not find unit %s\n", filename);
					error = true;
					break;
				}
			}
			else if(!strcmp(keyword,"SECTOR_SIZE"))
			{
				fscanf(file, "%f", &fval);
				SECTOR_SIZE = fval;
				ai->Log("SECTOR_SIZE set to %f", SECTOR_SIZE);
			}
			else if(!strcmp(keyword,"MIN_ENERGY"))
			{
				fscanf(file, "%i", &ival);
				MIN_ENERGY = ival;
			}
			else if(!strcmp(keyword, "MAX_UNITS"))
			{
				fscanf(file, "%i", &ival);
				MAX_UNITS = ival;
			}
			else if(!strcmp(keyword, "MAX_SCOUTS"))
			{
				fscanf(file, "%i", &ival);
				MAX_SCOUTS = ival;
			}
			else if(!strcmp(keyword, "MAX_SECTOR_IMPORTANCE"))
			{
				fscanf(file, "%i", &ival);
				MAX_SECTOR_IMPORTANCE = ival;
			}
			else if(!strcmp(keyword, "MAX_XROW"))
			{
				fscanf(file, "%i", &ival);
				MAX_XROW = ival;
			}
			else if(!strcmp(keyword, "MAX_YROW"))
			{
				fscanf(file, "%i", &ival);
				MAX_YROW = ival;
			}
			else if(!strcmp(keyword, "X_SPACE"))
			{
				fscanf(file, "%i", &ival);
				X_SPACE = ival;
			}
			else if(!strcmp(keyword, "Y_SPACE"))
			{
				fscanf(file, "%i", &ival);
				Y_SPACE = ival;
			}
			else if(!strcmp(keyword, "MAX_GROUP_SIZE"))
			{
				fscanf(file, "%i", &ival);
				MAX_GROUP_SIZE = ival;
			}
			else if(!strcmp(keyword, "MAX_AIR_GROUP_SIZE"))
			{
				fscanf(file, "%i", &ival);
				MAX_AIR_GROUP_SIZE = ival;
			}
			else if(!strcmp(keyword, "MAX_NAVAL_GROUP_SIZE"))
			{
				fscanf(file, "%i", &ival);
				MAX_NAVAL_GROUP_SIZE = ival;
			}
			else if(!strcmp(keyword, "MAX_SUBMARINE_GROUP_SIZE"))
			{
				fscanf(file, "%i", &ival);
				MAX_SUBMARINE_GROUP_SIZE = ival;
			}
			else if(!strcmp(keyword, "MAX_ANTI_AIR_GROUP_SIZE"))
			{
				fscanf(file, "%i", &ival);
				MAX_ANTI_AIR_GROUP_SIZE = ival;
			}
			else if(!strcmp(keyword, "MAX_ARTY_GROUP_SIZE"))
			{
				fscanf(file, "%i", &ival);
				MAX_ARTY_GROUP_SIZE = ival;
			}
			else if(!strcmp(keyword, "UNIT_SPEED_SUBGROUPS"))
			{
				fscanf(file, "%i", &ival);
				UNIT_SPEED_SUBGROUPS = ival;
			}
			else if(!strcmp(keyword, "FALLBACK_DIST_RATIO"))
			{
				fscanf(file, "%f", &fval);
				FALLBACK_DIST_RATIO = fval;
			}
			else if(!strcmp(keyword, "MIN_FALLBACK_RANGE"))
			{
				fscanf(file, "%f", &fval);
				MIN_FALLBACK_RANGE = fval;
			}
			else if(!strcmp(keyword, "MAX_FALLBACK_RANGE"))
			{
				fscanf(file, "%f", &fval);
				MAX_FALLBACK_RANGE = fval;
			}
			else if(!strcmp(keyword, "MIN_FALLBACK_TURNRATE"))
			{
				fscanf(file, "%f", &fval);
				MIN_FALLBACK_TURNRATE = fval;
			}
			else if(!strcmp(keyword, "MIN_EFFICIENCY"))
			{
				fscanf(file, "%f", &fval);
				MIN_EFFICIENCY = fval;
			}
			else if(!strcmp(keyword, "MIN_AIR_SUPPORT_EFFICIENCY"))
			{
				fscanf(file, "%f", &fval);
				MIN_AIR_SUPPORT_EFFICIENCY = fval;
			}
			else if(!strcmp(keyword, "MAX_BUILDERS"))
			{
				fscanf(file, "%i", &ival);
				MAX_BUILDERS = ival;
			}
			else if(!strcmp(keyword, "MAX_BUILDQUE_SIZE"))
			{
				fscanf(file, "%i", &ival);
				MAX_BUILDQUE_SIZE = ival;
			}
			else if(!strcmp(keyword, "MAX_ASSISTANTS"))
			{
				fscanf(file, "%i", &ival);
				MAX_ASSISTANTS = ival;
			}
			else if(!strcmp(keyword, "MIN_ASSISTANCE_BUILDSPEED"))
			{
				fscanf(file, "%i", &ival);
				MIN_ASSISTANCE_BUILDSPEED = ival;
			}
			else if(!strcmp(keyword, "MAX_BASE_SIZE"))
			{
				fscanf(file, "%i", &ival);
				MAX_BASE_SIZE = ival;
			}
			else if(!strcmp(keyword, "MAX_AIR_TARGETS"))
			{
				fscanf(file, "%i", &ival);
				MAX_AIR_TARGETS = ival;
			}
			else if(!strcmp(keyword, "MIN_AIR_ATTACK_COST"))
			{
				fscanf(file, "%i", &ival);
				MIN_AIR_ATTACK_COST = ival;
			}
			else if(!strcmp(keyword, "SCOUT_SPEED"))
			{
				fscanf(file, "%f", &fval);
				SCOUT_SPEED = fval;
			}
			else if(!strcmp(keyword, "GROUND_ARTY_RANGE"))
			{
				fscanf(file, "%f", &fval);
				GROUND_ARTY_RANGE = fval;
			}
			else if(!strcmp(keyword, "SEA_ARTY_RANGE"))
			{
				fscanf(file, "%f", &fval);
				SEA_ARTY_RANGE = fval;
			}
			else if(!strcmp(keyword, "HOVER_ARTY_RANGE"))
			{
				fscanf(file, "%f", &fval);
				HOVER_ARTY_RANGE = fval;
			}
			else if(!strcmp(keyword, "STATIONARY_ARTY_RANGE"))
			{
				fscanf(file, "%f", &fval);
				STATIONARY_ARTY_RANGE = fval;
			}
			else if(!strcmp(keyword, "MAX_BUILDERS_PER_TYPE"))
			{
				fscanf(file, "%i", &ival);
				MAX_BUILDERS_PER_TYPE = ival;
			}
			else if(!strcmp(keyword, "MAX_FACTORIES_PER_TYPE"))
			{
				fscanf(file, "%i", &ival);
				MAX_FACTORIES_PER_TYPE = ival;
			}
			else if(!strcmp(keyword, "MIN_ASSISTANCE_BUILDTIME"))
			{
				fscanf(file, "%i", &ival);
				MIN_ASSISTANCE_BUILDTIME = ival;
			}
			else if(!strcmp(keyword, "AIR_DEFENCE"))
			{
				fscanf(file, "%i", &ival);
				AIR_DEFENCE = ival;
			}
			else if(!strcmp(keyword, "AIRCRAFT_RATE"))
			{
				fscanf(file, "%i", &ival);
				AIRCRAFT_RATE = ival;
			}
			else if(!strcmp(keyword, "HIGH_RANGE_UNITS_RATE"))
			{
				fscanf(file, "%i", &ival);
				HIGH_RANGE_UNITS_RATE = ival;
			}
			else if(!strcmp(keyword, "FAST_UNITS_RATE"))
			{
				fscanf(file, "%i", &ival);
				FAST_UNITS_RATE = ival;
			}
			else if(!strcmp(keyword, "MAX_METAL_COST"))
			{
				fscanf(file, "%i", &ival);
				MAX_METAL_COST = ival;
			}
			else if(!strcmp(keyword, "MAX_DEFENCES"))
			{
				fscanf(file, "%i", &ival);
				MAX_DEFENCES = ival;
			}
			else if(!strcmp(keyword, "MIN_SECTOR_THREAT"))
			{
				fscanf(file, "%f", &fval);
				MIN_SECTOR_THREAT = fval;
			}
			else if(!strcmp(keyword, "MAX_STAT_ARTY"))
			{
				fscanf(file, "%i", &ival);
				MAX_STAT_ARTY = ival;
			}
			else if(!strcmp(keyword, "MAX_AIR_BASE"))
			{
				fscanf(file, "%i", &ival);
				MAX_AIR_BASE = ival;
			}
			else if(!strcmp(keyword, "AIR_ONLY_MOD"))
			{
				fscanf(file, "%i", &ival);
				AIR_ONLY_MOD = (bool)ival;
			}
			else if(!strcmp(keyword, "METAL_ENERGY_RATIO"))
			{
				fscanf(file, "%f", &fval);
				METAL_ENERGY_RATIO = fval;
			}
			else if(!strcmp(keyword, "NON_AMPHIB_MAX_WATERDEPTH"))
			{
				fscanf(file, "%f", &fval);
				NON_AMPHIB_MAX_WATERDEPTH = fval;
			}
			else if(!strcmp(keyword, "MAX_METAL_MAKERS"))
			{
				fscanf(file, "%i", &ival);
				MAX_METAL_MAKERS = ival;
			}
			else if(!strcmp(keyword, "MAX_STORAGE"))
			{
				fscanf(file, "%i", &ival);
				MAX_STORAGE = ival;
			}
			else if(!strcmp(keyword, "MIN_METAL_MAKER_ENERGY"))
			{
				fscanf(file, "%f", &fval);
				MIN_METAL_MAKER_ENERGY = fval;
			}
			else if(!strcmp(keyword, "MAX_MEX_DISTANCE"))
			{
				fscanf(file, "%i", &ival);
				MAX_MEX_DISTANCE = ival;
			}
			else if(!strcmp(keyword, "MAX_MEX_DEFENCE_DISTANCE"))
			{
				fscanf(file, "%i", &ival);
				MAX_MEX_DEFENCE_DISTANCE = ival;
			}
			else if(!strcmp(keyword, "MIN_FACTORIES_FOR_DEFENCES"))
			{
				fscanf(file, "%i", &ival);
				MIN_FACTORIES_FOR_DEFENCES = ival;
			}
			else if(!strcmp(keyword, "MIN_FACTORIES_FOR_STORAGE"))
			{
				fscanf(file, "%i", &ival);
				MIN_FACTORIES_FOR_STORAGE = ival;
			}
			else if(!strcmp(keyword, "MIN_FACTORIES_FOR_RADAR_JAMMER"))
			{
				fscanf(file, "%i", &ival);
				MIN_FACTORIES_FOR_RADAR_JAMMER = ival;
			}
			else if(!strcmp(keyword, "MIN_SUBMARINE_WATERLINE"))
			{
				fscanf(file, "%i", &ival);
				MIN_SUBMARINE_WATERLINE = ival;
			}
			else if(!strcmp(keyword, "MAX_ATTACKS"))
			{
				fscanf(file, "%i", &ival);
				MAX_ATTACKS = ival;
			}
			else
			{
				error = true;
				break;
			}
		}

		if(error)
		{
			ai->Log("Mod config file %s contains erroneous keyword %s\n", filename, keyword);
			initialized = false;
			return;
		}
		else
		{
//			loaded = true;
			fclose(file);
			ai->Log("Mod config file loaded\n");
		}
	}


	// load general settings
	STRCPY_T(buffer, sizeof(buffer), MAIN_PATH);
	STRCAT_T(buffer, sizeof(buffer), GENERAL_CFG_FILE);
	ReplaceExtension(buffer, filename, sizeof(filename), ".cfg");
	ai->Getcb()->GetValue(AIVAL_LOCATE_FILE_R, filename);
	file = fopen(filename, "r");

	if(file)
	{
		while(EOF != fscanf(file, "%s", keyword))
		{
			if(!strcmp(keyword, "LEARN_RATE"))
			{
				fscanf(file, "%i", &ival);
				LEARN_RATE = ival;
			}
			else if(!strcmp(keyword, "LEARN_SPEED"))
			{
				fscanf(file, "%f", &fval);
				LEARN_SPEED = fval;
			}
			else if(!strcmp(keyword, "WATER_MAP_RATIO"))
			{
				fscanf(file, "%f", &fval);
				WATER_MAP_RATIO = fval;
			}
			else if(!strcmp(keyword, "LAND_WATER_MAP_RATIO"))
			{
				fscanf(file, "%f", &fval);
				LAND_WATER_MAP_RATIO = fval;
			}
			else if(!strcmp(keyword, "SCOUT_UPDATE_FREQUENCY"))
			{
				fscanf(file, "%i", &ival);
				SCOUT_UPDATE_FREQUENCY = ival;
			}
			else if(!strcmp(keyword, "SCOUTING_MEMORY_FACTOR"))
			{
				fscanf(file, "%f", &fval);
				SCOUTING_MEMORY_FACTOR = fval;
			}
			else
			{
				error = true;
				break;
			}
		}

		fclose(file);

		if(error)
		{
			ai->Log("General config file %s contains erroneous keyword %s\n", filename, keyword);
			initialized = false;
			return;
		}

		else
		{
			ai->Log("General config file loaded\n");
			initialized = true;
			return;
		}
	}
	else
	{
		ai->Log("General config file %s not found\n", filename);
		initialized = false;
		return;
	}
}