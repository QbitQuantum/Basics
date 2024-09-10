// Display scene
void SeasonalWindow::OnDisplay()
{
	gameTime.Update();

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0,0,0,1);

	// draw world
	scn.Draw(gameTime);

	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// draw current season
	glRasterPos2f(0.5f, 0.9f);
	Printf("Current Season: %s", scn.GetCurrentSeasonString());
	
	// draw current time multiplier
	glRasterPos2f(-0.96f, 0.9f);
	Printf("Current Time Multiplier: %f", scn.GetMultiplier());

	// display help menu if required
	if(displayHelpMenu)
	{
		glRasterPos2f(-0.96f, 0.75f); Printf("Press p to pause/ unpause time");
		glRasterPos2f(-0.96f, 0.7f);  Printf("Press +/- to increase/decrease time multiplier");

		glRasterPos2f(-0.96f, 0.6f);  Printf("Press s to switch lighting mode");
		glRasterPos2f(-0.96f, 0.55f); Printf("Press t to switch polygon mode (wireframe or fill)");
		glRasterPos2f(-0.96f, 0.5f);  Printf("Press m to switch tree viewing mode");

		glRasterPos2f(-0.96f, 0.4f);  Printf("Press Left/Right or Up/Down arrows to rotate camera");
		glRasterPos2f(-0.96f, 0.35f); Printf("Hold Left Mouse and move mouse to zoom");
		glRasterPos2f(-0.96f, 0.3f);  Printf("Hold Right Mouse and move mouse to rotate");

		glRasterPos2f(-0.96f, 0.2f);  Printf("Press h to hide/display this help menu");
	}
	else
	{
		glRasterPos2f(-0.96f, 0.80f);
		Printf("Press h to display help menu");
	}
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();   
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);

	SwapBuffers();
};