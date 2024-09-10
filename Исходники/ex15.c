/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   int ndm[] = {31,28,31,30,31,30,31,31,30,31,30,31};
   int doy = zh/360;
   int mo,dy,hr,mn;
   int id;
   //  Sun angle
   float fh = doy*360.0/365.0;
   //  Light direction
   float Position[]  = {Cos(fh),0.0,Sin(fh),0.0};

   //  Time of day
   id = (zh+(int)fh)%360;
   hr = (id/15)%24;
   mn = 4*(id%15);
   //  Compute month and day
   dy = doy+1;
   for (mo=0;dy>ndm[mo];mo++)
      dy -= ndm[mo];
   fh = (dy-1)/(float)ndm[mo];
   mo++;

   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Set tranformation
   glLoadIdentity();
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);

   //  OpenGL should normalize normal vectors
   glEnable(GL_NORMALIZE);
   //  Enable lighting
   glEnable(GL_LIGHTING);
   //  Enable light 0
   glEnable(GL_LIGHT0);
   //  Set position of light 0
   glLightfv(GL_LIGHT0,GL_POSITION,Position);

   //  Texture for this month
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D,day[mo-1]);
   //  Texture for next month
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D,day[mo%12]);

   //  Rotate Z up and inclined 23.5 degrees
   glRotated(-90,1,0,0);
   glRotated(-23.5,0,1,0);
   //  Draw planet
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
   //  Rotation around spin axis
   glRotated(zh,0,0,1);
   //  Solid
   gluQuadricDrawStyle(ball,GLU_FILL);
   //  Calculate normals
   gluQuadricNormals(ball,GLU_SMOOTH);
   //  Apply Textures
   gluQuadricTexture(ball,1);
   //  Enable shader
   glUseProgram(shader);
   //  Set textures
   id = glGetUniformLocation(shader,"DayTex0");
   if (id>=0) glUniform1i(id,0);
   id = glGetUniformLocation(shader,"DayTex1");
   if (id>=0) glUniform1i(id,1);
   id = glGetUniformLocation(shader,"NightTex");
   if (id>=0) glUniform1i(id,2);
   id = glGetUniformLocation(shader,"CloudGloss");
   if (id>=0) glUniform1i(id,3);
   id = glGetUniformLocation(shader,"mode");
   if (id>=0) glUniform1i(id,mode);
   id = glGetUniformLocation(shader,"frac");
   if (id>=0) glUniform1f(id,fh);
   //  Draw the ball
   gluSphere(ball,2.0,72,72);
   //  Shader off
   glUseProgram(0);

   //  No lighting from here on
   glDisable(GL_LIGHTING);
   //  Axes
   glBegin(GL_LINES);
   glVertex3f(0,0,+2.5);
   glVertex3f(0,0,-2.5);
   glEnd();

   //  Display parameters
   glColor3f(1,1,1);
   glWindowPos2i(5,5);
   Print("FPS=%d Dim=%.1f %d/%.2d %.2d:%.2d UTC %s", 
      FramesPerSecond(),dim,mo,dy,hr,mn,text[mode]);
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}