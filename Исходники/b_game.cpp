//This function is called every tick (from g_game.c),
//send bots into thinking (+more).
void FCajunMaster::Main (int buf)
{
	int i;

	BotThinkCycles.Reset();

	if (consoleplayer != Net_Arbitrator || demoplayback)
		return;

	if (gamestate != GS_LEVEL)
		return;

	m_Thinking = true;

	//Think for bots.
	if (botnum)
	{
		BotThinkCycles.Clock();
		for (i = 0; i < MAXPLAYERS; i++)
		{
			if (playeringame[i] && players[i].mo && !freeze && players[i].isbot)
				Think (players[i].mo, &netcmds[i][buf]);
		}
		BotThinkCycles.Unclock();
	}

	//Add new bots?
	if (wanted_botnum > botnum && !freeze)
	{
		if (t_join == ((wanted_botnum - botnum) * SPAWN_DELAY))
		{
            if (!SpawnBot (getspawned[spawn_tries]))
				wanted_botnum--;
            spawn_tries++;
		}

		t_join--;
	}

	//Check if player should go observer. Or un observe
	if (bot_observer && !observer && !netgame)
	{
		Printf ("%s is now observer\n", players[consoleplayer].userinfo.netname);
		observer = true;
		players[consoleplayer].mo->UnlinkFromWorld ();
		players[consoleplayer].mo->flags = MF_DROPOFF|MF_NOBLOCKMAP|MF_NOCLIP|MF_NOTDMATCH|MF_NOGRAVITY|MF_FRIENDLY;
		players[consoleplayer].mo->flags2 |= MF2_FLY;
		players[consoleplayer].mo->LinkToWorld ();
	}
	else if (!bot_observer && observer && !netgame) //Go back
	{
		Printf ("%s returned to the fray\n", players[consoleplayer].userinfo.netname);
		observer = false;
		players[consoleplayer].mo->UnlinkFromWorld ();
		players[consoleplayer].mo->flags = MF_SOLID|MF_SHOOTABLE|MF_DROPOFF|MF_PICKUP|MF_NOTDMATCH|MF_FRIENDLY;
		players[consoleplayer].mo->flags2 &= ~MF2_FLY;
		players[consoleplayer].mo->LinkToWorld ();
	}

	m_Thinking = false;
}