void Boat::drawCannonBarrel(double height)
{
	double length=.22;
	double radius=.09;
	double thickness=.02;
	double inc=4;
	// transform
	glPushMatrix();
	glTranslated(0,height,0);
	glRotated(cannonHorizAngle,0,1,0);
	glRotated(cannonVertAngle,0,0,1);
	// Begin drawing
	// Sphere
	glPushMatrix();
	glScaled(.15,.15,.15);
	for (double i=0;i<180;i+=inc)
	{
		glBegin(GL_QUAD_STRIP);
		for (double j=0;j<=360;j+=inc)
		{
			glNormal3f( Cos(j)*Sin(i), Cos(i), Sin(j)*Sin(i));
			glTexCoord2f(j/360, i/180); 		
                glVertex3f(Cos(j+0  )*Sin(i+0  ), Cos(i+0  ), Sin(j+0  )*Sin(i+0  ));
			glNormal3f( Cos(j)*Sin(i+inc), Cos(i+inc), Sin(j)*Sin(i+inc));
			glTexCoord2f(j/360, (i+inc)/180);	
                glVertex3f(Cos(j+0  )*Sin(i+inc), Cos(i+inc), Sin(j+0  )*Sin(i+inc));
		}
		glEnd();
	}
	glPopMatrix();
	// Outside surface
	glBegin(GL_QUAD_STRIP);
	for(double i=0;i<=360;i+=5)
	{
   		glNormal3f( 0,Sin(i), Cos(i));
		glTexCoord2f(i/360,0); 
            glVertex3d(0,Sin(i)*radius,Cos(i)*radius);
		glTexCoord2f(i/360,.2); 
            glVertex3d(length,Sin(i)*radius,Cos(i)*radius);
	}
	glEnd();
	// Inside surface
	glBegin(GL_QUAD_STRIP);
	for(double i=0;i<=360;i+=5)
	{
   		glNormal3f( 0,-Sin(i), -Cos(i));
		glTexCoord2f(i/360,0); 
            glVertex3d(0,Sin(i)*(radius-thickness),Cos(i)*(radius-thickness) );
		glTexCoord2f(i/360,.2);
            glVertex3d(length,Sin(i)*(radius-thickness),Cos(i)*(radius-thickness) );
	}
	glEnd();
	// End
	glBegin(GL_QUAD_STRIP);
	glNormal3f( 1,0,0);
	for(int i=0;i<=360;i+=5)
	{
		glTexCoord2f(.5+Sin(i)*.5, .5+Cos(i)*.5  );	
            glVertex3d(length,Sin(i)*(radius-thickness),Cos(i)*(radius-thickness) );
		glTexCoord2f(.5+Sin(i)*.45, .5+Cos(i)*.45  );	
            glVertex3d(length,Sin(i)*radius,Cos(i)*radius);
	}
	glEnd();
	// Black spot inside
	glBegin(GL_POLYGON);
	glColor3f(0,0,0);
   	glNormal3f(-1,0,0);
	for(int i=0;i<=360;i+=5) {
        glVertex3d(.15,Sin(i)*(radius-thickness),Cos(i)*(radius-thickness));
    }
    glEnd();
	glPopMatrix();	
}