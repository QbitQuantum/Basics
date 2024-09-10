void AAI::InitAI(IGlobalAICallback* callback, int team)
{
	aicb = callback;
	cb = callback->GetAICallback();

	// open log file
	char filename[500];
	char buffer[500];
	char team_number[3];

	SNPRINTF(team_number, 3, "%d", team);

	STRCPY(buffer, MAIN_PATH);
	STRCAT(buffer, AILOG_PATH);
	STRCAT(buffer, "AAI_log_team_");
	STRCAT(buffer, team_number);
	STRCAT(buffer, ".txt");
	ReplaceExtension (buffer, filename, sizeof(filename), ".txt");

	cb->GetValue(AIVAL_LOCATE_FILE_W, filename);

	file = fopen(filename,"w");

	fprintf(file, "AAI %s running mod %s\n \n", AAI_VERSION(team), cb->GetModHumanName());

	// load config file first
	cfg->LoadConfig(this);

	if(!cfg->initialized)
	{
		std::string errorMsg =
				std::string("Error: Could not load mod and/or general config file."
					" For further information see the config file under: ") +
				filename;
		cb->SendTextMsg(errorMsg.c_str(), 0);
		throw 1;
	}

	// create buildtable
	bt = new AAIBuildTable(cb, this);
	bt->Init();

	// init unit table
	ut = new AAIUnitTable(this, bt);

	// init map
	map = new AAIMap(this);
	map->Init();

	// init brain
	brain = new AAIBrain(this);

	// init executer
	execute = new AAIExecute(this, brain);

	// create unit groups
	group_list.resize(MOBILE_CONSTRUCTOR+1);

	// init airforce manager
	af = new AAIAirForceManager(this, cb, bt);

	// init attack manager
	am = new AAIAttackManager(this, cb, bt, map->continents.size());

	cb->SendTextMsg("AAI loaded", 0);
}