void invRTSGame::drawQuads()
{
	//------------------------------------------------
	// Draw the selection circles
	//------------------------------------------------
	glColor3f(1.f, 1.f, 1.f);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	quadinstances.rewind();
	while(!quadinstances.isEnd())
	{
		invQuadInstance* q = quadinstances.current();
		if(q->visible && !q->q->in2D)
			q->draw();
		quadinstances.next();
	}

	
	glBindTexture(GL_TEXTURE_2D, circle);
	glColor3f(1.f, 1.f, 1.f);
	for(int i=0;i < nb_selectedl;i++)
	{
		glPushMatrix();
		glTranslatef(selectedl[i]->pos.x, 0.02f, selectedl[i]->pos.z);
		glRotatef(90.f, 1.f, 0.f, 0.f);

		drawTexturedSquare(selectedl[i]->mdef->bx * 1.5f, selectedl[i]->mdef->bz * 1.5f);
		glPopMatrix();
	}


	if(mouse_over)
	{
		glPushMatrix();
		glTranslatef(mouse_over->pos.x, 0.02f, mouse_over->pos.z);
		glRotatef(90.f, 1.f, 0.f, 0.f);

		glColor4f(1.f, 1.f, 1.f, 0.5f);
		drawTexturedSquare(mouse_over->mdef->bx * 1.5f, mouse_over->mdef->bz * 1.5f);
		glPopMatrix();
	}

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	if(draw_grid)
	{
		glBegin(GL_QUADS);
		// draw the grid
		for(int i=0;i<pfgrid->countx;i++)
		{
			for(int j=0;j<pfgrid->county;j++)
			{
				if(pfgrid->occupied[i * pfgrid->county + j] ||
				pfgrid->occupiedByMobileUnit[i * pfgrid->county + j])
					glColor3f(1.f, 0.f, 0.f);
				else
					glColor3f(0.f, 1.f, 0.f);

				glVertex3f(pfgrid->startx + (float)i * pfgrid->cellx,
						   0.2f, 
						   pfgrid->starty + (float)j * pfgrid->celly);
				glVertex3f(pfgrid->startx + (float)(i+1) * pfgrid->cellx,
						   0.2f, 
						   pfgrid->starty + (float)j * pfgrid->celly);
				glVertex3f(pfgrid->startx + (float)(i+1) * pfgrid->cellx,
						   0.2f, 
						   pfgrid->starty + (float)(j+1) * pfgrid->celly);
				glVertex3f(pfgrid->startx + (float)i * pfgrid->cellx,
						   0.2f, 
						   pfgrid->starty + (float)(j+1) * pfgrid->celly);
			}
		}

		glEnd();
	}

	glEnable(GL_TEXTURE_2D);
}