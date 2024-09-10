void PFonts::PrintOnScreen(float x, float y, float z, int Screenwidth, int Screenheight, 
						   const char *Text,int argument)
{
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();

	glLoadIdentity();							// Reset The Projection Matrix
	glOrtho(0,Screenwidth,0,Screenheight,-1,1); //Set orthographic projection based on the applications
	                                            // width and height

	if(z<-1)
	{
		z=-1;
	}

	if(z>1)
	{
		z=1;
	}

	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	glPushMatrix();								// Store The Modelview Matrix
	glLoadIdentity();

	glTranslatef(x,y,z);                   //Move to specified location on screen

	
	glRasterPos2f(0.0,0.0f);
	PrintF(Text,argument);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();		

	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	glPopMatrix();

}