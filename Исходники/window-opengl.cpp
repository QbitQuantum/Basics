  void draw(sf::Clock &Clock)
  {	

	// Apply move direction
	if (dir == 0)
	  glRotatef(Clock.GetElapsedTime() * 90, 1.f, 0.f, 0.f);
	else if (dir == 1)
	  glRotatef(Clock.GetElapsedTime() * -90, 1.f, 0.f, 0.f);
	else if (dir == 2)
	  glRotatef(Clock.GetElapsedTime() * 90, 0.f, 1.f, 0.f);
	else if (dir == 3)
	  glRotatef(Clock.GetElapsedTime() * -90, 0.f, 1.f, 0.f);

        // Draw a cube
        glBegin(GL_QUADS);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(-50.f,  50.f, -50.f);
	glVertex3f( 50.f,  50.f, -50.f);
	glVertex3f( 50.f, -50.f, -50.f);
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-50.f, -50.f, 50.f);
	glVertex3f(-50.f,  50.f, 50.f);
	glVertex3f( 50.f,  50.f, 50.f);
	glVertex3f( 50.f, -50.f, 50.f);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f(-50.f,  50.f, -50.f);
	glVertex3f(-50.f,  50.f,  50.f);
	glVertex3f(-50.f, -50.f,  50.f);
	
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.f, -50.f, -50.f);
	glVertex3f(50.f,  50.f, -50.f);
	glVertex3f(50.f,  50.f,  50.f);
	glVertex3f(50.f, -50.f,  50.f);
	
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-50.f, -50.f,  50.f);
	glVertex3f(-50.f, -50.f, -50.f);
	glVertex3f( 50.f, -50.f, -50.f);
	glVertex3f( 50.f, -50.f,  50.f);
	
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-50.f, 50.f,  50.f);
	glVertex3f(-50.f, 50.f, -50.f);
	glVertex3f( 50.f, 50.f, -50.f);
	glVertex3f( 50.f, 50.f,  50.f);
	
        glEnd();
  }