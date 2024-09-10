void CEndGameBox::Draw()
{
	if (!graphTex) {
		graphTex = bm.CreateTexture();
	}

	if (disabled) {
		return;
	}

	float mx = MouseX(mouse->lastx);
	float my = MouseY(mouse->lasty);

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

	// Large Box
	glColor4f(0.2f, 0.2f, 0.2f, guiAlpha);
	DrawBox(box);

	glColor4f(0.2f, 0.2f, 0.7f, guiAlpha);
	if (dispMode == 0) {
		DrawBox(box + playerBox);
	} else if (dispMode == 1) {
		DrawBox(box + sumBox);
	} else {
		DrawBox(box + difBox);
	}

	if (InBox(mx, my, box+exitBox)) {
		glColor4f(0.7f, 0.2f, 0.2f, guiAlpha);
		DrawBox(box + exitBox);
	}
	if (InBox(mx,my,box+playerBox)) {
		glColor4f(0.7f, 0.2f, 0.2f, guiAlpha);
		DrawBox(box + playerBox);
	}
	if (InBox(mx,my,box+sumBox)) {
		glColor4f(0.7f, 0.2f, 0.2f, guiAlpha);
		DrawBox(box + sumBox);
	}
	if (InBox(mx,my,box+difBox)) {
		glColor4f(0.7f, 0.2f, 0.2f, guiAlpha);
		DrawBox(box + difBox);
	}

	glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 0.8f);
	font->glPrint(box.x1 + exitBox.x1   + 0.025f, box.y1 + exitBox.y1   + 0.005f, 1.0f, FONT_SCALE | FONT_NORM, "Exit");
	font->glPrint(box.x1 + playerBox.x1 + 0.015f, box.y1 + playerBox.y1 + 0.005f, 0.7f, FONT_SCALE | FONT_NORM, "Player stats");
	font->glPrint(box.x1 + sumBox.x1    + 0.015f, box.y1 + sumBox.y1    + 0.005f, 0.7f, FONT_SCALE | FONT_NORM, "Team stats");
	font->glPrint(box.x1 + difBox.x1    + 0.015f, box.y1 + difBox.y1    + 0.005f, 0.7f, FONT_SCALE | FONT_NORM, "Team delta stats");

	if (winners.empty()) {
		font->glPrint(box.x1 + 0.25f, box.y1 + 0.65f, 1.0f, FONT_SCALE | FONT_NORM, "Game result was undecided");
	} else {
		std::stringstream winnersText("Game Over, winning AllyTeams are: ");

		const bool neverPlayed = (gu->myPlayingAllyTeam < 0);
		      bool playedAndWon = false;

		for (unsigned int i = 0; i < winners.size(); i++) {
			const int winner = winners[i];

			if (!neverPlayed && winner == gu->myPlayingAllyTeam) {
				// we actually played and won!
				playedAndWon = true; break;
			}

			winnersText << winner;

			if (i < (winners.size() - 1))
				winnersText << ", ";
		}

		if (neverPlayed) {
			font->glPrint(box.x1 + 0.25f, box.y1 + 0.65f, 1.0f, FONT_SCALE | FONT_NORM, (winnersText.str()).c_str());
		} else {
			font->glPrint(box.x1 + 0.25f, box.y1 + 0.65f, 1.0f, FONT_SCALE | FONT_NORM, (playedAndWon? "You won the game": "You lost the game"));
		}
	}

	if (gs->frameNum <= 0) {
		return;
	}

	if (dispMode == 0) {
		float xpos = 0.01f;

		std::string headers[] = {"Name", "MC/m", "MP/m", "KP/m", "Cmds/m", "ACS"};

		for (int a = 0; a < 6; ++a) {
			font->glPrint(box.x1 + xpos, box.y1 + 0.55f, 0.8f, FONT_SCALE | FONT_NORM,headers[a].c_str());
			xpos += 0.1f;
		}

		float ypos=0.5f;
		for (int a = 0; a < playerHandler->ActivePlayers(); ++a) {
			if (playerHandler->Player(a)->currentStats.mousePixels == 0) {
				continue;
			}
			char values[6][100];

			sprintf(values[0], "%s",	playerHandler->Player(a)->name.c_str());
			sprintf(values[1], "%i", (int)(playerHandler->Player(a)->currentStats.mouseClicks * 60 / game->totalGameTime));
			sprintf(values[2], "%i", (int)(playerHandler->Player(a)->currentStats.mousePixels * 60 / game->totalGameTime));
			sprintf(values[3], "%i", (int)(playerHandler->Player(a)->currentStats.keyPresses  * 60 / game->totalGameTime));
			sprintf(values[4], "%i", (int)(playerHandler->Player(a)->currentStats.numCommands * 60 / game->totalGameTime));
			sprintf(values[5], "%i", (int)
				( playerHandler->Player(a)->currentStats.numCommands != 0 ) ?
				( playerHandler->Player(a)->currentStats.unitCommands/playerHandler->Player(a)->currentStats.numCommands) :
				( 0 ));

			float xpos = 0.01f;
			for (int a = 0; a < 6; ++a) {
				font->glPrint(box.x1 + xpos, box.y1 + ypos, 0.8f, FONT_SCALE | FONT_NORM, values[a]);
				xpos += 0.1f;
			}

			ypos -= 0.02f;
		}
	} else {
		if (stats.empty()) {
			FillTeamStats();
		}

		glBindTexture(GL_TEXTURE_2D, graphTex);
		CVertexArray* va=GetVertexArray();
		va->Initialize();

		va->AddVertexT(float3(box.x1+0.15f, box.y1+0.08f, 0), 0, 0);
		va->AddVertexT(float3(box.x1+0.69f, box.y1+0.08f, 0), 4, 0);
		va->AddVertexT(float3(box.x1+0.69f, box.y1+0.62f, 0), 4, 4);
		va->AddVertexT(float3(box.x1+0.15f, box.y1+0.62f, 0), 0, 4);

		va->DrawArrayT(GL_QUADS);

		if ((mx > box.x1 + 0.01f) && (mx < box.x1 + 0.12f) &&
		    (my < box.y1 + 0.57f) && (my > box.y1 + 0.571f - (stats.size() * 0.02f))) {
			const int sel = (int) floor(50 * -(my - box.y1 - 0.57f));

			glColor4f(0.7f, 0.2f, 0.2f, guiAlpha);
			glDisable(GL_TEXTURE_2D);
			CVertexArray* va = GetVertexArray();
			va->Initialize();

			va->AddVertex0(float3(box.x1 + 0.01f, box.y1 + 0.55f - (sel * 0.02f)         , 0));
			va->AddVertex0(float3(box.x1 + 0.01f, box.y1 + 0.55f - (sel * 0.02f) + 0.02f , 0));
			va->AddVertex0(float3(box.x1 + 0.12f, box.y1 + 0.55f - (sel * 0.02f) + 0.02f , 0));
			va->AddVertex0(float3(box.x1 + 0.12f, box.y1 + 0.55f - (sel * 0.02f)         , 0));

			va->DrawArray0(GL_QUADS);
			glEnable(GL_TEXTURE_2D);
			glColor4f(1, 1, 1, 0.8f);
		}
		float ypos = 0.55f;
		for (size_t a = 0; a < stats.size(); ++a) {
			font->glPrint(box.x1 + 0.01f, box.y1 + ypos, 0.8f, FONT_SCALE | FONT_NORM, stats[a].name);
			ypos -= 0.02f;
		}
		float maxy = 1;

		if (dispMode == 1) {
			maxy = std::max(stats[stat1].max,    (stat2 != -1) ? stats[stat2].max    : 0);
		} else {
			maxy = std::max(stats[stat1].maxdif, (stat2 != -1) ? stats[stat2].maxdif : 0) / TeamStatistics::statsPeriod;
		}

		int numPoints = stats[0].values[0].size();

		for (int a = 0; a < 5; ++a) {
			font->glPrint(box.x1 + 0.12f, box.y1 + 0.07f + (a * 0.135f), 0.8f, FONT_SCALE | FONT_NORM,
			                FloatToSmallString(maxy * 0.25f * a));
			font->glFormat(box.x1 + 0.135f + (a * 0.135f), box.y1 + 0.057f, 0.8f, FONT_SCALE | FONT_NORM, "%02i:%02i",
			                (int) (a * 0.25f * numPoints * TeamStatistics::statsPeriod / 60),
			                (int) (a * 0.25f * (numPoints - 1) * TeamStatistics::statsPeriod) % 60);
		}

		font->glPrint(box.x1 + 0.55f, box.y1 + 0.65f, 0.8f, FONT_SCALE | FONT_NORM, stats[stat1].name);
		font->glPrint(box.x1 + 0.55f, box.y1 + 0.63f, 0.8f, FONT_SCALE | FONT_NORM, (stat2 != -1) ? stats[stat2].name : "");

		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINES);
				glVertex3f(box.x1+0.50f, box.y1+0.66f, 0);
				glVertex3f(box.x1+0.55f, box.y1+0.66f, 0);
		glEnd();

		glLineStipple(3, 0x5555);
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
				glVertex3f(box.x1 + 0.50f, box.y1 + 0.64f, 0.0f);
				glVertex3f(box.x1 + 0.55f, box.y1 + 0.64f, 0.0f);
		glEnd();
		glDisable(GL_LINE_STIPPLE);

		const float scalex = 0.54f / std::max(1.0f, numPoints - 1.0f);
		const float scaley = 0.54f / maxy;

		for (int team = 0; team < teamHandler->ActiveTeams(); team++) {
			const CTeam* pteam = teamHandler->Team(team);

			if (pteam->gaia) {
				continue;
			}

			glColor4ubv(pteam->color);

			glBegin(GL_LINE_STRIP);
			for (int a = 0; a < numPoints; ++a) {
				float value = 0.0f;

				if (dispMode == 1) {
					value = stats[stat1].values[team][a];
				} else if (a > 0) {
					value = (stats[stat1].values[team][a] - stats[stat1].values[team][a - 1]) / TeamStatistics::statsPeriod;
				}

				glVertex3f(box.x1 + 0.15f + a * scalex, box.y1 + 0.08f + value * scaley, 0.0f);
			}
			glEnd();

			if (stat2 != -1) {
				glLineStipple(3, 0x5555);
				glEnable(GL_LINE_STIPPLE);

				glBegin(GL_LINE_STRIP);
				for (int a = 0; a < numPoints; ++a) {
					float value = 0;
					if (dispMode == 1) {
						value = stats[stat2].values[team][a];
					} else if (a > 0) {
						value = (stats[stat2].values[team][a]-stats[stat2].values[team][a-1]) / TeamStatistics::statsPeriod;
					}

					glVertex3f(box.x1+0.15f+a*scalex, box.y1+0.08f+value*scaley, 0);
				}
				glEnd();

				glDisable(GL_LINE_STIPPLE);
			}
		}
	}
}