void CTeamHandler::LoadFromSetup(const CGameSetup* setup)
{
    const bool useLuaGaia  = CLuaGaia::SetConfigString(setup->luaGaiaStr);

    activeTeams = setup->numTeams;
    activeAllyTeams = setup->numAllyTeams;

    assert(activeTeams <= MAX_TEAMS);
    assert(activeAllyTeams <= MAX_TEAMS);

    for (int i = 0; i < activeTeams; ++i) {
        // TODO: this loop body could use some more refactoring
        CTeam* team = Team(i);
        const CGameSetup::TeamData& teamStartingData = setup->teamStartingData[i];

        team->metal = setup->startMetal;
        team->metalIncome = setup->startMetal; // for the endgame statistics

        team->energy = setup->startEnergy;
        team->energyIncome = setup->startEnergy;

        float3 start(teamStartingData.startPos.x, teamStartingData.startPos.y, teamStartingData.startPos.z);
        team->StartposMessage(start, (setup->startPosType != CGameSetup::StartPos_ChooseInGame));
        std::memcpy(team->color, teamStartingData.color, 4);
        team->handicap = teamStartingData.handicap;
        team->leader = teamStartingData.leader;
        team->side = teamStartingData.side;
        SetAllyTeam(i, teamStartingData.teamAllyteam);

        if (!teamStartingData.luaAI.empty()) {
            team->luaAI = teamStartingData.luaAI;
            team->isAI = true;
        } else if (!(teamStartingData.skirmishAIShortName.empty())) {
            if (setup->hostDemo) {
                team->skirmishAIKey = SkirmishAIKey(); // unspecifyed AI Key
            } else {
                const char* sn = teamStartingData.skirmishAIShortName.c_str();
                const char* v = teamStartingData.skirmishAIVersion.empty()
                                ? NULL : teamStartingData.skirmishAIVersion.c_str();
                SkirmishAIKey spec = SkirmishAIKey(sn, v);
                SkirmishAIKey fittingKey =
                    IAILibraryManager::GetInstance()->ResolveSkirmishAIKey(spec);
                if (!fittingKey.IsUnspecified()) {
                    team->skirmishAIKey = fittingKey;
                    team->skirmishAIOptions = teamStartingData.skirmishAIOptions;
                    team->isAI = true;
                } else {
                    const int MAX_MSG_LENGTH = 511;
                    char s_msg[MAX_MSG_LENGTH + 1];
                    SNPRINTF(s_msg, MAX_MSG_LENGTH,
                             "Specifyed Skirmish AI could not be found: %s (version: %s)",
                             spec.GetShortName().c_str(), spec.GetVersion() != "" ? spec.GetVersion().c_str() : "<not specifyed>");
                    handleerror(NULL, s_msg, "Team Handler Error", MBF_OK | MBF_EXCL);
                }
            }
        }
    }

    for (int allyTeam1 = 0; allyTeam1 < activeAllyTeams; ++allyTeam1)
    {
        for (int allyTeam2 = 0; allyTeam2 < activeAllyTeams; ++allyTeam2)
            allies[allyTeam1][allyTeam2] = setup->allyStartingData[allyTeam1].allies[allyTeam2];
    }

    if (useLuaGaia) {
        // Gaia adjustments
        gaiaTeamID = activeTeams;
        gaiaAllyTeamID = activeAllyTeams;
        activeTeams++;
        activeAllyTeams++;

        // Setup the gaia team
        CTeam* team = Team(gaiaTeamID);
        team->color[0] = 255;
        team->color[1] = 255;
        team->color[2] = 255;
        team->color[3] = 255;
        team->gaia = true;
        team->StartposMessage(float3(0.0, 0.0, 0.0), true);
        //players[setup->numPlayers]->team = gaiaTeamID;
        SetAllyTeam(gaiaTeamID, gaiaAllyTeamID);
    }
}